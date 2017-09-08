#pragma once
#include "HUD.h"
class Image
{
public:
	Image();
	~Image();
	void Init();
	void Update();
	void Render();

	HRESULT CreateSprite();		//スプライト生成関数

	void Damage(int dame)
	{
		Hpnum -= dame;
	}

	int GetHp()
	{
		return Hpnum;
	}
private:
	int				Hpnum = 3;
	HUD				m_Hud[3];//画像表示の変数
	HUD				Key;
	LPD3DXSPRITE	m_Sprite;
	D3DXVECTOR2 Hppos = { 120.0f,80.0f };
	D3DXVECTOR2 Keypos = { 120.0f, 200.0f };
};

