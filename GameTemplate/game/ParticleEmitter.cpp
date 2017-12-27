#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"

using namespace std;
ParticleEmitter::ParticleEmitter()
{
}


ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Init(const SParticleEmitParameter& param)
{
	this->param = param;
	timer = 0.0f;
}

void ParticleEmitter::Update()
{

	if (timer >= param.intervalTime) {//一定時間経過したら
		//パーティクルを生成
		Particle* p =new Particle;
		p->Init(param);
		timer = 0.0f;
		particleList.push_back(p);
	}
	timer += 1.0f / 60.0f;
	for (auto p : particleList) {
		p->Update();
	}
}

void ParticleEmitter::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	for (auto p : particleList)
	{
		p->Render(viewMatrix, projMatrix);
	}
}