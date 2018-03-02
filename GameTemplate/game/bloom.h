#pragma once
#include "RenderTarget.h"
class Bloom:public IGameObject
{
public:
	//コンストラクタ
	Bloom();
	//デストラクタ
	~Bloom();
	//更新
	void Update();
	//描画
	void Draw();
	//重み更新
	void UpdateWeight(float dispersion);

//	//インスタンスの生成
//	static void Bloom::Create()
//	{
//		if (!m_bloom)
//		{
//			m_bloom = new Bloom;
//		}
//	}
//	//インスタンスの消去
//	static  void Bloom::Destroy()
//	{
//		delete m_bloom;
//		m_bloom = nullptr;
//	}
//	//インスタンスの取得
//	static Bloom& GetInstance()
//	{
//		return *m_bloom;
//	}
//private:
//	static Bloom* m_bloom;//インスタンス
private:
	static const int MGF_DOWN_SAMPLE_COUNT = 5;
	LPD3DXEFFECT effect;
	RenderTarget luminanceRenderTarget;
	RenderTarget downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];
	static const int NUM_WEIGHT = 4;
	float weights[NUM_WEIGHT];
};

