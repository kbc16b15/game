#pragma once
#include "MapObject.h"
class GravityObject :
	public MapObject
{
public:
	GravityObject();
	~GravityObject();

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
	//Rendflg　描画フラグ
	//bool Rend(bool Rendflg);

private:
	SkinModel			model;					//スキンモデル
	SkinModelData		modelData;				//スキンモデルデータ
	D3DXVECTOR3			position;				//座標
	D3DXQUATERNION		rotation;				//回転
	Light				light;					//ライト
	MeshCollider		meshCollider;			//メッシュコライダー
	RigidBody			rigidBody;				//剛体。
	RigidBodyInfo		rbInfo;					//剛体情報
	bool				Gflg = false;			//範囲フラグ
	float				SpringSpeed = 10.0f;	//バネ速度
	const float			length = 1.0f;			//範囲
	int					GravityTime = 0;		//反転時間
	CharacterController	characterController;	//キャラクターコントローラー
};

