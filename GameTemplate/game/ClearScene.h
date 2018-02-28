#pragma once
//#include "IGameObject.h"
#include "IScene.h"
#include "HUD.h"
class ClearScene :public IScene
{
public:
	//コンストラクタ
	ClearScene();
	//デストラクタ
	~ClearScene();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void /*PrePost*/Draw();
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
	EState				m_state = Run;
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD					m_clearHud;							//タイトル画像
	const D3DXVECTOR2	m_clearHudPos = { 620.0f,400.0f };	//タイトル画像の座標
};

