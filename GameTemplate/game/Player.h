#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine\HID\Pad.h"
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
	void Draw();
	//アニメーション処理
	void AnimationSet();
	//移動処理
	void move();
	//移動キーの設定
	void Key();
	//バレットの当たり処理
	void BulletHit();

	//プレイヤー座標の取得
	D3DXVECTOR3 Getpos()
	{
		return characterController.GetPosition();
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
		//DamageTime = 200;
	}
private:
	enum PlayerState						//プレイヤーアニメーションの状態
	{Stand, Move, Dash, Jump,Damage,Dead};
	bool				IsDead = false;		//死亡アニメーションフラグ
	bool				Isrun=false;		//走るアニメーションフラグ
	bool				Ismove=false;		//歩行アニメーションフラグ
	bool				Isjump=false;		//ジャンプアニメーションフラグ
	bool				Jumpflg = false;	//ジャンプアニメーションフラグ
	bool				IsDamage = false;	//ダメージアニメーションフラグ
	bool				IsStand = false;	//待機アニメーションフラグ
	//bool				IsAnimend = true;	//アニメーションエンドフラグ
	bool				Damageflg = false;	//ダメージアニメーションフラグ
	int					DamageTime = 200;	//ダメージ間隔
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
	LPDIRECT3DTEXTURE9 normalMap = NULL;					//法線マップ。
	LPDIRECT3DTEXTURE9 specularMap = NULL;					//スペキュラマップ。

};

