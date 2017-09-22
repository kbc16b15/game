#include "stdafx.h"
#include "Scene.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	scene->SceneChange();
}

void TitleScene::Init()
{
	m_Title.Initialize("Assets/Sprite/ÇΩÇ¢Ç∆ÇÈ.jpg", titlepos, 210);
	CreateSprite();
}

void TitleScene::Update()
{
	m_Title.Update();
	pad.Update();
	if (GetAsyncKeyState('S')||pad.IsTrigger(pad.enButtonStart))
	{
		delete this;
	}
}

void TitleScene::Render()
{
	
	m_Title.Draw(m_Sprite);
	
}

HRESULT TitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}