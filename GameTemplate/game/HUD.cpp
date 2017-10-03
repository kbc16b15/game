#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::Initialize(LPCTSTR modelName,D3DXVECTOR2 position)
{

	m_position = D3DXVECTOR2(position/*Hppos*/);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0, 1.0);
	m_backColor = D3DCOLOR_COLORVALUE(Red, Green,Blue, alfa);//A‚Í“§–¾“x
	//m_backColor = D3DCOLOR_ARGB(alfa,255, 255,255);//A‚Í“§–¾“x
	Sprite::Initialize(modelName,position);
	
}

void HUD::Update()
{
	
	SetupMatrices();
	
}
