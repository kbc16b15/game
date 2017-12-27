#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
//#include "BaseScene.h"
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
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//選択
	enum Select {
		NO,
		START,
		BREAK,
	};
	Select				GAME = START;
	EState				m_state = Run;
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD					m_end;							//タイトル画像
	const D3DXVECTOR2	m_endPos = { 700.0f,300.0f };	//タイトル画像の座標
	Pad					m_pad;							//パッド
};

