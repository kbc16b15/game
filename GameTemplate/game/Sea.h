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
	SkinModel			model;							//�X�L�����f��
	SkinModelData		modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			position;						//���W
	D3DXQUATERNION		rotation;						//��]
	Light				light;							//���C�g
	//LPDIRECT3DCUBETEXTURE9 m_cubeTex = nullptr;			//!<�L���[�u�e�N�X�`���B
	//LPDIRECT3DTEXTURE9	normalMap = NULL;				//�@���}�b�v�B

};

