#pragma once
#include "MapObject.h"
class TrapObject :public MapObject
{
public:
	//TrapObject(/*D3DXVECTOR3 RDir*/);
	//~TrapObject();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation) override;
	//�X�V
	void Update() override;
	//��]
	void Rot();

private:
	D3DXVECTOR3		m_rotDir;					//��]����
	const float		m_rotSpeed=0.04f;		//��]���x
	float			m_angle = 0.0f;			//�p�x
	bool			m_rotflg = false;
};