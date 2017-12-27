#include "stdafx.h"
#include "Scene.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Init()
{
	g_fade->StartFadeIn();
	m_title.Initialize("Assets/Sprite/たいとる.jpg",m_titlePos);
	//m_Title.Setalfa(10);
	//m_Title.SetRGB(0, 0, 0);
	CreateSprite();
	//g_fade->StartFadeIn();

}

void TitleScene::Update()
{
	//if (m_Title == NULL)return;
	m_title.Update();
	m_pad.Update();
	/*
	if (pad.IsTrigger(pad.enButtonStart)) {

		scene->SceneChange();
	}
	*/

	switch (GAME){
	case START:
		switch (m_state) {
		case WaitFadeIn:
			if (!g_fade->isExecute())
			{
				m_state = Run;
			}
			break;
		case Run:
			if (m_pad.IsTrigger(m_pad.enButtonStart)||GetAsyncKeyState('S')){
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (!g_fade->isExecute())
			{
				//delete this;
				g_scene->SceneChange(g_scene->CHANGEGAME);
				return;
				
			}
			//break;
		}
		break;
	default:
		break;
	}
}


void TitleScene::Render()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_title.Draw(m_sprite);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
}

HRESULT TitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}