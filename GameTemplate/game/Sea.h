#pragma once
#include "MapObject.h"
class Sea:public MapObject
{
public:
	//�R���X�g���N�^
	Sea();
	//�f�X�g���N�^
	~Sea();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();

private:
	SkinModel			m_model;							//�X�L�����f��
	SkinModelData		m_modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;						//���W
	D3DXQUATERNION		m_rotation;						//��]
	Light				m_light;							//���C�g
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;				//�@���}�b�v�B
	//LPDIRECT3DCUBETEXTURE9 m_cubeTex = nullptr;		//!<�L���[�u�e�N�X�`���B

};

