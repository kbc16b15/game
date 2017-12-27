#pragma once
#include "MapObject.h"
class GoalObject :public MapObject
{
public:
	//コンストラクタ
	GoalObject();
	//デストラクタ
	~GoalObject();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//更新
	void Update();
	//描画
	void Draw();

private:
	SkinModel			m_model;			//スキンモデル
	SkinModelData		m_modelData;		//スキンモデルデータ
	D3DXVECTOR3			m_position;			//座標
	D3DXQUATERNION		m_rotation;			//回転
	Light				m_light;			//ライト
	MeshCollider		m_meshCollider;		//メッシュコライダー
	RigidBody			m_rigidBody;		//剛体。
	RigidBodyInfo		m_rbInfo;			//剛体情報
};

