#pragma once
#include "MapObject.h"
#include "ParticleEmitter.h"
class GoalObject :public MapObject
{
public:
	//�R���X�g���N�^
	//GoalObject();
	//�f�X�g���N�^
	~GoalObject();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation) override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

private:
	ParticleEmitter*	m_particleEmitter;	//�p�[�e�B�N��
	bool				m_isGoal = false;
};

