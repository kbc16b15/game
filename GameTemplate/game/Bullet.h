#pragma once
//#include "IGameObject.h"
class Bullet/*:public IGameObject*/
{
public:
	//コンストラクタ
	Bullet();
	//デストラクタ
	~Bullet();
	//初期化　座標の設定
	void Start(D3DXVECTOR3 pos,D3DXVECTOR3 targetPos,int cha);
	//更新
	void Update();
	//描画
	void Draw();

	//座標取得
	D3DXVECTOR3 Getpos()
	{
		return position;
	}
	//バレットの寿命と追従
	void TargetBullet();

	//死亡フラグの取得
	bool GetBulletflg()
	{
		return Bulletflg;
	}
	//打ったキャラ
	enum Chara {
		Player,
		Enemy
	};
private:
	//enum EState {
	//	eState_Search,	//索敵状態。
	//	eState_Find,	//発見状態。
	//};
	//EState state;		//敵の状態。

	int m_Chara = Enemy;//弾の状態
	SkinModel			skinModel;										//スキンモデル
	static SkinModelData* skinModelData;								//スキンモデルデータ
	Light				light;											//ライト
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };					//座標
	D3DXVECTOR3			scale = { 0.3f,0.3f,0.3f };						//拡大
	D3DXQUATERNION		rotation=D3DXQUATERNION(0.0f, 1.0f, 0.0f, 1.0);	//回転
	D3DXVECTOR3			Playerpos;										//プレイヤーの座標の格納変数
	D3DXVECTOR3			TargetPos;										//目的の座標
	D3DXVECTOR3			direction;										//バレットの向き
	int					Btime = 300;									//バレットの寿命
	bool				Bulletflg = true;								//バレットの死亡フラグ
	bool				Find = false;									//発見フラグ
};

