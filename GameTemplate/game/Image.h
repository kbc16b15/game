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

	HRESULT CreateSprite();		//�X�v���C�g�����֐�

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
	HUD				m_Hud[3];//�摜�\���̕ϐ�
	HUD				Key;
	LPD3DXSPRITE	m_Sprite;
	D3DXVECTOR2 Hppos = { 120.0f,80.0f };
	D3DXVECTOR2 Keypos = { 120.0f, 200.0f };
};

