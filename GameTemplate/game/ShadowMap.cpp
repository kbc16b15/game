#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	D3DXMatrixIdentity(&m_lightViewMatrix);
	D3DXMatrixIdentity(&m_lightProjectionMatrix);
	m_viewPosition.x = 0.0f;
	m_viewPosition.y = 0.0f;
	m_viewPosition.z = 0.0f;
	m_viewTarget.x = 0.0f;
	m_viewTarget.y = 0.0f;
	m_viewTarget.z = 0.0f;

}

ShadowMap::~ShadowMap()
{
}

void ShadowMap::Init()
{
	m_renderTarget.Create(
		512,
		512,
		1,
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);

}


void ShadowMap::Update()
{

	D3DXVECTOR3 tmp = m_viewTarget - m_viewPosition;
	D3DXVec3Normalize(&tmp, &tmp);
	if (fabsf(tmp.y) > 0.9999f)
	{
		D3DXMatrixLookAtLH(&m_lightViewMatrix, &m_viewPosition, &m_viewTarget, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	}
	else
	{
		D3DXMatrixLookAtLH(&m_lightViewMatrix, &m_viewPosition, &m_viewTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	D3DXMatrixPerspectiveFovLH(&m_lightProjectionMatrix, D3DXToRadian(60.0f), 1.0f, 0.1f, 100.0f);

}

void ShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTargetBackup;
	LPDIRECT3DSURFACE9 depthBufferBackup;

	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);

	g_pd3dDevice->SetRenderTarget(0, m_renderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(m_renderTarget.GetDepthStencilBuffer());
	//g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	if (g_game != NULL && g_game->GetPlayer() != NULL)
	{
		g_game->GetPlayer()->Draw(&m_lightViewMatrix,&m_lightProjectionMatrix,true,false);
	}

	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);


}