#pragma once
#include "Sound.h"
#include "IScene.h"
#include "GameObjectManager.h"
class Silhouette;
class Player;
class PlayerHp;
class BossEnemy;
class BossHp;
class EnemyManager;
class BulletManager;
class gameCamera;
class Map;
class Bloom;
/*!
 * @brief	ゲームクラス。
 */
class Game :public IScene
{
public:
	//コンストラクタ
	Game();
	//デストラクタ
	~Game();
	//起動関数
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//シャドウの位置設定
	void SetShadow();
	//フェード
	void SceneFade();
	//ゲームシーンの開放
	void GameRelease();

	//ゲーム終了のフラグの取得
	bool GetGameEnd()
	{
		return m_isEnd;
	}
	//次のステージへ
	void StageNext()
	{
		m_isNext = true;
	}
	//クリア
	void StageClear(bool isClear)
	{
		m_isClear = isClear;
	}
	//BGMストップ
	void BgmStop()
	{
		if (m_bgmSound != nullptr)
			m_bgmSound->Stop();
	}
	//ステージセット
	void SetStage(int No)
	{
		m_stageNo = No;
	}

	Player& GetPlayer()
	{
		return *m_player;
	}

	PlayerHp& GetPlayerHp()
	{
		return *m_playerHp;
	}

	EnemyManager& GetEnemyManager()
	{
		return *m_enemyManager;
	}

	BulletManager& GetBulletManager()
	{
		return *m_bulletManager;
	}

	gameCamera& GetGameCamara()
	{
		return *m_gameCamera;
	}

	Map& GetMap()
	{
		return *m_map;
	}

	/*void CreateBoss(BossEnemy boss)
	{
		m_bossEnemy = &boss;
		GameObjectManager::GetGameObjectManager().AddGameObject(m_bossEnemy);


	}

	void CreateBossHp(BossHp bossHp)
	{
		m_bossHp = &bossHp;
		GameObjectManager::GetGameObjectManager().AddGameObject(m_bossHp);
	}*/

	BossEnemy& GetBoss()
	{
		return *m_bossEnemy;
	}

	BossHp& GetBossHp()
	{
		return *m_bossHp;
	}

	void SetBossBattle(bool isBoss)
	{
		m_isBossBattle = isBoss;
	}
private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState			m_state = WaitFadeIn;		//フェードの状態
	Silhouette*		m_silhouette = nullptr;		
	Player*			m_player = nullptr;			
	PlayerHp*		m_playerHp = nullptr;		
	BossEnemy*		m_bossEnemy = nullptr;		
	BossHp*			m_bossHp = nullptr;			
	EnemyManager*	m_enemyManager = nullptr;
	BulletManager*	m_bulletManager=nullptr;	
	gameCamera*		m_gameCamera=nullptr;		
	Map*			m_map=nullptr;				
	Bloom*			m_bloom=nullptr;			


	Sound*			m_bgmSound=nullptr;			//サウンド
	const float		m_killZ = -10.0f;			//プレイヤーが死ぬ高さ
	bool			m_isNext = false;			//次のステージへ
	bool			m_isClear = false;			//クリア
	bool			m_isEnd = false;			//ゲームオーバー
	bool			m_isBossBattle = false;
	int				m_stageNo=0;
};