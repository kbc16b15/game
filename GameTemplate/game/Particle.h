#pragma once
#include "Primitive.h"
#include <d3dx9effect.h>

struct SParticleEmitParameter;


//パーティクル
class Particle{
	Primitive		primitive;
	/*static */LPDIRECT3DTEXTURE9 texture;
	ID3DXEffect* shaderEffect;
	D3DXVECTOR3 moveSpeed;
	D3DXVECTOR3 position;
	int time=40;
	//HRESULT hr;
public:
	//コンストラクタ
	Particle();
	//デストラクタ
	~Particle();
	void Init(const SParticleEmitParameter& param);
	void Update();
	//void Update(D3DXVECTOR3 pos);
	void Render(const D3DXMATRIX& viewMatrix,const D3DXMATRIX& projMatrix);

	int gettime()
	{
		return time;
	}
};


