#pragma once
#include "MapObject.h"
class TrapObject :public MapObject
{
public:
	TrapObject(int Damagetype,D3DXVECTOR3 RDir);
	~TrapObject();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新
	void Update();
	//描画
	void Draw();

	void Rot();
	//座標の取得
	D3DXVECTOR3 Getpos()
	{
		return m_position;
	}

	enum DamageObjectType {
		STAND,
		ROT,
		MOVE,
	};
private:
	int				m_damageType = STAND;
	SkinModel		m_model;					//スキンモデル
	SkinModelData	m_modelData;				//スキンモデルデータ
	D3DXVECTOR3		m_position;					//座標
	D3DXQUATERNION	m_rotation;					//回転
	D3DXVECTOR3		m_scale;					//拡大
	Light			m_light;					//ライト
	MeshCollider	m_meshCollider;			//メッシュコライダー
	RigidBody		m_rigidBody;				//剛体。
	RigidBodyInfo	m_rbInfo;					//剛体情報
	D3DXVECTOR3		m_rotDir;					//回転方向
	D3DXVECTOR3		m_totSpeed;				//回転速度
	float			m_angle = 0.0f;			//角度
	bool			m_rotflg = false;
};