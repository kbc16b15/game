/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "SceneManager.h"
#include "Fade.h"
#include "Map.h"
#include "ShadowMap.h"
#include "bloom.h"
#include "gameCamera.h"
#include "Player.h"
#include "PlayerHp.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "GameObjectManager.h"
#include "BossEnemy.h"
#include "BossHp.h"
#include "Silhouette.h"
#include "IGameObject.h"

//コンストラクタ。
Game::Game()
{
	/*Player::Create();
	PlayerHp::Create();
	BulletManager::Create();
	EnemyManager::Create();
	Map::Create();
	gameCamera::Create();
	Bloom::Create();*/
	m_silhouette = new Silhouette;
	m_player = new Player;
	m_playerHp = new PlayerHp;
	//m_bossEnemy = new BossEnemy;
	//m_bossHp = new BossHp;
	m_enemyManager = new EnemyManager;
	m_bulletManager = new BulletManager;
	m_gameCamera = new gameCamera;
	m_map = new Map;
	m_bloom = new Bloom;
	m_silhouette = new Silhouette;
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
	if (m_bgmSound != nullptr)
	{
		m_bgmSound->Release();
		m_bgmSound = nullptr;
	}
	
	/*SceneManager::GetGame().GetPlayer().Destroy();
	PlayerHp::GetInstance().Destroy();
	EnemyManager::GetInstance().Release();
	BulletManager::GetInstance().Release();
	Map::GetInstance().Destroy();
	gameCamera::GetInstance().Destroy();
	Bloom::GetInstance().Destroy();*/
	delete m_player;
	delete m_playerHp;
	delete m_bulletManager;
	delete m_enemyManager;
	delete m_gameCamera;
	delete m_bloom;
	delete m_map;
	delete m_silhouette;
}

void Game::GameRelease()
{
	/*GameObjectManager::GetGameObjectManager().DeleteGameObject(&Map::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_silhouette);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Bloom::GetInstance());*/

	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_map);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_silhouette);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_bulletManager);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_player);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_playerHp);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_enemyManager);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_gameCamera);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_bloom);

	if (&m_bossEnemy != NULL)
	{
		GameObjectManager::GetGameObjectManager().DeleteGameObject(m_bossEnemy);
		GameObjectManager::GetGameObjectManager().DeleteGameObject(m_bossHp);
		delete m_bossEnemy;
		delete m_bossHp;
	}

}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Init()
{

	const float SoundVolume = 0.2f;
	m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/アバタール.wav", false);
	m_bgmSound->SetVolume(SoundVolume);
	m_bgmSound->Play(true);
	//プレイヤー初期化
	m_player->Init();
	m_playerHp->Init();
	//PlayerHp::GetInstance().Init();
	//マップを初期化
	//Map::GetInstance().SetStage(m_stageNo);
	//Map::GetInstance().Init();
	m_map->SetStage(m_stageNo);
	m_map->Init();
	//カメラ初期化。
	//gameCamera::GetInstance().Init();
	m_gameCamera->Init();
	//登録
	//GameObjectManager::GetGameObjectManager().AddGameObject(&Map::GetInstance());
	//GameObjectManager::GetGameObjectManager().AddGameObject(m_silhouette);
	//GameObjectManager::GetGameObjectManager().AddGameObject(&Player::GetInstance());
	//GameObjectManager::GetGameObjectManager().AddGameObject(&PlayerHp::GetInstance());
	//GameObjectManager::GetGameObjectManager().AddGameObject(&gameCamera::GetInstance());
	//GameObjectManager::GetGameObjectManager().AddGameObject(&BulletManager::GetInstance());
	//GameObjectManager::GetGameObjectManager().AddGameObject(&EnemyManager::GetInstance());
	//GameObjectManager::GetGameObjectManager().AddGameObject(&Bloom::GetInstance());

	GameObjectManager::GetGameObjectManager().AddGameObject(m_map);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_silhouette);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_player);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_playerHp);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_bulletManager);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_gameCamera);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_enemyManager);
	GameObjectManager::GetGameObjectManager().AddGameObject(m_bloom);

	if (m_isBossBattle)
	{
		m_bossEnemy = new BossEnemy;
		m_bossHp = new BossHp;
		m_bossHp->Init();
		m_bossEnemy->Init(D3DXVECTOR3(-11.94f, 10.00f, 8.28f),             //平行移動
			D3DXQUATERNION(0.00f, 1.00f, 0.00f, 0.00f));
		GameObjectManager::GetGameObjectManager().AddGameObject(m_bossHp);
		GameObjectManager::GetGameObjectManager().AddGameObject(m_bossEnemy);

	}
}

/*!
 * @brief	更新。
 */
void Game::Update()
{
	if (m_bgmSound != nullptr) {
		if (m_bgmSound->IsPlaying())
			m_bgmSound->Update();
	}

	//シャドウ
	SetShadow();
	//フェード
	SceneFade();//ゲームシーンをデリートする可能性がある?

}
//描画
void Game::Draw()
{
}

void Game::SetShadow()
{
	//かげ用のライトの位置の設定
	D3DXVECTOR3 toPos = m_player->Getpos();
	toPos.y += 6.0f;
	ShadowMap::GetInstance().SetviewPosition(toPos);
	ShadowMap::GetInstance().SetviewTarget(m_player->Getpos());
}

void Game::SceneFade()
{
	D3DXVECTOR3 toPos = m_player->Getpos();
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute()/*&&m_isLoadEnd*/) {
			Fade::GetInstance().StartFadeIn();
			m_state = Run;
		}
		break;
	case Run:
		//ゲームオーバー
		if (m_player->GetPlayerDeath() || toPos.y < m_killZ) {
			m_player->SetDeath(true);
			Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
			m_isEnd = true;
			
		}
		//次のステージへ
		else if (m_isNext)
		{
			if (m_map->GetStage() == m_map->STAGE1/*&&!m_isNextTo*/)
			{
				m_stageNo = 1;
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
			}
			else if (m_map->GetStage() == m_map->STAGE2/*&&!m_isNextTo*/)
			{
				m_stageNo = 2;
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
			}
		}
		//クリアシーン
		else if (m_isClear)
		{
			m_state = WaitFadeOut;
		}
		break;
	case WaitFadeOut:
		if(!Fade::GetInstance().isExecute())
		{
			
			GameRelease();
			if (m_isClear)
			{
				SceneManager::ChangeScene(SceneManager::CLEAR);
				m_isClear = false;
			}
			else if (m_isEnd)
			{
				SceneManager::ChangeScene(SceneManager::RESULT);
				m_isEnd = false;
			}
			else if (m_stageNo == 1 /*&& m_isNextTo*/)
			{
				SceneManager::ChangeScene(SceneManager::GAME2);
				m_isNext = false;
			}
			else if(m_stageNo==2/*&&m_isNextTo*/)
			{
				SceneManager::ChangeScene(SceneManager::GAME3);
				m_isNext = false;
			}
		}
		
		break;
	default:
		break;
	}
}