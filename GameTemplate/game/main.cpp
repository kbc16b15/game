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


//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	g_fade = new Fade;
	g_fade->Start();
	scene = new Scene;
	scene->SceneChange(scene->CHANGETITLE);
	g_shadowmap = new ShadowMap;
	g_shadowmap->Init();

}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	g_shadowmap->Update();
	//��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->BeginScene();
		
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		g_shadowmap->Draw();

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
//�X�e�[�W�P����
//������t����H
//�o�l�J�����A�R�[�X�J����
//�N���[���H