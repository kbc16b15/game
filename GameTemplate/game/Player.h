#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine\HID\Pad.h"
#include "Sound.h"
//#include "IGameObject.h"

class Player/*:public IGameObject*/
{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Start();
	//更新
	void Update();
	//描画
	void Draw(D3DXMATRIX* viewM, D3DXMATRIX* projM,bool shadowCaster,bool shadowRecive);

	//アニメーション処理
	void AnimationSet();
	//移動処理
	void move();
	//移動キーの設定
	//void Key();
	//バレットの当たり処理
	void BulletHit();
	//キャラの向きの設定
	void Setangle();

	//プレイヤー座標の取得
	D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
	}
	//座標セット
	void Setpos(D3DXVECTOR3 pos)
	{
		m_position = pos;

	}
	//プレイヤーのジャンプフラグ設定
	void SetJumpflg(bool Jump)
	{
		m_jumpflg = Jump;
	}
	//プレイヤーの移動速度を設定
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		m_characterController.SetMoveSpeed(addpos);
		m_characterController.Execute();
	}
	//プレイヤーの移動速度の取得
	D3DXVECTOR3 GetSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}
	//ダメージ通知
	void SetDamage()
	{
		if (m_damageTime > 0) { return; }
		m_damageflg = true;
	}

	//移動の停止
	void PlayerMoveSet(bool Move)
	{
		m_moveStop = Move;
	}
	//プレイヤーの死亡アニメーションの終了
	bool PlayerDeath()
	{
		return m_deathflg;
	}
	//オブジェクトとの当たった判定
	bool GetObjectHit()
	{
		return m_objectHit;
	}

	//オブジェクトとの当たった判定の設定
	void SetObjectHit(bool hit)
	{
		m_objectHit = hit;
	}

	
private:
	enum PlayerState						//プレイヤーアニメーションの状態
	{Stand, Move, Dash, Jump,Damage,Dead};
	PlayerState			m_state=Stand;
	PlayerState			m_workState = Stand;
	bool				m_isDead = false;		//死亡アニメーションフラグ
	bool				m_isrun=false;			//走るアニメーションフラグ
	bool				m_ismove=false;			//歩行アニメーションフラグ
	bool				m_isjump=false;			//ジャンプアニメーションフラグ
	bool				m_jumpflg = false;		//ジャンプアニメーションフラグ
	bool				m_isDamage = false;		//ダメージアニメーションフラグ
	bool				m_isStand = false;		//待機アニメーションフラグ
	bool				m_damageflg = false;	//ダメージアニメーションフラグ
	bool				m_deathflg = false;		//死亡フラグ
	int					m_damageTime = 0;		//ダメージ間隔
	SkinModel			m_skinModel;							//スキンモデル
	SkinModelData		m_skinModelData;						//スキンモデルデータ
	Light				m_light;								//ライト
	Animation			m_animation;							//アニメーション
	Pad					m_pad;									//パッド
	CharacterController	m_characterController;					//キャラクターコントローラー
	D3DXVECTOR3			m_position = { 0.0f,0.0f,0.0f };		//座標
	D3DXVECTOR3			m_scale = { 1.0f,1.0f,1.0f };			//拡大
	D3DXQUATERNION		m_rotation = { 0.0f,0.0f,0.0f,1.0f };	//回転
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;						//法線マップ
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;					//スペキュラマップ
	D3DXVECTOR3			m_dir = { 0.0f,0.0f,0.0f };				//かんせー
	D3DXVECTOR3			m_Addvector = { 0.0f,0.0f,0.0f };		//加算速度
	//Sound*				m_JumpSound = nullptr;					//ジャンプ音
	float				m_Gravity = -10.0f;						//重力
	const float			m_maxSpeed=5.0f;						//最大移動速度の保存
	const float			m_jumpHeight = 8.0f;					//ジャンプの高さ
	const float			m_downSpeed = 0.3f;						//移動していないときに減速させる処理(摩擦？)
	bool				m_moveStop = false;
	bool				m_objectHit = false;
	bool				m_maxSflg = false;


};