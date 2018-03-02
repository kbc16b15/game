#include "stdafx.h"
#include "Silhouette.h"
#include "game.h"
#include "SceneManager.h"
#include "Player.h"

Silhouette::Silhouette()
{
}


Silhouette::~Silhouette()
{
}

//���̂ɎՕ�����Ă���Ƃ��ɂ����`�悷�� �V���G�b�g
void Silhouette::Draw()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z�l���������܂Ȃ��悤�ɂ���
	SceneManager::GetInstance().GetGame().GetPlayer().ShadowDraw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix(),true, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}