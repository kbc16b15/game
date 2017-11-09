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
	void Start(D3DXVECTOR3 pos);
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
		return IsDeath;
	}
	enum TEnemyState
	{
		SEACH,
		FOUND,
		DEAD

	};
private:
	int TState = SEACH;
	SkinModel			skinModel;											//スキンモデル
	SkinModelData		skinModelData;										//スキンモデルデータ
	D3DXVECTOR3			position;											//座標
	D3DXVECTOR3			Spos;												//初期座標
	D3DXVECTOR3			scale = { 1.0f,1.0f,1.0f };							//拡大
	D3DXQUATERNION		rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//回転
	Light				light;												//ライト
	int					BulletTime = 150;									//バレットの発射間隔
	bool				IsDead = false;										//死亡処理フラグ
	bool				IsDeath = false;									//死亡フラグ
	int					DeadTime = 100;										//死亡タイム
	int					BulletDir = 0;										//バレット打つ方向
	CharacterController	characterController;				//キャラクターコントローラー
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度

	D3DXVECTOR3 direction = { 0.0f,0.0f,1.0f };
	bool				moveX = false;

};

