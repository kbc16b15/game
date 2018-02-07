#pragma once
#include "RenderTarget.h"
class Bloom:public IGameObject
{
public:
	~Bloom();

	void Update();
	void Draw();

	void UpdateWeight(float dispersion);

	//�C���X�^���X�̐���
	static void Bloom::Create()
	{
		if (!m_bloom)
		{
			m_bloom = new Bloom;
		}
	}
	//�C���X�^���X�̏���
	static  void Bloom::Destroy()
	{
		delete m_bloom;
		m_bloom = nullptr;
	}
	//�C���X�^���X�̎擾
	static Bloom& GetInstance()
	{
		return *m_bloom;
	}
private:
	
	//�R���X�g���N�^
	Bloom();
	static Bloom* m_bloom;//�C���X�^���X
private:
	static const int MGF_DOWN_SAMPLE_COUNT = 5;
	LPD3DXEFFECT effect;
	RenderTarget luminanceRenderTarget;
	RenderTarget downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];
	static const int NUM_WEIGHT = 4;
	float weights[NUM_WEIGHT];
};

