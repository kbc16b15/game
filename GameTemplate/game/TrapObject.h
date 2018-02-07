#pragma once
#include "MapObject.h"
class TrapObject :public MapObject
{
public:
	//TrapObject(/*D3DXVECTOR3 RDir*/);
	//~TrapObject();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation) override;
	//更新
	void Update() override;
	//回転
	void Rot();

private:
	D3DXVECTOR3		m_rotDir;					//回転方向
	const float		m_rotSpeed=0.04f;		//回転速度
	float			m_angle = 0.0f;			//角度
	bool			m_rotflg = false;
};