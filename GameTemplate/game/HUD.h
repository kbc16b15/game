#pragma once
#include "myEngine\Graphics\Sprite.h"

class HUD :public Sprite
{
public:
	//�R���X�g���N�^
	HUD();
	//�f�X�g���N�^
	~HUD();
	//������
	//modelName	���f����
	//position	���W
	//Alfa		�����x
	void Initialize(LPCTSTR modelName,D3DXVECTOR2 position,int Alfa)override;
	//�X�V
	void Update()override;
};

