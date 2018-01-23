#pragma once
#include "MapObject.h"
class FallObject:public MapObject
{
public:
	FallObject(int sType);
	~FallObject();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新
	void Update();
	//描画
	void Draw();
	//座標の取得
	D3DXVECTOR3 Getpos()
	{
		return position;
	}

	/*void SetSpeedflg(bool addflg)
	{
		m_addflg = addflg;
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

	D3DXVECTOR3		firstpos;			//初期座標
	SkinModel		model;				//スキンモデル
	SkinModelData	modelData;			//スキンモデルデータ
	D3DXVECTOR3		position;			//座標
	D3DXQUATERNION	rotation;			//回転
	Light			light;				//ライト
	MeshCollider	meshCollider;		//メッシュコライダー
	RigidBody		rigidBody;			//剛体。
	RigidBodyInfo	rbInfo;				//剛体情報
	D3DXVECTOR3		RotDir;				//回転方向
	D3DXVECTOR3		RotSpeed;			//回転速度
	float			angle = 0.0f;		//角度
	const float		m_addSpeed = 0.5f;	//速度にする？
	//bool			m_addflg = false;
	//const float		m_subSpeed = 0.05f;	//減産速度にする？

};

