#pragma once
#include "myEngine/Physics/CharacterController.h"
#include "ParticleEmitter.h"
class BossEnemy:public IGameObject
{
public:

	~BossEnemy();
	//初期化　座標の設定
	void Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//更新
	void Update();
	//描画
	void HudDraw();
	//描画
	void Draw();
	//開始
	void StartState();
	//Enemyの死亡処理
	void Dead();
	//ダメージ
	void Damege();
	//攻撃
	void Attack();
	//回転
	void rot();
	//Enemyの移動処理
	void Stand();
	//Enemyの死亡フラグの取得
	bool GetDeathflg()
	{
		return m_isDeath;
	}
	//座標の取得
	D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
	}

	//ダメージ通知
	void SetDamage()
	{
		if (m_damageTime > 0) { return; }
		m_isDamageflg = true;
	}

	//インスタンスの生成
	static void BossEnemy::Create()
	{
		if (!m_bossEnemy)
		{
			m_bossEnemy = new BossEnemy;
		}

	}

	//インスタンスの消去
	static  void BossEnemy::Destroy()
	{
		delete m_bossEnemy;
		m_bossEnemy = nullptr;
	}
	//インスタンスの取得
	static BossEnemy& GetInstance()
	{
		return *m_bossEnemy;
		
		
	}
private:
	BossEnemy();
	static BossEnemy* m_bossEnemy;
	enum BossEnemyState
	{
		START,
		STAND,
		ROT,
		ATTACK,
		DEAD
	};

	BossEnemyState		m_bossState = START;
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_middlePosition;		//ボスの中心座標
	D3DXVECTOR3			m_sPos;					//初期座標
	D3DXVECTOR3			m_targetPos;			//目的座標
	D3DXVECTOR3			m_scale;				//拡大
	D3DXQUATERNION		m_rotation;				//回転
	Light				m_light;				//ライト
	const float			m_charaRadius = 2.5f;	//キャラの半径
	int					m_bulletTime = 10;		//バレットの発射間隔
	const int			m_bulletMaxTime = 10;	//バレットの最大発射間隔
	//bool				m_isDead = false;		//死亡処理フラグ
	bool				m_isDeath = false;		//死亡フラグ
	int					m_deadTime = 500;		//死亡タイム
	int					m_bulletDir = 0;		//バレット打つ方向
	CharacterController	m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_moveSpeed;			//移動速度
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;	//スペキュラマップ
	D3DXVECTOR3			m_direction;			//方向
	int					m_standTime = 120;		//待機タイム
	const int			m_maxStandTime=120;		//最大待機タイム
	int					m_rotTime = 50;			//回転タイム
	const int			m_maxrotTime = 50;		//最大回転タイム
	int					m_attackTime=80;		//攻撃タイム
	const int			m_maxAttackTime = 80;	//最大攻撃タイム
	bool				m_isTarget = false;		//目標座標が決まった
	float				m_targetLen=0.0f;		//目標座標との距離
	float				m_stopAttackLen = 40.0f;//目標座標の距離
	int					m_startTime = 200;		//開始時間
	int					m_damageTime = 0;		//無敵時間
	int					m_damageMaxTime = 200;	//最大無敵時間
	bool				m_isDamageflg = false;	//ダメージフラグ
	bool				m_isAddParticle=false;	//パーティクルフラグ
	float				m_soundBreakTime = 0.6f;//撃破サウンドの間隔
	const float			m_soundBreakMaxTime = 0.6f;//撃破サウンドの最大間隔
	ParticleEmitter*	m_particleEmitter;	//パーティクル
};