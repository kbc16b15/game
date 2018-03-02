#pragma once
#include "MapObject.h"
#include "Sound.h"
class HealItem :public MapObject
{
public:
	//�R���X�g���N�^
	//HealItem();
	//�f�X�g���N�^
	//~HealItem();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation) override;
	//�X�V
	void Update() override;
	//�`��
	//void Draw();
	//�`��̖�����ݒ�

	bool GetHeal()
	{
		return m_healflg;
	}

private:
	bool				m_healflg = false;				//�񕜃A�C�e���̓���
	Sound*				m_healSound = nullptr;
};

