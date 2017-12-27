#pragma once
//#include "IGameObject.h"
#include "MapObject.h"
class MapChip :public MapObject
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
	//Rendflg　描画フラグ
	//bool Rend(bool Rendflg);

private:
	//MapObject*			mapObject;
	SkinModel			m_model;					//スキンモデル
	SkinModelData		m_modelData;				//スキンモデルデータ
	D3DXVECTOR3			m_position;				//座標
	D3DXQUATERNION		m_rotation;				//回転
	Light				m_light;					//ライト
	MeshCollider		m_meshCollider;			//メッシュコライダー
	//CapsuleCollider	capsuleCollider;		//カプセルコライダー
	RigidBody			m_rigidBody;				//剛体。
	RigidBodyInfo		m_rbInfo;					//剛体情報
	//bool				Render = false;			//描画フラグ

};

