/*!
*@brief	�Q�[���e���v���[�g�B
*/
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Scene.h"
#include "Fade.h"
#include "ShadowMap.h"

Game* game=nullptr;
Scene* scene=nullptr;
Fade* g_fade = nullptr;
ShadowMap* g_shadowmap= nullptr;
//Player* g_player = nullptr;
//Camera* g_camera=nullptr;
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	g_fade = new Fade;
	g_fade->Start();
	scene = new Scene;
	scene->SceneChange(scene->CHANGETITLE);
	//scene->Init();
	g_shadowmap = new ShadowMap;
	g_shadowmap->Init();
	//g_camera = new Camera;
	//g_camera->Init()
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	/*if (g_player != nullptr)
	{
		D3DXVECTOR3 toPos = g_player->Getpos();
		toPos.y = 7.0f;
		g_shadowmap->SetviewPosition(toPos);
		g_shadowmap->SetviewTarget(g_player->Getpos());
	}
	else
	{
		g_shadowmap->SetviewTarget({0.0f,0.0f,0.0f});
		g_shadowmap->SetviewPosition({0.0f,10.0f,0.0f});
	}*/
	g_shadowmap->Update();
	//��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->BeginScene();
		
		if (game != NULL)
		{
			g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

			g_shadowmap->Draw();
		}
		scene->Render();
		
		g_fade->Draw();

	}

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
*@brief	�X�V�����B
-----------------------------------------------------------------------------*/
void Update()
{
	scene->Update();
	g_fade->Update();
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	delete scene;
	delete g_fade;
	delete game;
	delete g_effectManager;
}

//������t����H
//���C�g�̒���
//�J�����̓���������
//�v���C���[���ǂ̉��ɂ��Ă������Č�����悤�ɂ���
