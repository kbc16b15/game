#pragma once
#include "MapObject.h"
class FallObject:public MapObject
{
public:
	FallObject(int sType);
	//~FallObject();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation) override;
	//�X�V
	void Update() override;
	//���W�̎擾
	/*D3DXVECTOR3 Getpos()
	{
		return m_position;
	}*/
	/*void SetMove(bool isMove)
	{
		m_isMove = isMove;
	}*/
private:
	enum SpeedType {
		NONE,
		F,
		B,
		R,
		L
	};

	int m_speed=NONE;
	//bool m_isGround=false;
	//bool m_isMove = false;
	//D3DXVECTOR3		firstpos;			//�������W
	D3DXVECTOR3		RotDir;				//��]����
	D3DXVECTOR3		RotSpeed;			//��]���x
	float			angle = 0.0f;		//�p�x
	const float		m_addSpeed = 0.5f;	//���x

};

