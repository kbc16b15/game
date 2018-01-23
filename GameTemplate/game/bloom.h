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
	static const int MGF_DOWN_SAMPLE_COUNT = 5;
	LPD3DXEFFECT effect;
	CRenderTarget luminanceRenderTarget;
	CRenderTarget downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];
	static const int NUM_WEIGHT = 4;
	float weights[NUM_WEIGHT];
};

