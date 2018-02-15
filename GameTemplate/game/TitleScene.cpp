#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"
#include "Fade.h"
#include "GameObjectManager.h"
TitleScene *TitleScene::m_title = NULL;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Init()
{
	m_titleHud.Initialize("Assets/Sprite/T2.tga",m_titlePos);
	CreateSprite();
	//Fade::GetInstance().StartFadeIn();
}

void TitleScene::Update()
{
	if (m_title == NULL) { return; };
	m_titleHud.Update();
	SceneFade();
}


void TitleScene::Draw()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_titleHud.Draw(m_sprite);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	
}

void TitleScene::SceneFade()
{
	//switch (GAME) {
	//case START:
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute())
		{
			Fade::GetInstance().StartFadeIn();
			m_state = Run;
		}
		break;
	case Run:
		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S')) {

			m_state = WaitFadeOut;
			
			Game::Create();
			GameObjectManager::GetGameObjectManager().AddGameObject(&Game::GetInstance());
			Game::GetInstance().Init();
			Fade::GetInstance().StartFadeOut();

		}
		break;
	case WaitFadeOut:

		if (!Fade::GetInstance().isExecute())
		{
			GameObjectManager::GetGameObjectManager().DeleteGameObject(&TitleScene::GetInstance());
			TitleScene::GetInstance().Destroy();
			//return;
		}
		break;
	default:
		break;
	}
		//break;
	//default:
	//	break;
	//}
}

HRESULT TitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}