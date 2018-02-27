#include "stdafx.h"
#include "myEngine\Graphics\Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{

	
}

void Sprite::Initialize(LPCTSTR modelName,D3DXVECTOR2 position)
{
	D3DXIMAGE_INFO imgInfo;
	D3DXCreateTextureFromFileEx(g_pd3dDevice, modelName, 0, 0, 0, 0, /*D3DFMT_A8R8G8B8*/D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, /*D3DCOLOR_ARGB(255,255, 255, 255)*//*0xff000000*/NULL, &imgInfo, NULL, &m_pTexture);
	this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);
	RECT rec = { 0,0,imgInfo.Width,imgInfo.Height };
	memcpy(&m_rect, &rec, sizeof(RECT));

}

void Sprite::SetupMatrices()
{

	/*D3DXMatrixIdentity(&m_transformMatrix);
	D3DXMatrixTransformation2D(&m_transformMatrix, NULL, 0.0f, &m_scale, NULL, D3DXToRadian(m_angle), &m_position);
*/
}

void Sprite::Draw(LPD3DXSPRITE pSprite)
{
	D3DXMatrixIdentity(&m_transformMatrix);
	D3DXMatrixTransformation2D(&m_transformMatrix, NULL, 0.0f, &m_scale, NULL, D3DXToRadian(m_angle), &m_position);

	//m_Sprite = pSprite;
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->SetTransform(&m_transformMatrix);
	pSprite->Draw(m_pTexture, &m_rect, &D3DXVECTOR3(m_texCenter.x, m_texCenter.y, 0.0f), NULL, m_backColor);//テクスチャの位置
	pSprite->End();

}