/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"
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
	for (auto bullet : Bullets) {
		delete bullet;
	}

	for (auto Enemynum : enem)
	{
		delete Enemynum;
	}
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	//物理ワールドを初期化
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//カメラ初期化。
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(5.0f, 7.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();
	//マップを初期化。
	map.Init();
	//プレイヤーを初期化。
	player.Start();
	//画像表示
	image.Init();
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

	//プレイヤー追従カメラ。
	D3DXVECTOR3 targetPos = player.Getpos();
	if (targetPos.y < 0.0f)
	{
		targetPos.y = 0.0f;
	}
	//GoMgr.Update();
	image.Update();
	g_physicsWorld->Update();
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);
	player.Update();
	camera.Update();
	map.Update();

}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	//GoMgr.Draw();
	player.Draw();
	map.Draw();
	image.Render();
	for (auto enemy : enem)
	{
		enemy->Draw();
	}
	for (auto bullet : Bullets)
	{
		bullet->Draw();
	}
}
