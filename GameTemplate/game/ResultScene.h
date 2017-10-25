#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
class ResultScene
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
	void Render();
	//スプライト生成関数
	HRESULT CreateSprite();
private:

	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};

	enum Select {
		NO,
		START,
		BREAK,
	};
	Select GAME = START;
	EState      m_state = Run;

	LPD3DXSPRITE		m_Sprite;						//スプライト
	HUD					m_End;						//タイトル画像
	const D3DXVECTOR2	endpos = { 700.0f,300.0f };	//タイトル画像の座標
	Pad					pad;								//パッド
};

