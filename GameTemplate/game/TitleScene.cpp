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
	m_Title.Initialize("Assets/Sprite/たいとる.jpg",titlepos);
	//m_Title.Setalfa(10);
	//m_Title.SetRGB(0, 0, 0);
	CreateSprite();
	//g_fade->StartFadeIn();

}

void TitleScene::Update()
{
	//if (m_Title == NULL)return;
	m_Title.Update();
	pad.Update();
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
			if (pad.IsTrigger(pad.enButtonStart)||GetAsyncKeyState('S')){
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (!g_fade->isExecute())
			{
				//delete this;
				scene->SceneChange(scene->CHANGEGAME);
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
	m_Title.Draw(m_Sprite);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
}

HRESULT TitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}