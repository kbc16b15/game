/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "TitleScene.h"
#include "ResultScene.h"
#include "ClearScene.h"
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
//#include "MapInfo.h"

Game *Game::m_game = NULL;

//コンストラクタ。
Game::Game()
{
	//SetLight();
	//srand((unsigned int)time(NULL));
	Player::Create();
	PlayerHp::Create();

	BulletManager::Create();
	EnemyManager::Create();
	Map::Create();
	gameCamera::Create();
	Bloom::Create();


	//マップを初期化。
	/*if (Map::GetInstance().GetStage()==Map::GetInstance().STAGE1)
	{
		Map::GetInstance().Init(&InfoOne[0]);
	}
	else if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE2)
	{
		Map::GetInstance().Init(&InfoTwo[0]);
	}
	else
	{
	}*/
	//カメラ初期化。
	gameCamera::GetInstance().Init();
	//プレイヤー初期化
	Player::GetInstance().Init();
	PlayerHp::GetInstance().Init();
	Map::GetInstance().Init();
	//Map::GetInstance().Init(&Map::GetInstance().GetMap1());


}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{

}

void Game::GameRelease()
{
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Game::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Map::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Bloom::GetInstance());

	Game::GetInstance().Destroy();
	Player::GetInstance().Destroy();
	PlayerHp::GetInstance().Destroy();
	EnemyManager::GetInstance().Destroy();
	BulletManager::GetInstance().Destroy();
	Map::GetInstance().Destroy();
	gameCamera::GetInstance().Destroy();
	Bloom::GetInstance().Destroy();

}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Init()
{

	GameObjectManager::GetGameObjectManager().AddGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&Map::GetInstance());
	//登録
	GameObjectManager::GetGameObjectManager().AddGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&Bloom::GetInstance());

	/*Sound**/ /*m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/bgm.wav",false);
	m_bgmSound->SetVolume(0.5f);
	m_bgmSound->Play(true);*/
	//フェードイン
	Fade::GetInstance().StartFadeIn();
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	//m_bgmSound->Update();
	//シャドウ
	SetShadow();
	//フェード
	SceneFade();//ゲームシーンをデリートする可能性があるからUpdateの一番下に置いている

}
/*!
 * @brief	描画。
 */
void Game::Draw()
{
	//物体に遮蔽されているときにだけ描画する
	//g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z値を書き込まないようにする
	//Player::GetInstance().ShadowDraw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix(),true, false);
	//g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}


void Game::SetShadow()
{
	//かげ用のライトの位置の設定
	D3DXVECTOR3 toPos = Player::GetInstance().Getpos();
	toPos.y += 6.0f;
	ShadowMap::GetInstance().SetviewPosition(toPos);
	ShadowMap::GetInstance().SetviewTarget(Player::GetInstance().Getpos());
}

void Game::SceneFade()
{
	D3DXVECTOR3 toPos = Player::GetInstance().Getpos();
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute()) {
			m_state = Run;
		}
		break;
	case Run:
		if (Player::GetInstance().PlayerDeath() || toPos.y < m_killZ) {
			Fade::GetInstance().StartFadeOut();
			m_isEnd = true;
			ResultScene::Create();
			ResultScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&ResultScene::GetInstance());
			m_state = WaitFadeOut;
		}
		else if (m_isNext)
		{
			if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE1)
			{
				Fade::GetInstance().StartFadeOut();
				Game::GetInstance().GameRelease();
				Game::Create();
				Game::GetInstance().Init();
				Map::GetInstance().SetStage(Map::GetInstance().STAGE2);
				GameObjectManager::GetGameObjectManager().AddGameObject(&Game::GetInstance());


			}
			else if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE2)
			{
				Fade::GetInstance().StartFadeOut();
				TitleScene::Create();
				TitleScene::GetInstance().Init();
				GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());
				Game::GetInstance().GameRelease();
			}
		}
		else if (m_isClear)
		{
			Fade::GetInstance().StartFadeOut();
			ClearScene::Create();
			ClearScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&ClearScene::GetInstance());
			Game::GetInstance().GameRelease();
		}
		break;
	case WaitFadeOut:
		if(!Fade::GetInstance().isExecute())
		{
			
			Game::GetInstance().GameRelease();
		}
		break;
	default:
		break;
	}

	
}