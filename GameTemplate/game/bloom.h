#pragma once
#include "RenderTarget.h"
class Bloom
{
public:
	Bloom();
	~Bloom();

	void Draw();

	void UpdateWeight(float dispersion);
private:
	LPD3DXEFFECT effect;
	CRenderTarget luminanceRenderTarget;
	CRenderTarget downSamplingRenderTarget[2];
	static const int NUM_WEIGHT = 8;
	float weights[NUM_WEIGHT];
};

