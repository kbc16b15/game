#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"
#include "Fade.h"
#include "SceneManager.h"
//TitleScene *TitleScene::m_title = NULL;

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{
	delete m_titleHud;
	if (m_buttonSound != nullptr) {
		delete m_buttonSound;
		m_buttonSound = nullptr;
	}
}

void TitleScene::Init()
{
	m_titleHud = new HUD;
	m_titleHud->Initialize("Assets/Sprite/T2.tga", m_titlePos);
	CreateSprite();
	m_buttonSound = new Sound;
	m_titleHud->Update();
}

void TitleScene::Update()
{
	if (m_buttonSound != nullptr) {
		if (m_buttonSound->IsPlaying())
			m_buttonSound->Update();
	}
	SceneFade();
}

void TitleScene::Draw()
{
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	m_titleHud->Draw(m_sprite);

	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	
}

void TitleScene::SceneFade()
{
	//switch (GAME) {
	//case START:
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute())
		{
			if (m_isStart)
			{
				m_state = Run;
				m_isStart = false;
			}
			else
			{
				Fade::GetInstance().StartFadeIn();
				m_state = Run;
			}
		}
		break;
	case Run:
		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonStart) || GetAsyncKeyState('S')) {
			Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
			m_buttonSound->Init("Assets/Sound/select2.wav");
			m_buttonSound->SetVolume(0.4f);
			m_buttonSound->Play(false);

		}
		break;
	case WaitFadeOut:

		if (!Fade::GetInstance().isExecute())
		{
			SceneManager::ChangeScene(SceneManager::GAME);
		}
		break;
	default:
		break;
	}
}

HRESULT TitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("ƒXƒvƒ‰ƒCƒgì¬¸”s"), NULL, MB_OK);
		return E_FAIL;//¸”s•Ô‹p
	}
	return S_OK;
}