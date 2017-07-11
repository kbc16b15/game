/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"


//gameCamera* g_gameCamera = nullptr;

/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
	for (auto bullet : Bullets) {
		delete bullet;
	}
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	//物理ワールドを初期化。
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
	enemy.Start({ -20.0f,3.0f,0.0f });
	/*for (auto bullet : Bullets)
	{
		bullet->Start({ -50.0f,0.5f,0.0f });
	}*/
	//マップを初期化。
	map.Init();
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	auto bulletIt = Bullets.begin();
	while (bulletIt != Bullets.end()) {
		if (!(*bulletIt)->GetBulletflg()) {
			//死亡
			bulletIt = Bullets.erase(bulletIt);
		}
		else {
			bulletIt++;
		}
	}
	//bulletstl->push_back(bullet);
	
	player.Update();
	enemy.Update();
	for (auto bullet : Bullets)
	{
		bullet->Update();
	}
	
	//プレイヤー追従カメラ。
	D3DXVECTOR3 targetPos = player.Getpos();
	//targetPos.x += target.x;
	if (targetPos.y < 0.0f)
	{
		targetPos.y = 0.0f;
	}
	//targetPos.y += target.y;
	//targetPos.z = 0.0f;
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);
	camera.Update();
	map.Update();
}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	//bullet.Render();
	for (auto bullet : Bullets)
	{
		bullet->Render();
	}
	
	player.Render();
	enemy.Render();
	map.Draw();
}
