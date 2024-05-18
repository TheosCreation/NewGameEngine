#pragma once

#include "MeshEntity.h"

class InstancedMeshEntity : public MeshEntity
{
public:
	void setMesh(const InstancedMeshPtr& mesh);
	InstancedMeshPtr getMesh();

	void onCreate() override;
	void setUniformData(UniformData data) override;
	void onGraphicsUpdate(float deltaTime) override;
private:
	InstancedMeshPtr m_mesh;
};