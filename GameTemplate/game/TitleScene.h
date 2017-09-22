#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
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
	LPD3DXSPRITE		m_Sprite;						//スプライト
	HUD					m_Title;						//タイトル画像
	const D3DXVECTOR2	titlepos = { 700.0f,300.0f };	//タイトル画像の座標
	Pad					pad;								//パッド
};

