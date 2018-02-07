#pragma once
#include "MapObject.h"
class Spring :
	public MapObject
{
public:
	//Spring();
	//~Spring();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rot	モデルの回転
	//void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//更新
	void Update() override;
	//描画
	//void Draw();

	//bool Getmaxdown()
	//{
	//	return m_maxDownflg;
	//}

private:
	bool				Sflg = false;			//範囲フラグ
	bool				m_maxDownflg = false;	//ボタン
	//float				SpringSpeed=10.0f;		//バネ速度
	const float			length = 3.0f;			//ひきつける範囲
};

