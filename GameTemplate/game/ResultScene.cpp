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
	g_fade->StartFadeIn();
	m_end.Initialize("Assets/Sprite/end.png", m_endPos);
	CreateSprite();
}

void ResultScene::Update()
{
	m_pad.Update();
	m_end.Update();
	//if (GetAsyncKeyState('S') || pad.IsTrigger(pad.enButtonStart))
	//{
	//	//delete this;
	//	scene->SceneChange();
	//}

	switch (GAME) {
	case START:
		switch (m_state) {
		case WaitFadeIn:
			if (!g_fade->isExecute())
			{
				m_state = Run;
			}
			break;
		case Run:
			if (m_pad.IsTrigger(m_pad.enButtonStart) || GetAsyncKeyState('S')) {
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (!g_fade->isExecute())
			{
				//delete this;
				g_scene->SceneChange(g_scene->CHANGETITLE);
				return;

			}
			break;
		}
		break;
	}
}

void ResultScene::Render()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_end.Draw(m_sprite);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT ResultScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}