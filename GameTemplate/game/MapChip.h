#pragma once
//#include "IGameObject.h"
#include "MapObject.h"
class MapChip :public MapObject
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
	//Rendflg�@�`��t���O
	//bool Rend(bool Rendflg);

private:
	//MapObject*			mapObject;
	SkinModel			m_model;					//�X�L�����f��
	SkinModelData		m_modelData;				//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;				//���W
	D3DXQUATERNION		m_rotation;				//��]
	Light				m_light;					//���C�g
	MeshCollider		m_meshCollider;			//���b�V���R���C�_�[
	//CapsuleCollider	capsuleCollider;		//�J�v�Z���R���C�_�[
	RigidBody			m_rigidBody;				//���́B
	RigidBodyInfo		m_rbInfo;					//���̏��
	//bool				Render = false;			//�`��t���O

};

