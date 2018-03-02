#include "stdafx.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "game.h"
#include "SceneManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	m_resultTexture.Release();
}

void ResultScene::Init()
{
	m_resultTexture.Load("Assets/Sprite/TE.tga");
	m_resultSprite.Init(&m_resultTexture);
	m_resultSprite.SetPosition(m_resultPos);
	m_resultSprite.SetSize(m_resultScale);
}

void ResultScene::Update()
{

	SceneFade();
}

void ResultScene::Draw()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//m_resultHud.Draw(m_sprite);
	m_resultSprite.Draw();
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

void ResultScene::SceneFade()
{
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute())
		{
			m_state = Run;
			Fade::GetInstance().StartFadeIn();
		}
		break;
	case Run:
		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S'))
		{
			m_state = WaitFadeOut;
			Fade::GetInstance().StartFadeOut();
		}
		break;
	case WaitFadeOut:
		if (!Fade::GetInstance().isExecute())
		{
			SceneManager::ChangeScene(SceneManager::TITLE);
		}
		break;
	default:
		break;
	}
}