/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "Scene.h"
#include "TitleScene.h"
#include "ResultScene.h"

Scene::Scene()
{
}
Scene::~Scene()
{
}

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Scene::Init()
{
	//m_bScene->Init();

	switch (m_scene)
	{
	case TITLE:
		m_title = new TitleScene;
		m_title->Init();
		break;
	case GAME:
		g_game = new Game;
		g_game->Init();
		break;
	case GAME2:
		g_game = new Game;
		g_game->GetMap()->SetStage(g_game->GetMap()->STAGE2);
		g_game->Init();
		break;
	case END:
		m_end = new ResultScene;
		m_end->Init();
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------


void Scene::Render()
{
	//m_bScene->Render();

	switch (m_scene)
	{
	case TITLE:
		if (m_title != nullptr)
		{
			m_title->Render();
		}
		break;
	case GAME:
		if (g_game != nullptr)
		{
			g_game->Render();
		}
		break;
	case GAME2:
		if (g_game != nullptr)
		{
			g_game->Render();
		}
		break;
	case END:
		if (m_end != nullptr)
		{
			m_end->Render();
		}
		break;
	default:
		break;
	}
}

/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Scene::Update()
{
	//m_bScene->Update();

	switch (m_scene)
	{
	case TITLE:
		if (m_title != nullptr)
		{
			m_title->Update();
		}
		break;
	case GAME:
		if (g_game != nullptr)
		{
			g_game->Update();
		}
		break;
	case GAME2:
		if (g_game != nullptr)
		{
			g_game->Update();
		}
		break;
	case END:
		if (m_end != nullptr)
		{
			m_end->Update();
		}
		break;
	case CHANGEGAME:
		if (m_title != nullptr)
		{
			delete m_title;
			m_title = nullptr;
		}
		if (g_game != nullptr)
		{
			delete g_game;
			g_game = nullptr;
		}
		m_scene = GAME;
		Init();
		break;
	case CHANGEGAME2:
		if (m_title != nullptr)
		{
			delete m_title;
			m_title = nullptr;
		}
		if (g_game != nullptr)
		{
			delete g_game;
			g_game = nullptr;
		}
		m_scene = GAME2;
		
		Init();
		break;
	case CHANGETITLE:
		m_scene = TITLE;
		Init();
		if (m_end != nullptr)
		{
			delete m_end;
			m_end = nullptr;
		}
		
		break;
	case CHANGEEND:
		m_scene = END;
		Init();
		if (g_game != nullptr)
		{
			delete g_game;
			g_game = nullptr;
		}
		/*if (g_physicsWorld != nullptr)
		{
			delete g_physicsWorld;
			g_physicsWorld = nullptr;
		}*/
		break;
	default:
		break;
	}

}

void Scene::SceneChange(SCENE SceneNo)
{
	m_scene = SceneNo;
	//Init();
	//if (m_bScene != nullptr) {
	//	delete 	m_bScene;
	//	m_bScene = nullptr;
	//}

	//if (g_physicsWorld != nullptr)
	//{
	//	delete g_physicsWorld;
	//	g_physicsWorld = nullptr;
	//}

	//switch (SceneNo)
	//{
	//case TITLE:
	//	m_bScene = new TitleScene;
	//	//scene->Init();
	//	break;
	//case GAME:
	//	m_bScene = new Game;
	//	//m_bScene->Init();
	//	break;
	//case END:
	//	m_bScene = new ResultScene;
	//	//m_bScene->Init();
	//	break;
	//default:
	//	break;
	//}


	//case TITLE:
	//	m_Scene = CHANGEGAME;
	//	break;
	//case GAME:
	//	m_Scene = CHANGEGAME2;
	//	break;
	//case GAME2:
	//	m_Scene = CHANGETITLE;
	//	break;
	//case END:
	//	m_Scene = CHANGETITLE;
	//	break;
	//default:
	//	break;
	//}


	/*switch (SceneNo)
	{
	case TITLE:
		m_Scene = CHANGEGAME;
		break;
	case GAME:
		m_Scene = CHANGEGAME2;
		break;
	case END:
		m_Scene = CHANGETITLE;
		break;
	default:
		break;
	}*/
}