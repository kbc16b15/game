#pragma once
#include "myEngine\Physics\ICollider.h"
class BoxCollider ://���b�p�[�N���X
	public ICollider
{
public:
	//�R���X�g���N�^
	BoxCollider();
	//�f�X�g���N�^
	~BoxCollider();
	//�{�b�N�X�̍쐬
	//halfSize �T�C�Y
	void Create(const D3DXVECTOR3& halfSize);
	//�{�b�N�X�̎擾
	btCollisionShape* GetBody() override
	{
		return m_boxShape;
	}
private:
	btBoxShape* m_boxShape=nullptr;//�{�b�N�X�R���C�_�[
};

