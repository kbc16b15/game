#pragma once
#include "MapObject.h"
class Spring :
	public MapObject
{
public:
	//Spring();
	//~Spring();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rot	���f���̉�]
	//void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//�X�V
	void Update() override;
	//�`��
	//void Draw();

	//bool Getmaxdown()
	//{
	//	return m_maxDownflg;
	//}

private:
	bool				Sflg = false;			//�͈̓t���O
	bool				m_maxDownflg = false;	//�{�^��
	//float				SpringSpeed=10.0f;		//�o�l���x
	const float			length = 3.0f;			//�Ђ�����͈�
};

