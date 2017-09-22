#pragma once
#include "myEngine\Graphics\Sprite.h"

class HUD :public Sprite
{
public:
	//コンストラクタ
	HUD();
	//デストラクタ
	~HUD();
	//初期化
	//modelName	モデル名
	//position	座標
	//Alfa		透明度
	void Initialize(LPCTSTR modelName,D3DXVECTOR2 position,int Alfa)override;
	//更新
	void Update()override;
};

