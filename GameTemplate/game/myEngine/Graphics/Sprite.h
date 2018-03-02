#pragma once
//#include "Primitive.h"
//class Primitive;
//class Texture;
#include "Texture.h"
#include "Primitive.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	//初期化
	void Init(Texture* texture);
	//テクスチャの設定
	void SetTexture(Texture* texture)
	{
		m_texture = texture;
	}
	//座標設定
	void SetPosition(const D3DXVECTOR2& pos)
	{
		m_pos = pos;
	}
	//画像の位置の設定
	const D3DXVECTOR2 GetPosition() const
	{
		return m_pos;
	}
	//サイズの設定
	void SetSize(const D3DXVECTOR2& size)
	{
		m_size = size;
	}
	//サイズの取得
	const D3DXVECTOR2& GetSize() const
	{
		return m_size;
	}
	//ピポットの設定
	void SetPivot(const D3DXVECTOR2& pivot)
	{
		m_pivot = pivot;
	}
	void SetRotation(D3DXQUATERNION rot)
	{
		m_rotation = rot;
	}
	//描画するUV座標の矩形を設定
	void SetUVRect(const D3DXVECTOR4& uvRect)
	{
		m_uvRect = uvRect;
	}
	//描画
	void Draw();
	//不透明度を設定
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}
	//不透明度を取得
	float GetAlpha() const
	{
		return m_alpha;
	}
private:
	LPD3DXEFFECT	m_effect = nullptr;			//エフェクト。
	Primitive*		m_spritePrimitive;			//プリミティブ。
	Texture*		m_texture = nullptr;		//テクスチャ。
	D3DXVECTOR2		m_pos = { 0.0f, 0.0f };		//座標。
	D3DXVECTOR2		m_size = { 0.0f, 0.0f };	//スプライトのサイズ。
	D3DXVECTOR2		m_pivot = { 0.5f, 0.5f };	//ピボット
	D3DXVECTOR4		m_uvRect = { 0.0f, 0.0f, 1.0f, 1.0f };	//UV座標。
	D3DXQUATERNION	m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	float			m_alpha = 1.0f;				//不透明度。
	//void Draw();
//	virtual void Initialize(LPCTSTR modelName,D3DXVECTOR2 position);
//	virtual void Update() = 0;
//	void Draw(LPD3DXSPRITE);
//	void SetupMatrices();
//protected:
//	D3DXVECTOR2 m_position;
//	float m_angle;
//	D3DXVECTOR2 m_scale;
//	LPDIRECT3DTEXTURE9 m_pTexture;
//	D3DCOLOR m_backColor;
//	LPD3DXSPRITE m_Sprite;
//	LPCTSTR m_texFileName;
//	D3DXVECTOR2 m_texCenter;
//	RECT m_rect;
//	D3DXMATRIX m_transformMatrix;
};