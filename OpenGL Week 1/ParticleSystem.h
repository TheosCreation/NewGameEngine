#pragma once
#include "Utils.h"
#include "GraphicsEntity.h"

class ParticleSystem : public GraphicsEntity
{
public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onGraphicsUpdate(UniformData data) override;

	void setOrigin(Vector3 origin);
	void setComputeShader(ShaderPtr shader);

private:
	uint VAO;
	uint VBO_PositionLife;
	uint VBO_Velocity;

	ShaderPtr m_computeShader;

	Vector3 EmitterOrigin = Vector3(0.0f);
	Vector4 VelocityLifeChange;

	int GroupCountX;
	int WorkGroupSizeX;
	int NumParticles;
};

