/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "Scene.h"

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

	switch (m_Scene)
	{
	case TITLE:
		title = new TitleScene;
		title->Init();
		break;
	case GAME:
		game = new Game;
		game->Start();
		break;
	case GAME2:
		game = new Game;
		game->GetMap()->SetStage(1);
		game->Start();
		
		break;
	case END:
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

	switch (m_Scene)
	{
	case TITLE:
		title->Render();
		break;
	case GAME:
		game->Render();
		break;
	case GAME2:
		game->Render();
		break;
	case END:
		end->Render();
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

	switch (m_Scene)
	{
	case TITLE:
		title->Update();
		break;
	case GAME:
		game->Update();
		break;
	case GAME2:
		game->Update();
		break;
	case END:
		end->Update();
		break;
	case CHANGEGAME:
		delete title;
		title = nullptr;
		m_Scene = GAME;
		Init();
		break;
	case CHANGEGAME2:
		delete game;
		game = nullptr;
		delete g_physicsWorld;
		g_physicsWorld = nullptr;
		m_Scene = GAME2;
		Init();
		break;
	case CHANGETITLE:
		m_Scene = TITLE;
		Init();
		delete end;
		end = nullptr;
		break;
	case CHANGEEND:
		m_Scene = END;
		Init();
		delete game;
		game = nullptr;
		delete g_physicsWorld;
		g_physicsWorld = nullptr;
		break;
	default:
		break;
	}
}

void Scene::SceneChange()
{
	switch (m_Scene)
	{
	case TITLE:
		m_Scene = CHANGEGAME;
		break;
	case GAME:
		m_Scene = CHANGEGAME2;
		break;
	case GAME2:
		
		m_Scene = CHANGETITLE;
		break;
	case END:
		m_Scene = CHANGETITLE;
		break;
	default:
		break;
	}
}