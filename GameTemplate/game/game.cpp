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
	//�v���C���[���������B
	player.Start();
	//�}�b�v���������B
	map.Init();
	float pp = 0;
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Addpos(pp);
		m_Hud[i].Initialize();
		pp += 100;
		
	}
	CreateSprite();
	//Player* pl = new Player();
	//GoMgr.AddGameObject(pl);
	//Enemy* en = new Enemy();
	//GoMgr.AddGameObject(en);
	//Map* map = new Map();
	//GoMgr.AddGameObject(map);

//	enem.reserve(10);
//	for (int i = 0; i < 5; i++) {
//		int Ran = rand() % 3;
//		Enemy* enemy = new Enemy;
//		enem.push_back(enemy);
//		float EZpos = 0.0f;
//		float EXpos = 0.0f;
//		if (Ran == 0)
//		{
//			 EZpos = 0.0f;
//		}
//		else if(Ran == 1)
//		{
//			 EZpos =2.0f;
//		}
//		else if (Ran == 2)
//		{
//			EZpos = -2.0f;
//		}
//		enemy->Start(D3DXVECTOR3(6.0f * -i, 4.0f, EZpos),i);
//	}
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
	
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);
	player.Update();
	camera.Update();
	//GoMgr.Update();
	map.Update();
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Update();
	}
}
/*!
 * @brief	�`��B
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
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Draw(m_Sprite);
	}
}


HRESULT Game::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}