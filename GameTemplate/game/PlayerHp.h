#pragma once
//#include "IGameObject.h"
//#include "HUD.h"
class PlayerHp :
	public IGameObject
{
public:
	//コンストラクタ
	PlayerHp();
	~PlayerHp();

	void Init();
	void Update() {};
	void HudDraw();
	//プレイヤーダメージ処理
	void PlayerDamage(int dame)
	{
		m_playerHpNum -= dame;
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
	int GetPlayerHpNum()
	{
		return m_playerHpNum;
	}
private:
	//プレイヤーHP
	D3DXVECTOR2	m_playerHpPos = { -550.0f,300.0f };	//プレイヤーHP座標
	const D3DXVECTOR2 m_playerHpScale = { 100.0f,100.0f };
	const int	m_playerHpMaxNum = 3;		//最大プレイヤーHP量
	int			m_playerHpNum = 3;			//プレイヤーHP量
	const float	m_playerHpMovePos = 110.0f;	//プレイヤーHP間隔
	Sprite		m_playerHpNo[3];			//画像表示の変数
	Texture		m_playerHpTexture;			//スプライト
};

