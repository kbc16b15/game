#include "stdafx.h"
#include "Image.h"

Image::Image()
{
}


Image::~Image()
{
}

void Image::Init()
{
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Initialize("Assets/Sprite/HP.png", Hppos, 210);
		Hppos.x += 100.0f;

	}
	Key.Initialize("Assets/Sprite/key.png", Keypos, 210);
	CreateSprite();
}

void Image::Update()
{
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Update();
	}
	Key.Update();
}

void Image::Render()
{
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Draw(m_Sprite);
	}
	Key.Draw(m_Sprite);
}

HRESULT Image::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("ƒXƒvƒ‰ƒCƒgì¬Ž¸”s"), NULL, MB_OK);
		return E_FAIL;//Ž¸”s•Ô‹p
	}
	return S_OK;
}
