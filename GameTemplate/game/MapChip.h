#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
//#include "IGameObject.h";
class MapChip/*:public IGameObject*/
{
public:
	//�R���X�g���N�^
	MapChip();
	//�f�X�g���N�^
	~MapChip();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�`��̖�����ݒ�
	//Resndflg�@�`��t���O
	//bool Rend(bool Rendflg);


private:
	/*enum MapObjectState 
	{
		Normal,
		Move,

	};

	int MState = Normal;*/
	SkinModel			model;							//�X�L�����f��
	SkinModelData		modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			position;						//���W
	D3DXQUATERNION		rotation;						//��]
	Light				light;							//���C�g
	MeshCollider		meshCollider;					//���b�V���R���C�_�[
	//CapsuleCollider	capsuleCollider;				//�J�v�Z���R���C�_�[
	RigidBody			rigidBody;						//���́B
	RigidBodyInfo		rbInfo;							//���̏��
	CharacterController	characterController;			//�L�����N�^�[�R���g���[���[
	//bool				Render = false;					//�`��t���O

};

