#pragma once

#include "myEngine/Physics/CharacterController.h"

class trackingEnemy
{
public:
	//コンストラクタ
	trackingEnemy();
	//デストラクタ
	~trackingEnemy();
	//初期化　座標の設定
	void Start(D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新
	void Update();
	//描画
	void Draw();
	//Enemyの死亡処理
	void Dead();
	//Enemyの移動処理
	void Move();
	//Enemyの死亡フラグの取得
	bool GetDeathflg()
	{
		return m_isDeath;
	}

	/*D3DXMATRIX get()
	{
		return Transmat;
	}
	D3DXMATRIX rotget()
	{
		return rotmat;
	}

	bool Getparent()
	{
		return parent;
	}*/
	
private:
	enum TEnemyState
	{
		SEACH,
		FOUND,
		DEAD
	};
	/*D3DXMATRIX Transmat;
	D3DXMATRIX rotmat;*/
	//bool				parent = false;
	int TState = SEACH;
	SkinModel			m_skinModel;										//スキンモデル
	SkinModelData		m_skinModelData;									//スキンモデルデータ
	D3DXVECTOR3			m_position;											//座標
	D3DXVECTOR3			m_sPos;												//初期座標
	D3DXVECTOR3			m_scale = { 0.7f,0.7f,0.7f };						//拡大
	D3DXQUATERNION		m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);//回転
	Light				m_light;											//ライト
	int					m_bulletTime = 150;									//バレットの発射間隔
	bool				m_isDead = false;									//死亡処理フラグ
	bool				m_isDeath = false;									//死亡フラグ
	int					m_deadTime = 100;									//死亡タイム
	int					m_bulletDir = 0;									//バレット打つ方向
	CharacterController	m_characterController;								//キャラクターコントローラー
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };					//移動速度
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;									//法線マップ
	D3DXVECTOR3			m_direction = { 0.0f,0.0f,1.0f };
	bool				moveX = false;
	
};

