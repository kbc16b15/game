#pragma once
class Particle;

//�p�[�e�B�N���̃p�����[�^�[
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
	D3DXVECTOR3 initSpeed;
	D3DXVECTOR3 position;
};

//�p�[�e�B�N���̔�����
class ParticleEmitter
{
public:
	//�R���X�g���N�^
	ParticleEmitter();
	//�f�X�g���N�^
	~ParticleEmitter();

	void Init(const SParticleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);
private:
	SParticleEmitParameter	param;
	std::list<Particle*>	particleList;
	float					timer;
	float					deleteTimer;
};

