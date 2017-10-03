#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
//#include "IGameObject.h";
class MapChip/*:public IGameObject*/
{
public:
	//コンストラクタ
	MapChip();
	//デストラクタ
	~MapChip();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//更新
	void Update();
	//描画
	void Draw();
	//描画の無効を設定
	//Resndflg　描画フラグ
	//bool Rend(bool Rendflg);


private:
	/*enum MapObjectState 
	{
		Normal,
		Move,

	};

	int MState = Normal;*/
	SkinModel			model;							//スキンモデル
	SkinModelData		modelData;						//スキンモデルデータ
	D3DXVECTOR3			position;						//座標
	D3DXQUATERNION		rotation;						//回転
	Light				light;							//ライト
	MeshCollider		meshCollider;					//メッシュコライダー
	//CapsuleCollider	capsuleCollider;				//カプセルコライダー
	RigidBody			rigidBody;						//剛体。
	RigidBodyInfo		rbInfo;							//剛体情報
	CharacterController	characterController;			//キャラクターコントローラー
	//bool				Render = false;					//描画フラグ

};

