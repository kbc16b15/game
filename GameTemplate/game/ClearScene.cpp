#include "stdafx.h"
#include "ClearScene.h"
#include "SceneManager.h"
#include "Fade.h"
#include "GameObjectManager.h"
//#include "BossEnemy.h"
//#include "BossHp.h"


ClearScene::ClearScene()
{

}


ClearScene::~ClearScene()
{
	m_clearTexture.Release();
}

void ClearScene::Init()
{
	Fade::GetInstance().StartFadeIn();
	/*if (BossEnemy::GetInstance().GetDeathflg())
	{
		GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossEnemy::GetInstance());
		GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossHp::GetInstance());
		BossHp::GetInstance().Destroy();
		BossEnemy::GetInstance().Destroy();
	}*/

	m_clearTexture.Load("Assets/Sprite/GameClear.png");
	m_clearSprite.Init(&m_clearTexture);
	m_clearSprite.SetSize(m_clearScale);
}

void ClearScene::Update()
{

	SceneFade();
}

void ClearScene::Draw()
{

	m_clearSprite.Draw();

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
			//exit(0);
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