#pragma once
#include "MapObject.h"
class BoxChip :
	public MapObject
{
public:
	//BoxChip();
	//~BoxChip();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION	rot) override;
	//�X�V
	//void Update();
	//�`��
	//void Draw();
private:
	BoxCollider			m_boxCollider;			//�{�b�N�X�R���C�_�[
//	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//�@���}�b�v
//
};

