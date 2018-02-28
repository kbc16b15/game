#pragma once
#include "myEngine/Physics/CharacterController.h"
#include "Sound.h"
class Player:public IGameObject
{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void ShadowDraw(D3DXMATRIX* viewM, D3DXMATRIX* projM, bool shadowCaster, bool shadowRecive);
	//描画
	void Draw();
	//サウンド
	void PlayerSound();
	//アニメーション処理
	void AnimationSet();
	//移動処理
	void move();
	//移動キーの設定
	//void Key();
	//バレットの当たり処理
	void Hit();
	//キャラの向きの設定
	void Setangle();
	//キャラのジャンプの設定
	void Setjump();
	//キャラの慣性の設定
	void SetSubmove();

	void PlayerBullet();
	//プレイヤー座標の取得（足元？）
	const D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
	}
	//プレイヤー中心座標の取得
	const D3DXVECTOR3 GetMiddlepos()
	{
		return m_middlePosition;
	}
	//座標セット
	void Setpos(D3DXVECTOR3 pos)
	{
		m_characterController.SetPosition(pos);

	}
	//プレイヤーの移動速度を設定
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		m_characterController.SetMoveSpeed(addpos);
		m_characterController.Execute();

	}
	//プレイヤーの移動方向を設定
	void SetDir(int dir)
	{
		m_addDir = dir;
	}
	//プレイヤーの移動方向を取得
	int GetDir()
	{
		return m_addDir;
	}
	//プレイヤーの移動速度の取得
	const D3DXVECTOR3 GetSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}
	//ダメージ通知
	void SetDamage()
	{
		if (m_damageTime > 0) { return; }
		m_isDamageflg = true;
	}

	

	//移動しているかの取得
	const bool GetPlayerMove()
	{
		return m_ismove;
	}
	//プレイヤーの死亡アニメーションの終了
	bool GetPlayerDeath()
	{
		return m_isDeathflg;
	}
	void SetDeath(bool isdeath)
	{
		m_isDeathflg = isdeath;
	}
	//プレイヤーが地面についているかどうか
	const bool GetGround()
	{
		return m_characterController.IsOnGround();
	}

	//インスタンスの生成
	static void Player::Create()
	{
		if (!player)
		{
			player = new Player;
		}

	}

	//インスタンスの消去
	static void Player::Destroy()
	{
		delete player;
		player = nullptr;
	}
	//インスタンスの取得
	static Player& GetInstance()
	{
		return *player;
	}
	//スキンモデルの取得
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
	void SetMove(bool isMove)
	{
		m_isMoveStop = isMove;
	}
private:

	static Player* player;//インスタンス
	enum PlayerState							//プレイヤーアニメーションの状態
	{Stand, Dash, Jump,Damage,Dead,Bullets};
	PlayerState			m_state=Stand;
	PlayerState			m_workState = Stand;
	bool				m_isDead = false;		//死亡アニメーションフラグ
	bool				m_isrun=false;			//走るアニメーションフラグ
	bool				m_ismove=false;			//歩行アニメーションフラグ
	bool				m_isjump=false;			//ジャンプアニメーションフラグ
	bool				m_jumpflg = false;		//ジャンプアニメーションフラグ
	bool				m_isDamage = false;		//ダメージアニメーションフラグ
	bool				m_isStand = false;		//待機アニメーションフラグ
	bool				m_isDamageflg = false;	//ダメージアニメーションフラグ
	bool				m_isDeathflg = false;		//死亡フラグ
	bool				m_isBulletflg = false;
	int					m_damageTime = 0;		//無敵時間
	int					m_damageMaxTime = 200;	//最大無敵時間
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	Light				m_light;				//ライト
	Animation			m_animation;			//アニメーション
	CharacterController	m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_middlePosition;		//プレイヤーの中心座標
	D3DXVECTOR3			m_scale;				//拡大
	D3DXQUATERNION		m_rotation;				//回転
	const float			m_charaRadius=0.6f;		//キャラの半径
	const float			m_charaHeight=0.5f;		//キャラの高さ
	D3DXVECTOR3			m_moveSpeed ;			//移動速度
	D3DXVECTOR3			m_dir;					//かんせー
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;	//スペキュラマップ
	//LPDIRECT3DTEXTURE9	m_normalMapGun = NULL;		//法線マップ
	//LPDIRECT3DTEXTURE9	m_specularMapGun = NULL;	//スペキュラマップ
	float				m_gravity = -10.0f;		//重力
	bool				m_isMoveStop = false;		//移動と回転をなくす
	bool				m_isMax = false;		//最大移動速度のフラグ
	//bool				m_isGaraviey = true;
	int					m_addDir = 0;			//加算方向
	D3DXVECTOR3			m_cameraTar;
	D3DXVECTOR3			m_cameraPos;

	const float			m_playerBulletLenge = 2.0f;	//バレットが打てる距離
	const float			m_beamVolume = 0.4f;	//ビーム音量
	const int			m_maxBulletTime = 60;	//最大死亡タイム

	int					m_bulletIntervalTime = 20;	//バレットの発射間隔
	//bool				m_isDead = false;		//死亡処理フラグ
	//bool				m_isDeath = false;		//死亡フラグ
	bool				m_isPlayerBulletCamera = false;//バレットカメラ
	bool				m_isPlayerBullet = false;
	Sound*				m_jumpSound=nullptr;
	Sound*				m_beamSound=nullptr;
};