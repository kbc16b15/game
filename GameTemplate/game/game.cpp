/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

//gameCamera* g_gameCamera = nullptr;

/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
	srand((unsigned int)time(NULL));

}
/*!
 * @brief	�f�X�g���N�^�B
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
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	//�������[���h��������
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//�J�����������B
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(5.0f, 7.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();
	//�}�b�v���������B
	map.Init();
	//�v���C���[���������B
	player.Start();
	//�摜�\��
	image.Init();
	//Player* pl = new Player();
	//GoMgr.AddGameObject(pl);
	//Enemy* en = new Enemy();
	//GoMgr.AddGameObject(en);
	//Map* map = new Map();
	//GoMgr.AddGameObject(map);

}
/*!
 * @brief	�X�V�B
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

	//�v���C���[�Ǐ]�J�����B
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
 * @brief	�`��B
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
