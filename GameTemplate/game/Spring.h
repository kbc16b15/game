#pragma once
#include "MapObject.h"
class Spring :
	public MapObject
{
public:
	Spring();
	~Spring();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//更新
	void Update();
	//描画
	void Draw();

	bool Getmaxdown()
	{
		return m_maxDownflg;
	}
	//描画の無効を設定
	//Rendflg　描画フラグ
	//bool Rend(bool Rendflg);

private:
	SkinModel			model;					//スキンモデル
	SkinModelData		modelData;				//スキンモデルデータ
	Light				light;					//ライト
	MeshCollider		meshCollider;			//メッシュコライダー
	RigidBody			rigidBody;				//剛体。
	RigidBodyInfo		rbInfo;					//剛体情報
	D3DXVECTOR3			position;				//座標
	D3DXQUATERNION		rotation;				//回転
	D3DXVECTOR3			scale;					//拡大
	bool				Sflg = false;			//範囲フラグ
	bool				m_maxDownflg = false;	//ボタン
	//float				SpringSpeed=10.0f;		//バネ速度
	const float			length = 3.0f;			//ひきつける範囲
};

