#pragma once
#include "MapObject.h"
class MoveObject :public MapObject
{
public:
	//コンストラクタ
	MoveObject();
	//デストラクタ
	~MoveObject();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新
	void Update();
	//描画
	void Draw();

	/*void SetMState(int mstate)
	{
		MState = mstate;
	}*/
	//座標の取得
	D3DXVECTOR3 Getpos()
	{
		return position;

	}
	//オブジェクトに乗っているフラグ
	bool GetRide()
	{
		return Rideflg;
	}


private:
	SkinModel		model;						//スキンモデル
	SkinModelData	modelData;					//スキンモデルデータ
	D3DXVECTOR3		position;					//座標
	D3DXQUATERNION	rotation;					//回転
	Light			light;						//ライト
	MeshCollider	meshCollider;				//メッシュコライダー
	RigidBody		rigidBody;					//剛体。
	RigidBodyInfo	rbInfo;						//剛体情報
	CharacterController	characterController;	//キャラクターコントローラー
	D3DXVECTOR3		UMovelenge = position;
	D3DXVECTOR3		LMovelenge = position;
	D3DXVECTOR3		RMovelenge = position;
	D3DXVECTOR3		DMovelenge = position;
	bool			Render = false;				//描画フラグ
	bool			Rideflg = false;			//乗った時のフラグ

	bool Rflg = false;
	bool Lflg = false;
	bool Uflg = false;
	bool Dflg = false;

	const float PAddSpeed = 1.2f;
	const float MoveSpeed = 0.02f;
};

