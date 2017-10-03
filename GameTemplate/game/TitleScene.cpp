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

	m_Title.Initialize("Assets/Sprite/�����Ƃ�.jpg",titlepos);
	//m_Title.Setalfa(10);
	//m_Title.SetRGB(0, 0, 0);
	CreateSprite();
	//g_fade->StartFadeIn();

}

void TitleScene::Update()
{

	m_Title.Update();
	pad.Update();
	/*if (pad.IsTrigger(pad.enButtonStart)) {

		scene->SceneChange();
	}*/

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
			if (pad.IsTrigger(pad.enButtonStart)) {
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (!g_fade->isExecute())
			{
				//delete this;
				scene->SceneChange();
				return;
				
			}
			break;
		}
		break;
	}
}


void TitleScene::Render()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_Title.Draw(m_Sprite);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	
}

HRESULT TitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}