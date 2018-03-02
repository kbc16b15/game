#pragma once
#include "IGameObject.h"
class BossHp :
	public IGameObject
{
public:
	//コンストラクタ
	BossHp();
	//デストラクタ
	~BossHp();

	void Init();
	void Update() {};
	void HudDraw();

	//ボスダメージ処理
	void BossDamage(int dame)
	{
		m_bossHpNum -= dame;
	}
	//ボスHPの取得
	int GetBossHpNum()
	{
		return m_bossHpNum;
	}
	////インスタンスの生成
	//static void Create()
	//{
	//	if (!m_bossHp)
	//	{
	//		m_bossHp = new BossHp;
	//	}

	//}

	////インスタンスの消去
	//static void Destroy()
	//{
	//	delete m_bossHp;
	//	m_bossHp = nullptr;
	//}
	////インスタンスの取得
	//static BossHp& GetInstance()
	//{
	//	return *m_bossHp;
	//}
private:
	//static BossHp* m_bossHp;//インスタンス
private:

	//ボスHP
	D3DXVECTOR2			m_bossHpPos = { 140.0f,-300.0f };	//ボスのHP座標
	const D3DXVECTOR2	m_bossHpScale = { 100.0f,100.0f };
	const int			m_bossHpMaxNum = 5;			//ボスの最大HP
	int					m_bossHpNum = 5;			//ボスのHP
	const float			m_bossHpMovePos = 100.0f;	//ボスのHP間隔
	Sprite				m_bossHpNo[5];				//画像表示の変数
	Texture				m_bossHpTexture;					//テクスチャ
};

