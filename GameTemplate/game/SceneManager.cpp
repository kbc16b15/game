#include "stdafx.h"
#include "SceneManager.h"
#include "game.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "ClearScene.h"

IScene *SceneManager::m_pScene= NULL;
SceneManager *SceneManager::m_sMgr = NULL;
Game *SceneManager::m_game = NULL;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(SCENE scene)
{
	if (m_pScene != NULL) {
		
		delete m_pScene;
	}
	switch (scene) {          //引数のシーン
	case SCENE::TITLE:
		//m_pScene = new TitleScene();      //タイトルシーン
		ChangeState(new TitleScene);
		break;
	case SCENE::GAME:
		//m_pScene = new Game();       //ゲームシーン
		m_game = new Game();
		m_game->SetStage(0);
		m_pScene = m_game;
		break;
	case SCENE::GAME2:
		m_game = new Game();
		m_game->SetStage(1);
		m_pScene = m_game;
		break;
	case SCENE::GAME3:
		m_game = new Game();
		m_game->SetStage(2);
		m_pScene = m_game;
		break;
	case SCENE::RESULT:
		//m_pScene = new ResultScene();     //リザルトシーン
		ChangeState(new ResultScene);
		break;
	case SCENE::CLEAR:
		//m_pScene = /*new ClearScene()*/;     //クリアシーン
		ChangeState(new ClearScene);
		break;
	default:
		break;
	}
	if (m_pScene != NULL) {
		m_pScene->Init();
	}


}

void SceneManager::ChangeState(IScene* state) {
	//delete m_pScene;
	m_pScene = state;
}


void SceneManager::PrePostDraw()
{
	m_pScene->Draw();
}

void SceneManager::Update()
{
	m_pScene->Update();
}