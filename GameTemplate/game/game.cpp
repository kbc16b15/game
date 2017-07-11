/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"


//gameCamera* g_gameCamera = nullptr;

/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
	for (auto bullet : Bullets) {
		delete bullet;
	}
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	//�������[���h���������B
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//�J�����������B
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(5.0f, 7.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	//�v���C���[���������B
	player.Start();
	enemy.Start({ -20.0f,3.0f,0.0f });
	/*for (auto bullet : Bullets)
	{
		bullet->Start({ -50.0f,0.5f,0.0f });
	}*/
	//�}�b�v���������B
	map.Init();
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	auto bulletIt = Bullets.begin();
	while (bulletIt != Bullets.end()) {
		if (!(*bulletIt)->GetBulletflg()) {
			//���S
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
	
	//�v���C���[�Ǐ]�J�����B
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
 * @brief	�`��B
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
