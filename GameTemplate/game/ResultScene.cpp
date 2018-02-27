#include "stdafx.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "HUD.h"
#include "game.h"
#include "GameObjectManager.h"
//#include "SceneChange.h"
#include "BossEnemy.h"
#include "BossHp.h"

ResultScene *ResultScene::m_result = NULL;

ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Init()
{
	/*if (SceneChange::GetInstance().GetChange())
	{
		return;
	}*/

	//BossEnemy::GetInstance();
	//if (BossEnemy::GetInstance().GetDeathflg())//プレイヤーが死んだときにボスが消えない（1回目だけ？）
	//{
	//	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossEnemy::GetInstance());
	//	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossHp::GetInstance());
	//	BossHp::GetInstance().Destroy();BossEnemy::GetInstance().Destroy();
	//	BossEnemy::GetInstance().Destroy();
	//	
	//}
	m_resultHud.Initialize("Assets/Sprite/TE.tga", m_resultHudPos);
	CreateSprite();
	m_resultHud.Update();
}

void ResultScene::Update()
{
	if (m_result == NULL) { return; };
	/*m_resultHud.Update();*/
	SceneFade();
}

void ResultScene::PrePostDraw()
{
	/*if (SceneChange::GetInstance().GetChange())
	{
		return;
	}*/
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_resultHud.Draw(m_sprite);
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
		/*if (SceneChange::GetInstance().GetChange())
		{
			m_state = Run;
		}
		else */if (!Fade::GetInstance().isExecute())
		{
			m_state = Run;
			Fade::GetInstance().StartFadeIn();
		}
		break;
	case Run:
		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S'))
		{

			TitleScene::Create();
			TitleScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());
			m_state = WaitFadeOut;
			Fade::GetInstance().StartFadeOut();
		}
		break;
	case WaitFadeOut:
		if (!Fade::GetInstance().isExecute())
		{
			GameObjectManager::GetGameObjectManager().DeleteGameObject(&ResultScene::GetInstance());
			ResultScene::GetInstance().Destroy();
		}
		break;
	default:
		break;
	}
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