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

	//プレイヤーを初期化。
	player.Start();
	//enemy.Start({ -20.0f,3.0f,0.0f });
	//マップを初期化。
	map.Init();

	//Player* pl = new Player();
	//GoMgr.AddGameObject(pl);
	//Enemy* en = new Enemy();
	//GoMgr.AddGameObject(en);
	//Map* map = new Map();
	//GoMgr.AddGameObject(map);

	enem.reserve(10);
	for (int i = 0; i < 10; i++) {
		int Ran = rand() % 3;
		Enemy* enemy = new Enemy;
		enem.push_back(enemy);
		float EZpos = 0.0f;
		if (Ran == 0)
		{
			 EZpos = 0.0f;
		}
		else if(Ran == 1)
		{
			 EZpos =2.0f;
		}
		else if (Ran == 2)
		{
			EZpos = -2.0f;
		}
		enemy->Start(D3DXVECTOR3(-3.5f + 4.8f * -i, 7.0f, EZpos),i);
	/*	for (int i = 0; i < 4; i++){
			Bullet* bullet = new Bullet;
			Bullets.push_back(bullet);

			bullet->Start(enemy->Getpos(),i);
		}*/
	}
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
	while (bulletIt != Bullets.end()) {
		if (!(*bulletIt)->GetBulletflg()) {
			bulletIt = Bullets.erase(bulletIt);
		}
		else {
			bulletIt++;
		}
	}

	player.Update();
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
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);
	camera.Update();
	//GoMgr.Update();
	map.Update();

}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	//GoMgr.Draw();
	player.Draw();
	for (auto enemy : enem)
	{
		enemy->Draw();
	}
	map.Draw();
	for (auto bullet : Bullets)
	{
		bullet->Draw();
	}
}
