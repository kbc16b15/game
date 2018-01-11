/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include "Scene.h"

/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
	srand((unsigned int)time(NULL));
	m_player = new Player;
	m_map = new Map;
	m_renderTarget = new CRenderTarget;
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{

	delete m_player;
	delete m_map;
	//delete g_physicsWorld;
	delete m_renderTarget;

	if (m_sound != nullptr)
	{
		m_sound->Release();
		m_sound = nullptr;
	}

	if (m_soundEngine != nullptr)
	{
		m_soundEngine->Release();
		m_soundEngine = nullptr;
	}

	//bullet�̏���
	for (auto bullet : m_bullets) {
		delete bullet;
	}
	auto bulletIt = m_bullets.begin();
	while (bulletIt != m_bullets.end())
	{
		bulletIt = m_bullets.erase(bulletIt);
	}
	//enem�̏���
	/*for (auto Enemynum : m_enem) {
		delete Enemynum;
	}
	auto enemyIt = m_enem.begin();
	while (enemyIt != m_enem.end())
	{
		enemyIt = m_enem.erase(enemyIt);
	}*/
	//Tenem�̏���
	
	auto TenemyIt = m_tenem.begin();
	while (TenemyIt != m_tenem.end()) {

		TenemyIt = m_tenem.erase(TenemyIt);

	}
	for (auto TEnemynum : m_tenem)
	{
		if(TEnemynum!=nullptr)
		{
			delete TEnemynum;
			TEnemynum = nullptr;
		}
		
	}
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Init()
{
	g_fade->StartFadeIn();
	//�J�����������B
	m_gameCamera.Init();
	//�v���C���[������
	m_player->Start();
	//�}�b�v���������B
	m_map->Init();
	//�p�[�e�B�N���̏�����
	/*SParticleEmitParameter param;
	param.texturePath = "star.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 3.0f, 0.0f);*/
	//param.position = m_player->Getpos();
	//m_particleEmitter.Init(param);
	//�摜�\��
	for (int i = 0;i <= m_hpMaxNum;i++)
	{
		m_hud[i].Initialize("Assets/Sprite/HP.png", m_hppos);
		m_hppos.x += 100.0f;
	}
	//m_key.Initialize("Assets/Sprite/key.png", m_keypos);
	//m_rock.Setalfa(0.5f);
	//m_rock.Initialize("Assets/Sprite/Rock.jpg", m_rockpos);
	//�X�v���C�g�̐���
	CreateSprite();

	/*m_soundEngine = new SoundEngine();
	m_soundEngine->Init();
	m_sound = new Sound();
	m_sound->Init("Assets/Sound/bgm.wav",false);
	m_sound->Play(true);
	m_sound->SetVolume(0.5f);*/

	m_renderTarget->Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A8R8G8B8,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0
	);
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
	//param.position = m_player->Getpos();
	/*m_soundEngine->Update();
	m_sound->Update();*/
	m_pad.Update();
	//�����p�̃��C�g�̈ʒu�̐ݒ�
	D3DXVECTOR3 toPos = m_player->Getpos();
	toPos.y += 7.0f;
	g_shadowmap->SetviewPosition(toPos);
	g_shadowmap->SetviewTarget(m_player->Getpos());

	D3DXVECTOR3 Ppos = m_player->Getpos();

	switch (GAME){
	case START:
		switch(m_state){
		case WaitFadeIn:
			if (!g_fade->isExecute())
			{
				m_state = Run;
			}
			break;
		case Run:
			if (m_player->PlayerDeath()|| Ppos.y < -9.0f|| m_nextflg) {
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (m_nextflg&& !g_fade->isExecute())
			{
				if (m_map->GetStage() == m_map->STAGE1)
				{
					g_scene->SceneChange(g_scene->CHANGEGAME2);

				}
				else if (m_map->GetStage() == m_map->STAGE2)
				{
					g_scene->SceneChange(g_scene->CHANGETITLE);
				}
			}
			else if (!g_fade->isExecute())
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

	/*for (auto enemy : m_enem)
	{
		enemy->Update();
	}*/
	for (auto Tenemy : m_tenem)
	{
		Tenemy->Update();
	}
	for (auto bullet : m_bullets)
	{
		bullet->Update();
	}
	//�摜�̃A�b�v�f�[�g
	for (int i = 0;i < m_hpNum;i++)
	{
		m_hud[i].Update();
	}

	/*auto enemyIt = m_enem.begin();
	while (enemyIt != m_enem.end()) {
		if ((*enemyIt)->GetDeathflg()){
			enemyIt = m_enem.erase(enemyIt);
		}
		else {
			enemyIt++;
		}
	}*/

	auto TenemyIt = m_tenem.begin();
	while (TenemyIt != m_tenem.end()) {
		if ((*TenemyIt)->GetDeathflg()) {
			
			for (auto TEnemynum : m_tenem)
			{
				if (TEnemynum->GetDeathflg())
				{
					delete TEnemynum;
					TEnemynum = nullptr;
				}
			}
			TenemyIt = m_tenem.erase(TenemyIt);
		}
		else {
			TenemyIt++;
		}
	}

	auto bulletIt = m_bullets.begin();
	while (bulletIt != m_bullets.end()) {
		if (!(*bulletIt)->GetBulletflg()) {
			bulletIt = m_bullets.erase(bulletIt);
		}
		else {
			bulletIt++;
		}
	}

	//m_key.Update();
	//m_rock.Update();
	//GoMgr.Update();
	m_gameCamera.Update();
	m_player->Update();
	m_map->Update();
	//m_particleEmitter.Update();
	
	//if (GetAsyncKeyState('G'))
	//{
	//	//���̃X�e�[�W��
	//	NextStage();
	//}

}
/*!
 * @brief	�`��B
 */
void Game::Render()
{

	//GoMgr.Draw();
	m_map->Draw();
	//���̂ɎՕ�����Ă���Ƃ��ɂ����`�悷��
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z�l���������܂Ȃ��悤�ɂ���
	m_player->Draw(&m_gameCamera.Getcamera().GetViewMatrix(), &m_gameCamera.Getcamera().GetProjectionMatrix(),true, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	m_player->Draw(&m_gameCamera.Getcamera().GetViewMatrix(), &m_gameCamera.Getcamera().GetProjectionMatrix(), false, false);

	//�p�[�e�B�N���̕`��
	/*g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_particleEmitter.Render(m_gameCamera.Getcamera().GetViewMatrix(), m_gameCamera.Getcamera().GetProjectionMatrix());
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);*/


	//for (auto enemy : m_enem)
	//{
	//	enemy->Draw();
	//}

	for (auto Tenemy : m_tenem)
	{
		Tenemy->Draw();
	}
	
	for (auto bullet : m_bullets)
	{
		bullet->Draw();
	}
	
	for (int i = 0;i < m_hpNum;i++)
	{
		m_hud[i].Draw(m_sprite);
	}
	
	//m_key.Draw(m_sprite);
	/*if (m_gunflg)
	{
		m_rock.Draw(m_sprite);
	}*/
	m_bloom.Draw();

}

void Game::GameEnd()
{
	g_scene->SceneChange(g_scene->CHANGEEND);

}

void Game::NextStage()
{
	m_nextflg = true;

}

HRESULT Game::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}