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
		return m_position;
	}
	//バレットの寿命と追従
	void TargetBullet();

	//死亡フラグの取得
	bool GetBulletflg()
	{
		return m_bulletflg;
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

	int					m_Chara = Enemy;//弾の状態
	SkinModel			m_skinModel;										//スキンモデル
	static SkinModelData* m_skinModelData;									//スキンモデルデータ
	Light				m_light;											//ライト
	D3DXVECTOR3			m_position = { 0.0f,0.0f,0.0f };					//座標
	D3DXVECTOR3			m_scale = { 0.3f,0.3f,0.3f };						//拡大
	D3DXQUATERNION		m_rotation=D3DXQUATERNION(0.0f, 1.0f, 0.0f, 1.0);	//回転
	D3DXVECTOR3			m_playerpos;										//プレイヤーの座標の格納変数
	D3DXVECTOR3			m_targetPos;										//目的の座標
	D3DXVECTOR3			m_direction;										//バレットの向き
	int					m_btime = 300;									//バレットの寿命
	bool				m_bulletflg = true;								//バレットの死亡フラグ
	bool				m_find = false;									//発見フラグ
};

