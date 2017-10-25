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
	rock.Setalfa(0.5f);
	rock.Initialize("Assets/Sprite/Rock.jpg", rockpos);

	CreateSprite();

	shadowMap.Init();

	//m_Sound.Start("Assets/Sound/Machi.wav");
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
	D3DXVECTOR3 Ppos = player.Getpos();

	//m_Sound.Update();
	switch (GAME) {
	case START:
		switch (m_state) {
		case WaitFadeIn:
			if (!g_fade->isExecute())
			{
				m_state = Run;
			}
			break;
		case Run:
			if (Hpnum < 1 || Ppos.y < -2.0f || GetAsyncKeyState('S')) {

				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (!g_fade->isExecute())
			{
				GameEnd();
				return;

			}
			break;
		}
		break;
	}

	m_pad.Update();
	if (GetAsyncKeyState('L') || m_pad.IsTrigger(m_pad.enButtonLB1))
	{
		Gunflg = true;
		camera.SetRockCamera(true);
		player.PlayerMoveSet(true);
	}

	if (GetAsyncKeyState('R') || m_pad.IsTrigger(m_pad.enButtonLB2))
	{
		camera.SetRockCamera(false);
		Gunflg = false;
		player.PlayerMoveSet(false);
		rockpos = { 700.0f,250.0f };
	}
	rock.Initialize("Assets/Sprite/Rock.jpg", rockpos);

	if (GetAsyncKeyState('Z') || m_pad.IsTrigger(m_pad.enButtonRB1)&&Gunflg)
	{
		D3DXVECTOR3 Ppos = player.Getpos();
		D3DXVECTOR3 Cpos = camera.Getcamera().GetLookatPt();
		Bullet* bullet = new Bullet();
		bullet->Start(Ppos, { Cpos.x ,Cpos.y ,Cpos.z },0);
		game->AddBullets(bullet);
	}

	auto enemyIt = enem.begin();
	while (enemyIt != enem.end()) {
		if ((*enemyIt)->GetDeathflg()) {
			enemyIt = enem.erase(enemyIt);
		}
		else {
			enemyIt++;
		}
	}

	auto TenemyIt = Tenem.begin();
	while (TenemyIt != Tenem.end()) {
		if ((*TenemyIt)->GetDeathflg()) {
			TenemyIt = Tenem.erase(TenemyIt);
		}
		else {
			TenemyIt++;
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

	for (auto enemy : enem)
	{
		enemy->Update();
	}
	for (auto Tenemy : Tenem)
	{
		Tenemy->Update();
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
	rock.Update();
	//GoMgr.Update();
	g_physicsWorld->Update();
	player.Update();
	camera.Update();
	map.Update();
	shadowMap.Update();

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
	D3DXVECTOR3 toPos = player.Getpos();
	shadowMap.SetviewTarget(player.Getpos());
	toPos.y = 7.0f;
	//toPos.x += 5.0f;
	shadowMap.SetviewPosition(toPos);
	shadowMap.Update();

	shadowMap.Draw();
	//GoMgr.Draw();
	map.Draw();
	player.Draw(camera.Getcamera().GetViewMatrix(), camera.Getcamera().GetProjectionMatrix(), false, false);

	for (auto enemy : enem)
	{
		enemy->Draw();
	}

	for (auto Tenemy : Tenem)
	{
		Tenemy->Draw();
	}
	
	for (auto bullet : Bullets)
	{
		bullet->Draw();
	}
	
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Draw(m_Sprite);
	}
	
	Key.Draw(m_Sprite);
	if (Gunflg)
	{
		rock.Draw(m_Sprite);
	}
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
	for (auto TEnemynum : Tenem)
	{
		delete TEnemynum;
	}

	scene->SetScene(scene->CHANGEEND);
	scene->SceneChange();

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
	for (auto TEnemynum : Tenem)
	{
		delete TEnemynum;
	}
	scene->SceneChange();
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