#pragma once
class CubeCollision
{
public:
	//�R���X�g���N�^
	CubeCollision();
	//�f�X�g���N�^
	~CubeCollision();
	//���Ƌ��̓����蔻��
	//p1	��ڂ̋��̍��W
	//p2	��ڂ̋��̍��W
	//r1	��ڂ̋��̔��a(�傫��)
	//r2	��ڂ̋��̔��a(�傫��)
	bool Cubemass(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float r1, float r2);

};

