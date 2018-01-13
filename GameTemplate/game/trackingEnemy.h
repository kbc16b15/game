#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "Sound.h"
class trackingEnemy
{
public:
	//コンストラクタ
	trackingEnemy();
	//デストラクタ
	~trackingEnemy();
	//初期化　座標の設定
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot);
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

private:
	enum TEnemyState
	{
		SEACH,
		FOUND,
		DEAD
	};

	int TState = SEACH;
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_sPos;					//初期座標
	D3DXVECTOR3			m_scale;				//拡大
	D3DXQUATERNION		m_rotation;				//回転
	Light				m_light;				//ライト
	int					m_bulletTime = 60;		//バレットの発射間隔
	bool				m_isDead = false;		//死亡処理フラグ
	bool				m_isDeath = false;		//死亡フラグ
	int					m_deadTime = 100;		//死亡タイム
	int					m_bulletDir = 0;		//バレット打つ方向
	CharacterController	m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_moveSpeed;			//移動速度
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
	D3DXVECTOR3			m_direction;//方向
	bool				moveX = false;
	//Sound*				m_beamSound=nullptr;
	
};

