#pragma once
#include "MapObject.h"
class HealItem :public MapObject
{
public:
	//�R���X�g���N�^
	HealItem();
	//�f�X�g���N�^
	~HealItem();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�`��̖�����ݒ�

	bool GetHeal()
	{
		return Healflg;
	}

private:
	SkinModel			model;							//�X�L�����f��
	SkinModelData		modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			position;						//���W
	D3DXQUATERNION		rotation;						//��]
	Light				light;							//���C�g
	MeshCollider		meshCollider;					//���b�V���R���C�_�[
	RigidBody			rigidBody;						//���́B
	RigidBodyInfo		rbInfo;							//���̏��
	bool				Healflg = false;				//�񕜃A�C�e���̓���
};

