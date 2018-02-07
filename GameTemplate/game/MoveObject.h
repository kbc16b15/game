#pragma once
#include "MapObject.h"
class MoveObject :public MapObject
{
public:
	//コンストラクタ
	//MoveObject();
	//デストラクタ
	//~MoveObject();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot) override;
	//更新
	void Update() override;
	//座標の取得
	D3DXVECTOR3 Getpos()
	{
		return m_position;

	}
	//オブジェクトに乗っているフラグ
	/*bool GetRide()
	{
		return Rideflg;
	}*/


private:
	bool			m_open1 = false;			//ひらくか否か
	const float	length = 5.0f;//開く範囲
	const float m_maxUp = 30.0f;
	const float m_upSpeed = 0.02f;
};

