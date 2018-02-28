#pragma once
#include "HUD.h"
#include "Sound.h"
#include "IScene.h"
//#include "IGameObject.h"
class TitleScene :public IScene
{
public:
	//コンストラクタ
	TitleScene();
	//デストラクタ
	~TitleScene();
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
	//初回だけフェードインをなくす
	void SetStart(bool start)
	{
		m_isStart = start;
	}

private:

	//ステート
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;			//フェード
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD*				m_titleHud;						//タイトル画像
	const D3DXVECTOR2	m_titlePos = { 595.0f,400.0f };	//タイトル画像の座標
	bool				m_isStart = false;
	Sound*				m_buttonSound = nullptr;			//サウンド
};

