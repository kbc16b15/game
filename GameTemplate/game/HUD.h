#pragma once
#include "myEngine\Graphics\Sprite.h"

class HUD :public Sprite
{
public:
	HUD();
	~HUD();
	void Initialize()override;
	void Update()override;

	void Addpos(float pos)
	{
		Hppos.x += pos;
	}

private:
	D3DXVECTOR2 Hppos = { 120.0f,80.0f };
};

