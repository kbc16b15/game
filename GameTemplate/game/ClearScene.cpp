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
	if (BossEnemy::GetInstance().GetDeathflg())
	{
		GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossEnemy::GetInstance());
		GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossHp::GetInstance());
		BossEnemy::GetInstance().Destroy();
		BossHp::GetInstance().Destroy();

	}

	m_clearHud.Initialize("Assets/Sprite/T2.tga", m_clearHudPos);
	CreateSprite();

}

void ClearScene::Update()
{
	if (m_clear == NULL) { return; };
	m_clearHud.Update();
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
			Fade::GetInstance().StartFadeIn();
			m_state = Run;
		}
		break;
	case Run:
		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S')) {
			Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
		}
		break;
	case WaitFadeOut:
		if (!Fade::GetInstance().isExecute())
		{
			TitleScene::Create();
			TitleScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());

			GameObjectManager::GetGameObjectManager().DeleteGameObject(&ResultScene::GetInstance());
			ResultScene::GetInstance().Destroy();
			return;

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
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}
