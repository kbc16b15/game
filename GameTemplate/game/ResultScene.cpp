#include "stdafx.h"
#include "Scene.h"
#include "ResultScene.h"


ResultScene::ResultScene()
{
	g_fade->StartFadeIn();
}


ResultScene::~ResultScene()
{

}

void ResultScene::Init()
{
	m_End.Initialize("Assets/Sprite/end.png", endpos);
	CreateSprite();
}

void ResultScene::Update()
{
	pad.Update();
	m_End.Update();
	//if (GetAsyncKeyState('S') || pad.IsTrigger(pad.enButtonStart))
	//{
	//	//delete this;
	//	scene->SceneChange();
	//}

	switch (GAME) {
	case START:
		switch (m_state) {
		case WaitFadeIn:
			if (!g_fade->isExecute())
			{
				m_state = Run;
			}
			break;
		case Run:
			if (pad.IsTrigger(pad.enButtonStart) || GetAsyncKeyState('S')) {
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

void ResultScene::Render()
{
	m_End.Draw(m_Sprite);
}

HRESULT ResultScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("ƒXƒvƒ‰ƒCƒgì¬¸”s"), NULL, MB_OK);
		return E_FAIL;//¸”s•Ô‹p
	}
	return S_OK;
}