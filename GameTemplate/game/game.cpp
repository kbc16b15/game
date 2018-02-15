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
#include "SceneChange.h"
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
	SceneChange::Create();
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
	Player::GetInstance().Destroy();
	PlayerHp::GetInstance().Destroy();
	EnemyManager::GetInstance().Release();
	BulletManager::GetInstance().Release();
	Map::GetInstance().Destroy();
	gameCamera::GetInstance().Destroy();
	Bloom::GetInstance().Destroy();
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

}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Init()
{
	Map::GetInstance().SetStage(SceneChange::GetInstance().GetMapNo());
	//マップを初期化
	Map::GetInstance().Init();
	//プレイヤー初期化
	Player::GetInstance().Init();
	PlayerHp::GetInstance().Init();
	//カメラ初期化。
	gameCamera::GetInstance().Init();
	//登録
	GameObjectManager::GetGameObjectManager().AddGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&Map::GetInstance());

	GameObjectManager::GetGameObjectManager().AddGameObject(&Bloom::GetInstance());

	/*m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/tw038.mp3",false);
	m_bgmSound->SetVolume(0.5f);
	m_bgmSound->Play(true);*/
	//フェードイン
	//Fade::GetInstance().StartFadeIn();
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
	SceneFade();//ゲームシーンをデリートする可能性がある?

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

	if (!m_isLoadEnd)
	{
		m_isLoadEnd = true;
	}
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
		if (!Fade::GetInstance().isExecute()&&m_isLoadEnd) {
			Fade::GetInstance().StartFadeIn();
			m_state = Run;
		}
		break;
	case Run:
		if (Player::GetInstance().PlayerDeath() || toPos.y < m_killZ) {

			m_isEnd = true;
			ResultScene::Create();
			ResultScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&ResultScene::GetInstance());
			Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
		}
		else if (m_isNext)
		{
			if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE1)
			{
				/*
				SceneChange::Create();
				GameObjectManager::GetGameObjectManager().AddGameObject(&SceneChange::GetInstance());
				*/

				ResultScene::Create();
				ResultScene::GetInstance().Init();
				SceneChange::GetInstance().SetChange(true);
				GameObjectManager::GetGameObjectManager().AddGameObject(&ResultScene::GetInstance());
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
				//m_isNextTo = true;
			}
			else if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE2)
			{

				TitleScene::Create();
				TitleScene::GetInstance().Init();
				GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
			}
		}
		else if (m_isClear)
		{
			ClearScene::Create();
			ClearScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&ClearScene::GetInstance());
			m_state = WaitFadeOut;
			Fade::GetInstance().StartFadeOut();
			m_isClear = false;
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