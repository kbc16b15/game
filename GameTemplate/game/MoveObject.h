#pragma once
#include "MapObject.h"
class MoveObject :public MapObject
{
public:
	//�R���X�g���N�^
	//MoveObject();
	//�f�X�g���N�^
	//~MoveObject();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot) override;
	//�X�V
	void Update() override;
	//���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return m_position;

	}
	//�I�u�W�F�N�g�ɏ���Ă���t���O
	/*bool GetRide()
	{
		return Rideflg;
	}*/


private:
	bool			m_open1 = false;			//�Ђ炭���ۂ�
	const float	length = 5.0f;//�J���͈�
	const float m_maxUp = 30.0f;
	const float m_upSpeed = 0.02f;
};

