/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "Scene.h"
#include "TitleScene.h"
#include "ResultScene.h"
//BaseScene *Scene::m_bScene = NULL;
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

	switch (m_Scene)
	{
	case TITLE:
		 //scene= new TitleScene;
		title = new TitleScene;
		title->Init();
		break;
	case GAME:
		//scene = new Game;
		game = new Game;
		game->Init();
		break;
	/*case GAME2:
		game = new Game;
		game->Init();
		break;*/
	case END:
		//scene = new ResultScene;
		end = new ResultScene;
		end->Init();
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

	switch (m_Scene)
	{
	case TITLE:
		if (title != nullptr)
		{
			title->Render();
		}
		break;
	case GAME:
		if (game != nullptr)
		{
			game->Render();
		}
		break;
	//case GAME2:
	//	game->Render();
	//	break;
	case END:
		if (end != nullptr)
		{
			end->Render();
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


	switch (m_Scene)
	{
	case TITLE:
		if (title != nullptr)
		{
			title->Update();
		}
		break;
	case GAME:
		if (game != nullptr)
		{
			game->Update();
		}
		break;
	//case GAME2:
	//	game->Update();
	//	break;
	case END:
		if (end != nullptr)
		{
			end->Update();
		}
		break;
	case CHANGEGAME:
		if (title != nullptr)
		{
			delete title;
			title = nullptr;
		}
		m_Scene = GAME;
		Init();
		break;
	/*case CHANGEGAME2:
		delete game;
		game = nullptr;
		delete g_physicsWorld;
		g_physicsWorld = nullptr;
		m_Scene = GAME2;
		Init();
		break;*/
	case CHANGETITLE:
		m_Scene = TITLE;
		Init();
		if (end != nullptr)
		{
			delete end;
			end = nullptr;
		}
		break;
	case CHANGEEND:
		m_Scene = END;
		Init();
		if (game != nullptr)
		{
			delete game;
			game = nullptr;
		}
		if (g_physicsWorld != nullptr)
		{
			delete g_physicsWorld;
			g_physicsWorld = nullptr;
		}
		break;
	default:
		break;
	}

}

void Scene::SceneChange(SCENE SceneNo)
{
	m_Scene = SceneNo;
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