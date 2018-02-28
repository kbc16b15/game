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
	HRESULT CreateSprite();

private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD					m_resultHud;							//タイトル画像
	const D3DXVECTOR2	m_resultHudPos = { 700.0f,300.0f };	//タイトル画像の座標
};

