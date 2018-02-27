#include "stdafx.h"
#include "ClearScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "HUD.h"
#include "GameObjectManager.h"
#include "BossEnemy.h"
#include "BossHp.h"

ClearScene *ClearScene::m_clear = NULL;

ClearScene::ClearScene()
{
}


ClearScene::~ClearScene()
{
}

void ClearScene::Init()
{
	Fade::GetInstance().StartFadeIn();
	if (BossEnemy::GetInstance().GetDeathflg())
	{
		GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossEnemy::GetInstance());
		GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossHp::GetInstance());
		BossHp::GetInstance().Destroy();
		BossEnemy::GetInstance().Destroy();
	}

	m_clearHud.Initialize("Assets/Sprite/GameClear.png", m_clearHudPos);
	CreateSprite();
	m_clearHud.Update();
}

void ClearScene::Update()
{
	if (m_clear == NULL) { return; };
	//m_clearHud.Update();
	SceneFade();
}

void ClearScene::PrePostDraw()
{

	m_clearHud.Draw(m_sprite);

}

void ClearScene::SceneFade()
{
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute())
		{
			/*Fade::GetInstance().StartFadeIn();*/
			m_state = Run;
		}
		break;
	case Run:
		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S')) {
			//Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
			exit(0);
		}
		break;
	case WaitFadeOut:
		if (!Fade::GetInstance().isExecute())
		{
			/*TitleScene::Create();
			TitleScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());

			GameObjectManager::GetGameObjectManager().DeleteGameObject(&ClearScene::GetInstance());
			ClearScene::GetInstance().Destroy();*/

		}
		break;
	default:
		break;
	}
}

HRESULT ClearScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
