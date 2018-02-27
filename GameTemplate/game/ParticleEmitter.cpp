#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"

//using namespace std;

ParticleEmitter::ParticleEmitter()
{
}


ParticleEmitter::~ParticleEmitter()
{

	for (auto particleListnum : m_particleList)//消去ー
	{
		delete particleListnum;

	}
	auto particleListIt = m_particleList.begin();
	while (particleListIt != m_particleList.end()) {
			
			particleListIt = m_particleList.erase(particleListIt);
		
	}

	
}

void ParticleEmitter::Init(const SParticleEmitParameter& param)
{
	this->m_param = param;
	m_timer = 0.0f;
}

void ParticleEmitter::Update()
{
	
	if (m_timer >= m_param.intervalTime) {//一定時間経過したら
		//パーティクルを生成
		Particle* p = new Particle;
		p->Init(m_param);
		m_timer = 0.0f;
		m_particleList.push_back(p);

	}

	
	for (auto particleListnum : m_particleList)
	{
		if (particleListnum->GetDead())
		{
			delete particleListnum;
		}
	}

	auto particleListIt = m_particleList.begin();
	while (particleListIt != m_particleList.end()) {
		if ((*particleListIt)->GetDead()){
			
			//delete &particleListIt;
			particleListIt = m_particleList.erase(particleListIt);
			
		}
		else {
			particleListIt++;
		}
	}

	//auto func = [](Particle* particle)->bool {//匿名関数。
	//	if (particle->GetDead()) {
	//		return true;
	//	}
	//	return false;
	//};

	/*m_particleList.erase(
	remove_if(m_particleList.begin(), m_particleList.end(), func),
	m_particleList.end());*/

	//プレイヤーに回復パーティクル？

	m_timer += 1.0f / 60.0f;
	m_deleteTimer += 1.0f / 60.0f;
	for (auto p : m_particleList)
	{
		p->Update();
	}
}

void ParticleEmitter::HudDraw(/*const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix*/)
{
	for (auto p : m_particleList)
	{
		//p->Draw(viewMatrix, projMatrix);
		p->HudDraw();
	}
}