/*!
*@brief	�Q�[���e���v���[�g�B
*/
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Scene.h"
#include "Fade.h"
Game* game=nullptr;
Scene* scene=nullptr;
Fade* g_fade = nullptr;
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	g_fade = new Fade;
	g_fade->Start();
	scene = new Scene;
	scene->Init();
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	//��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();
	scene->Render();
	g_fade->Draw();


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

//�T�E���h������
//���쐬
//�����̍l�����X�e�[�W1�Ԗڂ��쐬
//�J�����̓���������
//�v���C���[���ǂ̉��ɂ��Ă������Č�����悤�ɂ���
