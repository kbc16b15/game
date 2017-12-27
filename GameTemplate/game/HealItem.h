#pragma once
#include "MapObject.h"
#include "Sound.h"
class HealItem :public MapObject
{
public:
	//コンストラクタ
	HealItem();
	//デストラクタ
	~HealItem();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//更新
	void Update();
	//描画
	void Draw();
	//描画の無効を設定

	bool GetHeal()
	{
		return m_healflg;
	}

private:
	SkinModel			m_model;							//スキンモデル
	SkinModelData		m_modelData;						//スキンモデルデータ
	D3DXVECTOR3			m_position;					//座標
	D3DXQUATERNION		m_rotation;					//回転
	Light				m_light;							//ライト
	MeshCollider		m_meshCollider;					//メッシュコライダー
	RigidBody			m_rigidBody;						//剛体。
	RigidBodyInfo		m_rbInfo;							//剛体情報
	bool				m_healflg = false;				//回復アイテムの入手
	Sound*				m_healSound = nullptr;
};

