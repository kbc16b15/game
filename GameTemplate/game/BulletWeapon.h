#pragma once
#include "IGameObject.h"
#include "myEngine/Physics/CharacterController.h"

class BulletWeapon :
	public IGameObject
{
public:
	//コンストラクタ
	BulletWeapon();
	//デストラクタ
	~BulletWeapon();
	//初期化　座標の設定
	void Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//更新
	void Update();
	//描画
	void Draw();
	//	BulletWeaponの死亡処理
	void Dead();
	//	BulletWeaponの移動処理
	void Move();
	//	BulletWeaponの死亡フラグの取得
	bool GetDeathflg()
	{
		return m_isDeath;
	}

private:
	enum BulletWeaponState
	{
		STAND,
		BULLET,
		DEAD
	};

	BulletWeaponState	m_bulletWeaponState = STAND;//敵の状態
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_scale;				//拡大
	D3DXQUATERNION		m_rotation;				//回転
	Light				m_light;				//ライト
	int					m_bulletIntervalTime = 20;	//バレットの発射間隔
	bool				m_isDead = false;		//死亡処理フラグ
	bool				m_isDeath = false;		//死亡フラグ
	bool				m_isPlayerBulletCamera = false;//バレットカメラ
	bool				m_isPlayerBullet = false;
	int					m_deadTime = 100;		//死亡タイム
	int					m_bulletDir = 0;		//バレット打つ方向
	//CharacterController	m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_moveSpeed;			//移動速度
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
	D3DXVECTOR3			m_direction;			//方向
	const float			m_enemySpeed = 1.2f;	//敵の速度
	const float			m_playerBulletLenge = 2.0f;	//バレットが打てる距離
	const float			m_standLenge = 2.0f;	//距離
	const float			m_charaRadius = 0.5f;	//キャラの半径
	const float			m_charaHeight = 0.5f;	//キャラの高さ
	const float			m_beamVolume = 0.4f;	//ビーム音量
	const int			m_maxBulletTime = 60;	//最大死亡タイム


};

