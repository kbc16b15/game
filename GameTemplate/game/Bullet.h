#pragma once
class Bullet:public IGameObject
{
public:
	//打ったキャラ
	enum CHARA {
		PLAYER,
		TANK,
		ENEMY
	};
	//コンストラクタ
	Bullet();
	//デストラクタ
	~Bullet();
	//初期化　座標の設定
	void Init(D3DXVECTOR3 pos, float speed,CHARA chara);

	//初期化　目標座標　座標の設定
	void Start(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, float speed, CHARA chara);
	//更新
	void Update();
	//描画
	void Draw();
	//バレットの寿命と追従
	void TargetBullet();

	//バレットの当たり
	void BulletHit();

	//死亡フラグの取得
	bool GetDeathflg()
	{
		return m_bulletDeadflg;
	}
	//IDの取得
	CHARA GetID()
	{
		return m_chara;
	}

private:
	CHARA				m_chara;	//弾の状態
	//CHARA				m_bulletId;			//弾のID
	SkinModel			m_skinModel;		//スキンモデル
	static SkinModelData* m_skinModelData;	//スキンモデルデータ
	Light				m_light;			//ライト
	D3DXVECTOR3			m_position;			//座標
	D3DXVECTOR3			m_scale;			//拡大
	D3DXQUATERNION		m_rotation;			//回転
	D3DXVECTOR3			m_targetPos;		//目的の座標
	D3DXVECTOR3			m_direction;		//バレットの向き
	int					m_btime = 300;		//バレットの寿命
	const int			m_maxBtime = 300;	//バレットの最大寿命
	bool				m_bulletDeadflg = false;	//バレットの死亡フラグ
	bool				m_find = false;		//発見フラグ
	const float			m_bulletRadius=0.2f;//バレットの半径
	const float			m_playerRadius=0.3f;//プレイヤーの半径
	float				m_bulletSpeed= 0.2f;//バレットのスピード
	const float			m_playerUp = 0.3f;	//プレイヤーのあげる幅
	const float			m_bulletDeathlenge = 0.1f;//バレットが死ぬ距離
};

