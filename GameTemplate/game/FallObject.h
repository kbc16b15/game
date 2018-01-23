#pragma once
#include "MapObject.h"
class FallObject:public MapObject
{
public:
	FallObject(int sType);
	~FallObject();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return position;
	}

	/*void SetSpeedflg(bool addflg)
	{
		m_addflg = addflg;
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

	D3DXVECTOR3		firstpos;			//�������W
	SkinModel		model;				//�X�L�����f��
	SkinModelData	modelData;			//�X�L�����f���f�[�^
	D3DXVECTOR3		position;			//���W
	D3DXQUATERNION	rotation;			//��]
	Light			light;				//���C�g
	MeshCollider	meshCollider;		//���b�V���R���C�_�[
	RigidBody		rigidBody;			//���́B
	RigidBodyInfo	rbInfo;				//���̏��
	D3DXVECTOR3		RotDir;				//��]����
	D3DXVECTOR3		RotSpeed;			//��]���x
	float			angle = 0.0f;		//�p�x
	const float		m_addSpeed = 0.5f;	//���x�ɂ���H
	//bool			m_addflg = false;
	//const float		m_subSpeed = 0.05f;	//���Y���x�ɂ���H

};

