/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "Scene.h"
#include <stdlib.h>
#include <time.h>

//gameCamera* g_gameCamera = nullptr;


/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
	srand((unsigned int)time(NULL));
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{

}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	g_fade->StartFadeIn();
	//物理ワールドを初期化
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//カメラ初期化。
	camera.Init();
	//マップを初期化。
	map.Init(/*mapChipInfo*/);
	//プレイヤーを初期化。
	player.Start();
	//画像表示
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Initialize("Assets/Sprite/HP.png", Hppos);
		Hppos.x += 100.0f;
	}
	Key.Initialize("Assets/Sprite/key.png", Keypos);
	
	CreateSprite();
	//Player* pl = new Player();
	//GoMgr.AddGameObject(pl);
	//Enemy* en = new Enemy();
	//GoMgr.AddGameObject(en);
	//Map* map = new Map();
	//GoMgr.AddGameObject(map);
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	auto enemyIt = enem.begin();
	while (enemyIt != enem.end()){
		if ((*enemyIt)->GetDeathflg()){
			enemyIt = enem.erase(enemyIt);
		}
		else {
			enemyIt++;
		}
	}

	auto bulletIt = Bullets.begin();
	while (bulletIt != Bullets.end()){
		if (!(*bulletIt)->GetBulletflg()) {
			bulletIt = Bullets.erase(bulletIt);
		}
		else {
			bulletIt++;
		}
	}

	for (auto enemy : enem)
	{
		enemy->Update();
	}
	for (auto bullet : Bullets)
	{
		bullet->Update();
	}
	//画像のアップデート
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Update();
	}
	Key.Update();
	//GoMgr.Update();
	g_physicsWorld->Update();
	player.Update();
	camera.Update();
	map.Update();
	D3DXVECTOR3 Ppos = player.Getpos();
	if (Hpnum < 1||Ppos.y<-2.0f)
	{
		GameEnd();
		
	}
	if (GetAsyncKeyState('G'))
	{
		NextStage();
	}
}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	//GoMgr.Draw();
	player.Draw();
	map.Draw();
	for (auto enemy : enem)
	{
		enemy->Draw();
	}
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	
	for (auto bullet : Bullets)
	{
		bullet->Draw();
	}
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Draw(m_Sprite);
	}
	
	Key.Draw(m_Sprite);
	
}

void Game::GameEnd()
{
	for (auto bullet : Bullets) {
		delete bullet;
	}

	for (auto Enemynum : enem)
	{
		delete Enemynum;
	}
	scene->SetScene(scene->CHANGEEND);
	scene->SceneChange();
	//g_fade->StartFadeOut();
}

void Game::NextStage()
{
	for (auto bullet : Bullets)
	{
		delete bullet;
	}

	for (auto Enemynum : enem)
	{
		delete Enemynum;
	}
	scene->SceneChange();
	//g_fade->StartFadeIn();
}



HRESULT Game::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}