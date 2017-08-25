#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::Initialize()
{

	m_position = D3DXVECTOR2(Hppos);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0, 1.0);
	m_backColor = D3DCOLOR_ARGB(210, 255, 255, 255);//A‚Í“§–¾“x
	m_texFileName = "Assets/Sprite/HP.png";
	Sprite::Initialize();
	
}

void HUD::Update()
{
	
	SetupMatrices();
	
}
