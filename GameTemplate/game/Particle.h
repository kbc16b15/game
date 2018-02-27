#pragma once
#include "Primitive.h"
#include <d3dx9effect.h>

struct SParticleEmitParameter;

//パーティクル
class Particle:public IGameObject
{
	Primitive	m_primitive;
	LPDIRECT3DTEXTURE9 m_texture;
	ID3DXEffect* m_shaderEffect;
	D3DXVECTOR3 m_moveSpeed;
	D3DXVECTOR3 m_position;
	bool		m_isDead = false;
	float		m_life=0.6f;
public:
	//コンストラクタ
	Particle();
	//デストラクタ
	~Particle();
	void Init(const SParticleEmitParameter& param);
	void Update();
	void HudDraw(/*const D3DXMATRIX& viewMatrix,const D3DXMATRIX& projMatrix*/);
	bool GetDead()
	{
		return m_isDead;
	}
};


