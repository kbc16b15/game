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
		return characterController.GetPosition();
	}
	//座標セット
	void Setpos(D3DXVECTOR3 pos)
	{
		position = pos;

	}
	//プレイヤーのジャンプフラグ設定
	void SetJumpflg(bool Jump)
	{
		Jumpflg = Jump;
	}
	//プレイヤーの移動速度を設定
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		characterController.SetMoveSpeed(addpos);
		characterController.Execute();
	}
	//プレイヤーの移動速度の取得
	D3DXVECTOR3 GetSpeed()
	{
		return characterController.GetMoveSpeed();
	}
	//ダメージ通知
	void SetDamage()
	{
		if (DamageTime > 0) { return; }
		Damageflg = true;
	}

	//移動の停止
	void PlayerMoveSet(bool Move)
	{
		MoveStop = Move;
	}
	//プレイヤーの死亡アニメーションの終了
	bool PlayerDeath()
	{
		return Deathflg;
	}
	//オブジェクトとの当たった判定
	bool GetObjectHit()
	{
		return ObjectHit;
	}

	//オブジェクトとの当たった判定の設定
	void SetObjectHit(bool hit)
	{
		ObjectHit = hit;
	}

	////重力の設定
	//void SetGravity()
	//{
	//	if (m_isGravity)
	//	{
	//		characterController.SetGravity(-10.0f);
	//		m_isGravity = false;
	//	}
	//	else
	//	{
	//		characterController.SetGravity(10.0f);
	//		m_isGravity = true;
	//	}
	//	
	//}
private:
	enum PlayerState						//プレイヤーアニメーションの状態
	{Stand, Move, Dash, Jump,Damage,Dead};
	PlayerState			m_State=Stand;
	PlayerState			workState = Stand;
	bool				IsDead = false;		//死亡アニメーションフラグ
	bool				Isrun=false;		//走るアニメーションフラグ
	bool				Ismove=false;		//歩行アニメーションフラグ
	bool				Isjump=false;		//ジャンプアニメーションフラグ
	bool				Jumpflg = false;	//ジャンプアニメーションフラグ
	bool				IsDamage = false;	//ダメージアニメーションフラグ
	bool				IsStand = false;	//待機アニメーションフラグ
	bool				Damageflg = false;	//ダメージアニメーションフラグ
	bool				Deathflg = false;	//死亡フラグ
	int					DamageTime = 0;		//ダメージ間隔
	SkinModel			skinModel;							//スキンモデル
	SkinModelData		skinModelData;						//スキンモデルデータ
	Light				light;								//ライト
	Animation			animation;							//アニメーション
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };		//座標
	D3DXVECTOR3			scale = { 1.0f,1.0f,1.0f };			//拡大
	D3DXQUATERNION		rotation = { 0.0f,0.0f,0.0f,1.0f };	//回転
	CharacterController	characterController;				//キャラクターコントローラー
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度
	Pad					pad;								//パッド
	LPDIRECT3DTEXTURE9	normalMap = NULL;					//法線マップ
	LPDIRECT3DTEXTURE9	specularMap = NULL;					//スペキュラマップ
	D3DXVECTOR3			Addvector = { 0.0f,0.0f,0.0f };		//加算速度
	float				m_Gravity = -10.0f;					//重力
	//bool				m_isGravity = false;				//反転フラグ
	//float				gAngle = 0.0f;
	//bool				Grotflg = true;
	bool				MoveStop = false;
	bool				ObjectHit = false;
	bool				maxSflg = false;
	D3DXVECTOR3 Dir = { 0.0f,0.0f,0.0f };//かんせー
	
	Sound*				m_JumpSound = nullptr;

};

//extern Player*		g_player;
