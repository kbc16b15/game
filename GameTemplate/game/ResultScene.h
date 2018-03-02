#pragma once
#include "IScene.h"
class ResultScene :public IScene
{
public:
	//コンストラクタ
	ResultScene();
	//デストラクタ
	~ResultScene();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//フェード
	void SceneFade();
	//スプライト生成関数
	//HRESULT CreateSprite();

private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;
	Sprite				m_resultSprite;						//スプライト。
	Texture				m_resultTexture;						//背景のテクスチャ。
	const D3DXVECTOR2	m_resultPos = { 0.0f,100.0f };	//画像の座標
	const D3DXVECTOR2	m_resultScale = { 1300.0f,1200.0f };//拡大
};

