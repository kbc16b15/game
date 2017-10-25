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
		return IsDeath;
	}
private:
	SkinModel			skinModel;											//スキンモデル
	SkinModelData		skinModelData;										//スキンモデルデータ
	D3DXVECTOR3			position = { -20.0f,0.0f,0.0f };					//座標
	D3DXVECTOR3			scale = { 0.5f,0.5f,0.5f };							//拡大
	D3DXQUATERNION		rotation= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//回転
	Light				light;												//ライト
	int					BulletTime = 150;									//バレットの発射間隔
	bool				IsDead = false;										//死亡処理フラグ
	bool				IsDeath = false;									//死亡フラグ
	int					DeadTime = 100;										//死亡タイム
	int					BulletDir = 0;										//バレット打つ方向

};

