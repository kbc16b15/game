#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
//#include "BaseScene.h"
class TitleScene
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
	void Render();
	//スプライト生成関数
	HRESULT CreateSprite();
private:
	//ステート
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//選択
	enum Select{
		NO,
		START,
		BREAK,
	};
	Select				GAME = START;					//状態
	EState				m_state = Run;					//フェード
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD					m_title;						//タイトル画像
	const D3DXVECTOR2	m_titlePos = { 595.0f,400.0f };	//タイトル画像の座標
	Pad					m_pad;							//パッド
	
};

