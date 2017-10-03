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
	void Initialize(LPCTSTR modelName,D3DXVECTOR2 position)override;
	//更新
	void Update()override;

	float Getalfa()
	{
		return alfa;
	}

	void Setalfa(float a)
	{
		alfa = a;
	}

	/*void SetRGB(int R, int G, int B)
	{
		Red = R;
		Green = G;
		Blue = B;
	}*/
private:
	float alfa = 1.0f;
	float Red=1.0f;
	float Green=1.0f;
	float Blue=1.0f;
	//int alfa =255;
	//int Red = 255;
	//int Green = 255;
	//int Blue = 255;
};

