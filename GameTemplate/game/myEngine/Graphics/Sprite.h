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
	//������
	void Init(Texture* texture);
	//�e�N�X�`���̐ݒ�
	void SetTexture(Texture* texture)
	{
		m_texture = texture;
	}
	//���W�ݒ�
	void SetPosition(const D3DXVECTOR2& pos)
	{
		m_pos = pos;
	}
	//�摜�̈ʒu�̐ݒ�
	const D3DXVECTOR2 GetPosition() const
	{
		return m_pos;
	}
	//�T�C�Y�̐ݒ�
	void SetSize(const D3DXVECTOR2& size)
	{
		m_size = size;
	}
	//�T�C�Y�̎擾
	const D3DXVECTOR2& GetSize() const
	{
		return m_size;
	}
	//�s�|�b�g�̐ݒ�
	void SetPivot(const D3DXVECTOR2& pivot)
	{
		m_pivot = pivot;
	}
	void SetRotation(D3DXQUATERNION rot)
	{
		m_rotation = rot;
	}
	//�`�悷��UV���W�̋�`��ݒ�
	void SetUVRect(const D3DXVECTOR4& uvRect)
	{
		m_uvRect = uvRect;
	}
	//�`��
	void Draw();
	//�s�����x��ݒ�
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}
	//�s�����x���擾
	float GetAlpha() const
	{
		return m_alpha;
	}
private:
	LPD3DXEFFECT	m_effect = nullptr;			//�G�t�F�N�g�B
	Primitive*		m_spritePrimitive;			//�v���~�e�B�u�B
	Texture*		m_texture = nullptr;		//�e�N�X�`���B
	D3DXVECTOR2		m_pos = { 0.0f, 0.0f };		//���W�B
	D3DXVECTOR2		m_size = { 0.0f, 0.0f };	//�X�v���C�g�̃T�C�Y�B
	D3DXVECTOR2		m_pivot = { 0.5f, 0.5f };	//�s�{�b�g
	D3DXVECTOR4		m_uvRect = { 0.0f, 0.0f, 1.0f, 1.0f };	//UV���W�B
	D3DXQUATERNION	m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	float			m_alpha = 1.0f;				//�s�����x�B
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