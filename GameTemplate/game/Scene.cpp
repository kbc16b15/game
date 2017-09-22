/*!
*@brief	�Q�[���e���v���[�g�B
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
// Name: �Q�[�����������B
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
	default:
		break;
	}
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
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
	default:
		break;
	}
}

/*!-----------------------------------------------------------------------------
*@brief	�X�V�����B
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
	case CHANGEGAME:
		m_Scene = GAME;
		Init();
		break;
	case CHANGETITLE:
		m_Scene = TITLE;
		Init();
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
		m_Scene = CHANGETITLE;
		break;
	default:
		break;
	}
}