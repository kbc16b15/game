#pragma once
#include "MapObject.h"
class MoveCube :public MapObject
{
public:
	//コンストラクタ
	MoveCube(int Dir,D3DXVECTOR3 limitpos);
	//デストラクタ
	~MoveCube();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新
	void Update()override;
	//描画
	void Draw();

	void SetDownflg(bool down)
	{
		Downflg = down;
	}

	//進行方向
	enum MOVEDIR
	{
		FORWARD,
		LEFT,
		RIGHT,
		BACK,
		DOWN,
		UP
	};
private:
	bool				Downflg = false;		//床が落ち始めるフラグ
	int					MoveDir = FORWARD;		//進む方向
	D3DXVECTOR3			Limitpos;				//移動上限値
	D3DXVECTOR3			Spos;					//初期座標
	SkinModel			model;					//スキンモデル
	SkinModelData		modelData;				//スキンモデルデータ
	D3DXVECTOR3			position;				//座標
	D3DXQUATERNION		rotation;				//回転
	Light				light;					//ライト
	MeshCollider		meshCollider;			//メッシュコライダー
	RigidBody			rigidBody;				//剛体。
	RigidBodyInfo		rbInfo;					//剛体情報
};

