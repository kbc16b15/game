/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include "Scene.h"

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
void Game::Init()
{
	g_fade->StartFadeIn();
	//�������[���h��������
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//camera = new Camera;
	//camera->Init();
	//�J�����������B
	gameCamera.Init();
	player.Start();
	//�}�b�v���������B
	map.Init();

	//�摜�\��
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Initialize("Assets/Sprite/HP.png", Hppos);
		Hppos.x += 100.0f;
	}
	Key.Initialize("Assets/Sprite/key.png", Keypos);
	rock.Setalfa(0.5f);
	rock.Initialize("Assets/Sprite/Rock.jpg", rockpos);

	CreateSprite();

	m_SoundEngine = new SoundEngine();
	m_SoundEngine->Init();
	m_Sound = new Sound();
	m_Sound->Init("Assets/Sound/bgm.wav");
	m_Sound->Play(true);
	m_Sound->SetVolume(0.5f);


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
	D3DXVECTOR3 Ppos = player.Getpos();
	m_SoundEngine->Update();
	m_Sound->Update();
	m_pad.Update();

	//if (player != nullptr)
	//{
		D3DXVECTOR3 toPos = player.Getpos();
		toPos.y += 7.0f;
		g_shadowmap->SetviewPosition(toPos);
		g_shadowmap->SetviewTarget(player.Getpos());
	//}
	//else
	//{
	//	g_shadowmap->SetviewTarget({ 0.0f,0.0f,0.0f });
	//	g_shadowmap->SetviewPosition({ 0.0f,10.0f,0.0f });
	//}
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
			if (player.PlayerDeath()|| Ppos.y < -9.0f) {
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (!g_fade->isExecute())
			{
				GameEnd();
			}
			break;
		}
		break;
	}

	//if (GetAsyncKeyState('L') || m_pad.IsTrigger(m_pad.enButtonLB1))
	//{
	//	Gunflg = true;
	//	camera.SetRockCamera(true);
	//	player.PlayerMoveSet(true);
	//}

	//if (GetAsyncKeyState('R') || m_pad.IsTrigger(m_pad.enButtonLB2))
	//{
	//	camera.SetRockCamera(false);
	//	Gunflg = false;
	//	player.PlayerMoveSet(false);
	//	rockpos = { 700.0f,250.0f };
	//}
	//rock.Initialize("Assets/Sprite/Rock.jpg", rockpos);

	//if (GetAsyncKeyState('Z') || m_pad.IsTrigger(m_pad.enButtonRB1)&&Gunflg)
	//{
	//	D3DXVECTOR3 Ppos = player.Getpos();
	//	D3DXVECTOR3 Cpos = camera.Getcamera().GetLookatPt();
	//	Bullet* bullet = new Bullet();
	//	bullet->Start(Ppos, { Cpos.x ,Cpos.y ,Cpos.z },0);
	//	game->AddBullets(bullet);
	//}

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
	//�摜�̃A�b�v�f�[�g
	for (int i = 0;i < Hpnum;i++)
	{
		m_Hud[i].Update();
	}
	Key.Update();
	rock.Update();
	//GoMgr.Update();
	gameCamera.Update();
	player.Update();
	//camera->Update();
	map.Update();
	g_physicsWorld->Update();
	if (GetAsyncKeyState('G'))
	{
		//���̃X�e�[�W��
		NextStage();
	}

}
/*!
 * @brief	�`��B
 */
void Game::Render()
{
	//GoMgr.Draw();
	map.Draw();
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	player.Draw(&gameCamera.Getcamera().GetViewMatrix(), &gameCamera.Getcamera().GetProjectionMatrix(),true, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	player.Draw(&gameCamera.Getcamera().GetViewMatrix(), &gameCamera.Getcamera().GetProjectionMatrix(), false, false);

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

	//g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);

	//player.Draw(&camera.Getcamera().GetViewMatrix(), &camera.Getcamera().GetProjectionMatrix(), false, false);

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
	delete m_Sound;
	m_Sound = nullptr;
	delete m_SoundEngine;
	m_SoundEngine = nullptr;
	//m_SoundEngine->Release();
	scene->SceneChange(scene->CHANGEEND);
	//scene->SceneChange(scene->END);

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
	scene->SceneChange(scene->GAME);

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