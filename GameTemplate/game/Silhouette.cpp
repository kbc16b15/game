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

//物体に遮蔽されているときにだけ描画する シルエット
void Silhouette::Draw()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z値を書き込まないようにする
	SceneManager::GetInstance().GetGame().GetPlayer().ShadowDraw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix(),true, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}