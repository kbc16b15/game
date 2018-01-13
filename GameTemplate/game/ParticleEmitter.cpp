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

	if (timer >= param.intervalTime) {//��莞�Ԍo�߂�����
		//�p�[�e�B�N���𐶐�
		Particle* p = new Particle;
		p->Init(param);
		timer = 0.0f;
		particleList.push_back(p);


	}

	//if (p != nullptr) {
	//	delete p;//�p�[�e�B�N���̏���
	//	p = nullptr;
	//	deleteTime = 100.0f;
	//}	

	auto pIt = particleList.begin();
	for (auto pt : particleList) {
		if (pt->gettime() <= 0.0f)
		{
			delete pt;
			pIt = particleList.erase(pIt);
			deleteTimer = 0.0f;
			

		}
		else {
			pIt++;
		}
	}

	
	//while (pIt != particleList.end()) {
	//	if (deleteTimer >= param.deleteTime) {
	//		/*for (auto pt : particleList) {
	//			delete pt;
	//		}*/
	//		
	//	}
	//	
	//}
	timer += 1.0f / 60.0f;
	deleteTimer += 1.0f / 60.0f;
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