#pragma once
#include "QuadEntity.h"

class SSRQuad : public QuadEntity
{
public:

	void onGraphicsUpdate(UniformData data) override;
	void onLightingPass(UniformData data) override;
	void onShadowPass(int index) override;
};

