#pragma once
#include "IGameObject.h"
//#include "myEngine/Physics/CharacterController.h"
#include "Sound.h"
#include "ParticleEmitter.h"
class trackingEnemy:public IGameObject
{
public:
	//コンストラクタ
	trackingEnemy();
	//デストラクタ
	~trackingEnemy();
	//初期化　座標の設定
	void Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot);
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

	void  SetDeathflg(bool isDead)
	{
		m_isDead = isDead;
	}

	D3DXVECTOR3 GetPos()
	{
		return m_position;
	}

private:
	enum EnemyState
	{
		SEACH,
		FOUND,
		DEAD
	};

	EnemyState			m_trackingState = SEACH;//敵の状態
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_sPos;					//初期座標
	D3DXVECTOR3			m_scale;				//拡大
	D3DXQUATERNION		m_rotation;				//回転
	Light				m_light;				//ライト
	int					m_bulletIntervalTime = 60;//バレットの発射間隔
	bool				m_isDead = false;		//死亡処理フラグ
	bool				m_isDeath = false;		//死亡フラグ
	bool				m_isParticle = false;	//パーティクルフラグ
	int					m_deadTime = 100;		//死亡タイム
	int					m_bulletDir = 0;		//バレット打つ方向
	//CharacterController	m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_moveSpeed;			//移動速度
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
	D3DXVECTOR3			m_direction;			//方向
	const float			m_enemySpeed = 1.2f;	//敵の速度
	const float			m_foundLenge = 12.0f;	//発見距離
	const float			m_seachLenge = 12.5f;	//索敵距離
	const float			m_charaRadius = 0.5f;	//キャラの半径
	const float			m_charaHeight = 0.5f;	//キャラの高さ
	const float			m_beamVolume = 0.4f;	//ビーム音量
	const int			m_maxBulletTime = 60;	//最大死亡タイム
	Sound*				m_beamSound = nullptr;	//ビーム音
	ParticleEmitter*	m_particleEmitter;	//パーティクル
	
};

