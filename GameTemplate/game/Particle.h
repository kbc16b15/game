#pragma once
#include "Primitive.h"
#include <d3dx9effect.h>

struct SParticleEmitParameter;


//�p�[�e�B�N��
class Particle{
	Primitive		primitive;
	LPDIRECT3DTEXTURE9 texture;
	ID3DXEffect* shaderEffect;
	D3DXVECTOR3 moveSpeed;
	D3DXVECTOR3 position;
	int time=40;
public:
	//�R���X�g���N�^
	Particle();
	//�f�X�g���N�^
	~Particle();
	void Init(const SParticleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix,const D3DXMATRIX& projMatrix);

	int gettime()
	{
		return time;
	}
};


