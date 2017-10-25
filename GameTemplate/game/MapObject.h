#pragma once
class MapObject
{
public:
	//コンストラクタ
	MapObject();
	//デストラクタ
	virtual ~MapObject();
	//初期化
	//void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//基底クラスのアップデート
	virtual void Update()=0;
	//基底クラスのドロウ
	virtual void Draw()=0;
//private:
//	SkinModel			model;							//スキンモデル
//	SkinModelData		modelData;						//スキンモデルデータ
//	D3DXVECTOR3			position;						//座標
//	D3DXQUATERNION		rotation;						//回転
//	Light				light;							//ライト
//	MeshCollider		meshCollider;					//メッシュコライダー
//	RigidBody			rigidBody;						//剛体。
//	RigidBodyInfo		rbInfo;							//剛体情報
};

