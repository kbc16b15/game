#pragma once
#include "IGameObject.h"
#include "HUD.h"
class BossHp :
	public IGameObject
{
public:
	//BossHp();
	~BossHp();

	void Init();
	void Update() {};
	void Draw();

	//スプライト生成関数
	HRESULT CreateSprite();
	//ボスダメージ処理
	void BossDamage(int dame)
	{
		m_bossHpNum -= dame;
		//ボスHPのアップデート
		for (int i = 0;i < m_bossHpNum;i++)
		{
			m_bossHpNo[i].Update();
		}
	}
	//ボスHPの取得
	int GetBossHp()
	{
		return m_bossHpNum;
	}
	//インスタンスの生成
	static void BossHp::Create()
	{
		if (!m_bossHp)
		{
			m_bossHp = new BossHp;
		}

	}

	//インスタンスの消去
	static  void BossHp::Destroy()
	{
		delete m_bossHp;
		m_bossHp = nullptr;
	}
	//インスタンスの取得
	static BossHp& GetInstance()
	{
		return *m_bossHp;
	}
private:
	//コンストラクタ
	BossHp();
	static BossHp* m_bossHp;//インスタンス
private:

	//ボスHP
	D3DXVECTOR2			m_bossHpPos = { 800.0f,620.0f };	//ボスのHP座標
	const int			m_bossHpMaxNum = 5;			//ボスの最大HP
	int					m_bossHpNum = 5;			//ボスのHP
	const float			m_bossHpMovePos = 100.0f;	//ボスのHP間隔
	HUD					m_bossHpNo[5];				//画像表示の変数
	LPD3DXSPRITE		m_sprite;					//スプライト
};

