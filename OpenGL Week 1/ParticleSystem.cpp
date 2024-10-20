#include "ParticleSystem.h"
#include "GraphicsEngine.h"
#include "Shader.h"

void ParticleSystem::onCreate()
{
	GroupCountX = 1000;
	WorkGroupSizeX = 128;
	NumParticles = WorkGroupSizeX * GroupCountX;

	// Store Position and Lifespan info
	glGenBuffers(1, &VBO_PositionLife);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, VBO_PositionLife);
	glBufferData(GL_SHADER_STORAGE_BUFFER,
		sizeof(Vector4) * NumParticles,
		NULL,
		GL_DYNAMIC_DRAW);

	// Store Velocity info
	glGenBuffers(1, &VBO_Velocity);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, VBO_Velocity);
	glBufferData(GL_SHADER_STORAGE_BUFFER,
		sizeof(Vector4) * NumParticles,
		NULL,
		GL_DYNAMIC_DRAW);

	// VAO for the standard render
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO for the standard pipeline render
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PositionLife);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, NULL, 0);
	glEnableVertexAttribArray(0);

	// Unbinding
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ParticleSystem::onUpdate(float deltaTime)
{
	Vector3 Gravity = Vector3(0.0f, -9.8f, 0.0f) * deltaTime;
	VelocityLifeChange = Vector4(Gravity, deltaTime);
}

void ParticleSystem::onGraphicsUpdate(UniformData data)
{
	auto& graphicsEngine = GraphicsEngine::GetInstance();
	graphicsEngine.setShader(m_computeShader);

	// Setting up seed values for the compute shader
	int seedLife = static_cast<int>(randomRange(1000.0f, 10000.0f));
	int seedX = static_cast<int>(randomRange(1000.0f, 10000.0f));
	int seedY = static_cast<int>(randomRange(1000.0f, 10000.0f));
	int seedZ = static_cast<int>(randomRange(1000.0f, 10000.0f));

	// Set the uniform values for the compute shader
	m_computeShader->setInt("SeedLife", seedLife);
	m_computeShader->setInt("SeedX", seedX);
	m_computeShader->setInt("SeedY", seedY);
	m_computeShader->setInt("SeedZ", seedZ);
	m_computeShader->setVec4("VelocityLifeChange", VelocityLifeChange);
	m_computeShader->setVec3("EmitterOrigin", EmitterOrigin);

	// Bind the storage buffers for compute shader manipulations
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, VBO_PositionLife);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, VBO_Velocity);

	// Set the compute shdaer going
	glDispatchCompute(	GroupCountX,	// X
						1,				// Y
						1);

	// Wait for the compute shader completion and sync all threads
	glMemoryBarrier(GL_ALL_BARRIER_BITS);

	// Standard pass
	graphicsEngine.setShader(m_shader);
	m_shader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);

	graphicsEngine.setVertexArrayObject(VAO); //bind vertex buffer to graphics pipeline
	graphicsEngine.drawTriangles(TriangleType::Points, NumParticles, 0); // draw triangles

	// Unbinding
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void ParticleSystem::setOrigin(Vector3 origin)
{
	EmitterOrigin = origin;
}

void ParticleSystem::setComputeShader(ShaderPtr shader)
{
	m_computeShader = shader;
}
