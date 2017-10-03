/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "Scene.h"
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

}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	g_fade->StartFadeIn();
	//�������[���h��������
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//�J�����������B
	camera.Init();
	//�}�b�v���������B
	map.Init(/*mapChipInfo*/);
	//�v���C���[���������B
	player.Start();
	//�摜�\��
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
	//�摜�̃A�b�v�f�[�g
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
 * @brief	�`��B
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
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}