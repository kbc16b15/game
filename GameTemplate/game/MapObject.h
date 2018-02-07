#pragma once
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Physics/MeshCollider.h"
#include "BoxCollider.h"
#include "myEngine\Physics\RigidBody.h"
class MapObject
{
public:
	//コンストラクタ
	MapObject();
	//デストラクタ
	virtual ~MapObject();
	//基底クラスのイニット
	virtual void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//基底クラスのアップデート
	virtual void Update();
	//基底クラスのドロウ
	virtual void Draw();
	MapObject* MapReturn(const char* MapName);
	
protected:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	Light			m_light;			//ライト
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	D3DXVECTOR3		m_scale;			//拡大
	MeshCollider	m_meshCollider;		//メッシュコライダー
	RigidBody		m_rigidBody;		//剛体。
	RigidBodyInfo	m_rbInfo;			//剛体情報
};

