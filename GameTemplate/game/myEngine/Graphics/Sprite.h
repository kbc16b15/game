#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();
	virtual void Initialize(LPCTSTR modelName,D3DXVECTOR2 position);
	virtual void Update() = 0;
	void Draw(LPD3DXSPRITE);
	void SetupMatrices();
protected:
	D3DXVECTOR2 m_position;
	float m_angle;
	D3DXVECTOR2 m_scale;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DCOLOR m_backColor;
	LPCTSTR m_texFileName;
	D3DXVECTOR2 m_texCenter;
	RECT m_rect;
	D3DXMATRIX m_transformMatrix;
};