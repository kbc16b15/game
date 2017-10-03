#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
class GoalObject
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
	//描画の無効を設定

private:
	SkinModel			model;							//スキンモデル
	SkinModelData		modelData;						//スキンモデルデータ
	D3DXVECTOR3			position;						//座標
	D3DXQUATERNION		rotation;						//回転
	Light				light;							//ライト
	MeshCollider		meshCollider;					//メッシュコライダー
	RigidBody			rigidBody;						//剛体。
	RigidBodyInfo		rbInfo;							//剛体情報
	CharacterController	characterController;			//キャラクターコントローラー
};

