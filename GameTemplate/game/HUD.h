#pragma once
#include "myEngine\Graphics\Sprite.h"

class HUD :public Sprite
{
public:
	HUD();
	~HUD();
	void Initialize(LPCTSTR modelName,D3DXVECTOR2 position,int Alfa)override;
	void Update()override;
};

