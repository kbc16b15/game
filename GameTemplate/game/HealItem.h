#pragma once
#include "MapObject.h"
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
		return Healflg;
	}

private:
	SkinModel			model;							//スキンモデル
	SkinModelData		modelData;						//スキンモデルデータ
	D3DXVECTOR3			position;						//座標
	D3DXQUATERNION		rotation;						//回転
	Light				light;							//ライト
	MeshCollider		meshCollider;					//メッシュコライダー
	RigidBody			rigidBody;						//剛体。
	RigidBodyInfo		rbInfo;							//剛体情報
	bool				Healflg = false;				//回復アイテムの入手
};

