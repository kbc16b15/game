#pragma once
//#include "IGameObject.h"
#include "HUD.h"
class PlayerHp :
	public IGameObject
{
public:
	//PlayerHp();
	~PlayerHp();

	void Init();
	void Update() {};
	void Draw();
	//スプライト生成関数
	HRESULT CreateSprite();

	//プレイヤーダメージ処理
	void PlayerDamage(int dame)
	{
		m_playerHpNum -= dame;
		//プレイヤーHPのアップデート
		for (int i = 0;i < m_playerHpNum;i++)
		{
			m_playerHpNo[i].Update();
		}
	}
	//プレイヤー体力の回復
	void PlayerHeal(int healval)
	{
		m_playerHpNum += healval;
		if (m_playerHpNum >= m_playerHpMaxNum)
		{
			m_playerHpNum = m_playerHpMaxNum;
		}
	}
	//プレイヤーHPの取得
	int GetPlayerHp()
	{
		return m_playerHpNum;
	}

	//インスタンスの生成
	static void PlayerHp::Create()
	{
		if (!m_playerHp)
		{
			m_playerHp = new PlayerHp;
		}

	}

	//インスタンスの消去
	static  void PlayerHp::Destroy()
	{
		delete m_playerHp;
		m_playerHp = nullptr;
	}
	//インスタンスの取得
	static PlayerHp& GetInstance()
	{
		return *m_playerHp;
	}
private:
	//コンストラクタ
	PlayerHp();
	static PlayerHp* m_playerHp;//インスタンス
private:
	//プレイヤーHP
	D3DXVECTOR2			m_playerHpPos = { 120.0f,80.0f };	//プレイヤーHP座標
	const int			m_playerHpMaxNum = 3;		//最大プレイヤーHP量
	int					m_playerHpNum = 3;			//プレイヤーHP量
	const float			m_playerHpMovePos = 100.0f;	//プレイヤーHP間隔
	HUD					m_playerHpNo[3];				//画像表示の変数
	LPD3DXSPRITE		m_sprite;					//スプライト
};

