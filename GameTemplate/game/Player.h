#pragma once
#include "myEngine/Physics/CharacterController.h"
class Player:public IGameObject
{
public:
	//デストラクタ
	~Player();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void ShadowDraw(D3DXMATRIX* viewM, D3DXMATRIX* projM, bool shadowCaster, bool shadowRecive);
	void Draw();

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
	//プレイヤー座標の取得
	D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
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
	D3DXVECTOR3 GetSpeed()
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
	bool GetPlayerMove()
	{
		return m_ismove;
	}
	//プレイヤーの死亡アニメーションの終了
	bool PlayerDeath()
	{
		return m_isDeathflg;
	}
	//プレイヤーが地面についているかどうか
	bool GetGround()
	{
		return m_characterController.IsOnGround();
	}

	//インスタンスの生成
	static void Player::Create()
	{
		if (!m_player)
		{
			m_player = new Player;
		}

	}

	//インスタンスの消去
	static  void Player::Destroy()
	{
		delete m_player;
		m_player = nullptr;
	}
	//インスタンスの取得
	static Player& GetInstance()
	{
		return *m_player;
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
	//コンストラクタ
	Player();
	static Player* m_player;//インスタンス
	enum PlayerState							//プレイヤーアニメーションの状態
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
	bool				m_isDamageflg = false;	//ダメージアニメーションフラグ
	bool				m_isDeathflg = false;		//死亡フラグ
	int					m_damageTime = 0;		//無敵時間
	int					m_damageMaxTime = 200;	//最大無敵時間
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	Light				m_light;				//ライト
	Animation			m_animation;			//アニメーション
	CharacterController	m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_scale;				//拡大
	D3DXQUATERNION		m_rotation;				//回転
	const float			m_charaRadius=0.6f;		//キャラの半径
	const float			m_charaHeight=0.5f;		//キャラの高さ
	D3DXVECTOR3			m_moveSpeed ;			//移動速度
	D3DXVECTOR3			m_dir;					//かんせー
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;	//スペキュラマップ
	float				m_gravity = -10.0f;		//重力
	bool				m_isMoveStop = false;		//移動と回転をなくす
	bool				m_isMax = false;		//最大移動速度のフラグ
	int					m_addDir = 0;			//加算方向

};