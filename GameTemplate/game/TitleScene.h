#pragma once
#include "Sound.h"
#include "IScene.h"
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
	Sprite				m_titleSprite;					//タイトル画面の背景のスプライト。
	Texture				m_titleTexture;					//タイトル画面の背景のテクスチャ。
	const D3DXVECTOR2	m_titlePos = { 0.0f,0.0f };		//タイトル画像の座標
	const D3DXVECTOR2	m_titleScale = { 1300.0f,1200.0f };//タイトル画像の拡大
	bool				m_isStart = false;
	Sound*				m_buttonSound = nullptr;		//サウンド
};

