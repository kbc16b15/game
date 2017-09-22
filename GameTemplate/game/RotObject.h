#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
class RotObject
{
public:
	RotObject(D3DXVECTOR3 RDir,D3DXVECTOR3 RSpeed);
	~RotObject();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新
	void Update();
	//描画
	void Draw();
	//座標の取得
	D3DXVECTOR3 Getpos()
	{
		return position;
	}

private:
	SkinModel		model;					//スキンモデル
	SkinModelData	modelData;				//スキンモデルデータ
	D3DXVECTOR3		position;				//座標
	D3DXQUATERNION	Rotation;				//回転
	Light			light;					//ライト
	MeshCollider	meshCollider;			//メッシュコライダー
	RigidBody		rigidBody;				//剛体。
	RigidBodyInfo	rbInfo;					//剛体情報
	//CharacterController	characterController;//キャラクターコントローラー
	D3DXVECTOR3		RotDir;					//回転方向
	D3DXVECTOR3		RotSpeed;				//回転速度
	float angle = 0.0f;						//角度
	bool Tflg = false;						//プレイヤーとのフラグ
};

