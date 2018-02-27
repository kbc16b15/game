#include "stdafx.h"
#include "SceneChange.h"
#include "game.h"
#include "Fade.h"
#include "GameObjectManager.h"
#include "Map.h"

SceneChange *SceneChange::m_change = NULL;

SceneChange::SceneChange()
{
}

SceneChange::~SceneChange()
{
}

void SceneChange::Init()
{
	m_changeHud.Initialize("Assets/Sprite/TL.tga", m_changePos);
	CreateSprite();
}

void SceneChange::Update()
{
	//if (m_change == NULL) { return; };
	m_changeHud.Update();
	SceneFade();
}

void SceneChange::PrePostDraw()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_changeHud.Draw(m_sprite);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

}

void SceneChange::SceneFade()
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
		if (SceneChange::GetInstance().GetChange()/*Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S')*/) {

			m_state = WaitFadeOut;

			Game::Create();
			//Map::Create();
			//Map::GetInstance().SetStage(1);
			//Map::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&Game::GetInstance());
			Game::GetInstance().Init();
			
			Fade::GetInstance().StartFadeOut();
			SceneChange::GetInstance().SetChange(false);
		}
		break;
	case WaitFadeOut:

		if (!Fade::GetInstance().isExecute())
		{
			GameObjectManager::GetGameObjectManager().DeleteGameObject(&SceneChange::GetInstance());
			SceneChange::GetInstance().Destroy();
			//return;
		}
		break;
	default:
		break;
	}

}

HRESULT SceneChange::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}