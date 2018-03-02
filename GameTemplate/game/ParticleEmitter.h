#pragma once
class Particle;

//パーティクルのパラメーター
struct SParticleEmitParameter
{
	void Init()
	{
		memset(this, 0, sizeof(SParticleEmitParameter));
	}
	const char* texturePath;
	float w;
	float h;
	float intervalTime;
	float lifeTime;
	float Multipos;
	D3DXVECTOR3 Multispeed;;
	//D3DXVECTOR3 random;
	D3DXVECTOR3 initSpeed;
	D3DXVECTOR3 position;
};

//パーティクルの発生器
class ParticleEmitter:public IGameObject
{
public:
	//コンストラクタ
	ParticleEmitter();
	//デストラクタ
	~ParticleEmitter();

	void Init(const SParticleEmitParameter& param);
	void Update();
	void HudDraw(/*const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix*/);
	void SetPos(D3DXVECTOR3 pos)
	{
		m_param.position = pos;
	}
private:
	SParticleEmitParameter	m_param;
	std::list<Particle*>	m_particleList;
	float					m_timer;
	float					m_deleteTimer;
};

