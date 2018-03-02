#pragma once
#include "MapObject.h"
class FallObject:public MapObject
{
public:
	FallObject(int sType);
	//~FallObject();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation) override;
	//更新
	void Update() override;
	//座標の取得
	/*D3DXVECTOR3 Getpos()
	{
		return m_position;
	}*/
	/*void SetMove(bool isMove)
	{
		m_isMove = isMove;
	}*/
private:
	enum SpeedType {
		NONE,
		F,
		B,
		R,
		L
	};

	int m_speed=NONE;
	//bool m_isGround=false;
	//bool m_isMove = false;
	//D3DXVECTOR3		firstpos;			//初期座標
	D3DXVECTOR3		RotDir;				//回転方向
	D3DXVECTOR3		RotSpeed;			//回転速度
	float			angle = 0.0f;		//角度
	const float		m_addSpeed = 0.5f;	//速度

};

