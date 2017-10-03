#include "stdafx.h"
#include "Scene.h"
#include "ResultScene.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{

}

void ResultScene::Init()
{
	m_End.Initialize("Assets/Sprite/end.png", endpos);
	CreateSprite();
}

void ResultScene::Update()
{
	pad.Update();
	m_End.Update();
	if (GetAsyncKeyState('S') || pad.IsTrigger(pad.enButtonStart))
	{
		//delete this;
		scene->SceneChange();
	}
}

void ResultScene::Render()
{
	m_End.Draw(m_Sprite);
}

HRESULT ResultScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}