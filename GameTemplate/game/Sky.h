#pragma once
#include "MapObject.h"
class Sky:public MapObject
{
public:
	//�R���X�g���N�^
	Sky();
	//�f�X�g���N�^
	~Sky();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	////�X�V
	void Update();
	////�`��
	void Draw();

private:
	SkinModel				m_model;								//�X�L�����f��
	SkinModelData			m_modelData;							//�X�L�����f���f�[�^
	D3DXVECTOR3				m_position;								//���W
	D3DXQUATERNION			m_rotation = {0.0f,0.0f,0.0f,1.0f};		//��]
	Light					m_light;								//���C�g
	LPDIRECT3DCUBETEXTURE9	m_cubeTex = nullptr;				//!<�L���[�u�e�N�X�`���B
};

