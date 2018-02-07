#pragma once
#include "MapObject.h"
#include "Sound.h"
class HealItem :public MapObject
{
public:
	//コンストラクタ
	//HealItem();
	//デストラクタ
	//~HealItem();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation) override;
	//更新
	void Update() override;
	//描画
	//void Draw();
	//描画の無効を設定

	bool GetHeal()
	{
		return m_healflg;
	}

private:
	bool				m_healflg = false;				//回復アイテムの入手
	Sound*				m_healSound = nullptr;
};

