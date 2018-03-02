#include "stdafx.h"
#include "myEngine\Graphics\Sprite.h"
#include "VertexElement.h"

Sprite::Sprite()
{
	D3DXQuaternionIdentity(&m_rotation);
}


Sprite::~Sprite()
{

	
}

void Sprite::Init(Texture* texture)
{
	m_spritePrimitive = new Primitive;
	//m_effect = EffectManager().LoadEffect("Assets/Shader/sprite.fx");
	m_effect = g_effectManager->LoadEffect("Assets/Shader/sprite.fx");
	static SShapeVertex_PT vertex[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	static unsigned short index[] = {
		0,1,2,3
	};
	m_spritePrimitive->Create(
		Primitive::EType::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vertex,
		4,
		D3DFMT_INDEX16,
		index
	);
	m_texture = texture;
	m_size.x = (float)m_texture->GetWidth();
	m_size.y = (float)m_texture->GetHeight();
}

void Sprite::Draw()
{
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	D3DXVECTOR3 scale;
	int frameBufferW = FRAME_BUFFER_WIDTH;
	int frameBufferH = FRAME_BUFFER_HEIGHT;
	int frameBufferHalfW = frameBufferW / 2;
	int framebufferHalfH = frameBufferH / 2;
	scale.x = m_size.x / frameBufferW;
	scale.y = m_size.y / frameBufferH;
	scale.z = 1.0f;
	D3DXMatrixScaling(&mWorld, scale.x, scale.y, scale.z);
	//mWorld.MakeScaling(sca;le);
	D3DXMATRIX mTrans;
	D3DXMatrixIdentity(&mTrans);
	D3DXVECTOR3 trans;
	trans.x = m_pos.x / frameBufferHalfW;
	trans.y = m_pos.y / framebufferHalfH;
	trans.z = 0.0f;
	//ピボットの分のオフセットを計算。
	D3DXVECTOR3 pivotOffset;
	pivotOffset.x = (m_size.x * (0.5f - m_pivot.x)) / frameBufferHalfW;
	pivotOffset.y = (m_size.y * (0.5f - m_pivot.y)) / framebufferHalfH;
	pivotOffset.z = 0.0f;
	D3DXVec3Add(&trans, &trans, &pivotOffset);
	//trans.Add(pivotOffset);

	//mTrans.MakeTranslation(trans);
	D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);
	D3DXMATRIX mRot;
	//mRot.MakeRotationFromQuaternion(m_rotation);
	D3DXMatrixRotationQuaternion(&mRot, &m_rotation);
	//mWorld.Mul(mRot, mWorld);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mRot);
	//mWorld.Mul(mWorld, mTrans);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mTrans);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_effect->BeginPass(0);
	m_effect->SetTechnique(/*g_pd3dDevice, */"SpriteTexture");
	m_effect->SetValue(/*g_pd3dDevice,*/ "mWorld", &mWorld, sizeof(mWorld));
	m_effect->SetTexture(/*g_pd3dDevice, */"g_tex", m_texture->GetTextureDX());
	m_effect->SetValue(/*g_pd3dDevice,*/ "uvRect", &m_uvRect, sizeof(m_uvRect));
	m_effect->SetValue(/*g_pd3dDevice,*/ "alpha", &m_alpha, sizeof(m_alpha));
	m_effect->CommitChanges(/*g_pd3dDevice*/);
	g_pd3dDevice->SetVertexDeclaration(m_spritePrimitive->GetVertexDecl());
	g_pd3dDevice->SetStreamSource(0, m_spritePrimitive->GetVertexBuffer()->GetBody(), 0, m_spritePrimitive->GetVertexBuffer()->GetStride());
	g_pd3dDevice->SetIndices(m_spritePrimitive->GetIndexBuffer()->GetBody());
	g_pd3dDevice->DrawIndexedPrimitive(
		m_spritePrimitive->GetD3DPrimitiveType(),
		0,
		0,
		m_spritePrimitive->GetNumVertex(),
		0,
		m_spritePrimitive->GetNumPolygon()
	);
	m_effect->EndPass();
	m_effect->End();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
//void Sprite::Initialize(LPCTSTR modelName,D3DXVECTOR2 position)
//{
//	D3DXIMAGE_INFO imgInfo;
//	D3DXCreateTextureFromFileEx(g_pd3dDevice, modelName, 0, 0, 0, 0, /*D3DFMT_A8R8G8B8*/D3DFMT_UNKNOWN,
//		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, /*D3DCOLOR_ARGB(255,255, 255, 255)*//*0xff000000*/NULL, &imgInfo, NULL, &m_pTexture);
//	this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);
//	RECT rec = { 0,0,imgInfo.Width,imgInfo.Height };
//	memcpy(&m_rect, &rec, sizeof(RECT));
//
//}
//
//void Sprite::SetupMatrices()
//{
//
//	/*D3DXMatrixIdentity(&m_transformMatrix);
//	D3DXMatrixTransformation2D(&m_transformMatrix, NULL, 0.0f, &m_scale, NULL, D3DXToRadian(m_angle), &m_position);
//*/
//}
//
//void Sprite::Draw(LPD3DXSPRITE pSprite)
//{
//	D3DXMatrixIdentity(&m_transformMatrix);
//	D3DXMatrixTransformation2D(&m_transformMatrix, NULL, 0.0f, &m_scale, NULL, D3DXToRadian(m_angle), &m_position);
//
//	//m_Sprite = pSprite;
//	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
//	pSprite->SetTransform(&m_transformMatrix);
//	pSprite->Draw(m_pTexture, &m_rect, &D3DXVECTOR3(m_texCenter.x, m_texCenter.y, 0.0f), NULL, m_backColor);//テクスチャの位置
//	pSprite->End();
//
//}