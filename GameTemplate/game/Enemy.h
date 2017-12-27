#pragma once

#include "myEngine/Physics/CharacterController.h"
//#include "IGameObject.h"

class Enemy/*:public IGameObject*/
{
public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	//初期化　座標の設定
	void Start(D3DXVECTOR3 pos);
	//更新
	void Update();
	//エネミーの移動の仕方
	void Move();
	//描画
	void Draw();
	//Enemyのバレットの発射タイミング
	void EnemyBullet();
	//Enemyの死亡処理
	void Dead();
	//Enemyの死亡フラグの取得
	bool GetDeathflg()
	{
		return m_isDeath;
	}
private:
	SkinModel			m_skinModel;											//スキンモデル
	SkinModelData		m_skinModelData;										//スキンモデルデータ
	D3DXVECTOR3			m_position = { -20.0f,0.0f,0.0f };					//座標
	D3DXVECTOR3			m_scale = { 0.5f,0.5f,0.5f };							//拡大
	D3DXQUATERNION		m_rotation= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//回転
	Light				m_light;												//ライト
	int					m_bulletTime = 150;									//バレットの発射間隔
	bool				m_isDead = false;										//死亡処理フラグ
	bool				m_isDeath = false;									//死亡フラグ
	int					m_deadTime = 100;										//死亡タイム
	int					m_dulletDir = 0;										//バレット打つ方向
	CharacterController	m_characterController;				//キャラクターコントローラー
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度
};

