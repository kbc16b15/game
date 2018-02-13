/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "TitleScene.h"
#include "ResultScene.h"
#include "ClearScene.h"
#include "Fade.h"
#include "Map.h"
#include "ShadowMap.h"
#include "bloom.h"
#include "gameCamera.h"
#include "Player.h"
#include "PlayerHp.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "GameObjectManager.h"
//#include "MapInfo.h"

Game *Game::m_game = NULL;

//�R���X�g���N�^�B
Game::Game()
{
	//SetLight();
	//srand((unsigned int)time(NULL));

}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
	Player::GetInstance().Destroy();
	PlayerHp::GetInstance().Destroy();
	EnemyManager::GetInstance().Destroy();
	BulletManager::GetInstance().Destroy();
	Map::GetInstance().Destroy();
	gameCamera::GetInstance().Destroy();
	Bloom::GetInstance().Destroy();
	if (m_isNextTo)
	{
		/*Game::Create();
		Game::GetInstance().Init();
		Map::GetInstance().SetStage(Map::GetInstance().STAGE2);
		GameObjectManager::GetGameObjectManager().AddGameObject(&Game::GetInstance());
		m_isNextTo = false;*/
	}
}

void Game::GameRelease()
{
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Game::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Map::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Bloom::GetInstance());


	Game::GetInstance().Destroy();

}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Init()
{
	Player::Create();
	PlayerHp::Create();

	BulletManager::Create();
	EnemyManager::Create();
	Map::Create();
	gameCamera::Create();
	Bloom::Create();


	//�}�b�v���������B

	Map::GetInstance().Init();
	//�v���C���[������
	Player::GetInstance().Init();
	PlayerHp::GetInstance().Init();
	//�J�����������B
	gameCamera::GetInstance().Init();

	//�o�^
	GameObjectManager::GetGameObjectManager().AddGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&Map::GetInstance());

	GameObjectManager::GetGameObjectManager().AddGameObject(&Bloom::GetInstance());

	/*Sound**/ /*m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/bgm.wav",false);
	m_bgmSound->SetVolume(0.5f);
	m_bgmSound->Play(true);*/
	//�t�F�[�h�C��
	Fade::GetInstance().StartFadeIn();
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	//m_bgmSound->Update();
	//�V���h�E
	SetShadow();
	//�t�F�[�h
	SceneFade();//�Q�[���V�[�����f���[�g����\�������邩��Update�̈�ԉ��ɒu���Ă���

}
/*!
 * @brief	�`��B
 */
void Game::Draw()
{
	//���̂ɎՕ�����Ă���Ƃ��ɂ����`�悷��
	//g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z�l���������܂Ȃ��悤�ɂ���
	//Player::GetInstance().ShadowDraw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix(),true, false);
	//g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}


void Game::SetShadow()
{
	//�����p�̃��C�g�̈ʒu�̐ݒ�
	D3DXVECTOR3 toPos = Player::GetInstance().Getpos();
	toPos.y += 6.0f;
	ShadowMap::GetInstance().SetviewPosition(toPos);
	ShadowMap::GetInstance().SetviewTarget(Player::GetInstance().Getpos());
}

void Game::SceneFade()
{
	D3DXVECTOR3 toPos = Player::GetInstance().Getpos();
	switch (m_state) {
	case WaitFadeIn:
		if (!Fade::GetInstance().isExecute()) {
			m_state = Run;
		}
		break;
	case Run:
		if (Player::GetInstance().PlayerDeath() || toPos.y < m_killZ) {

			m_isEnd = true;
			ResultScene::Create();
			ResultScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&ResultScene::GetInstance());
			Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
		}
		else if (m_isNext)
		{
			if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE1)
			{

				/*Game::Create();
				Game::GetInstance().Init();
				Map::GetInstance().SetStage(Map::GetInstance().STAGE2);
				GameObjectManager::GetGameObjectManager().AddGameObject(&Game::GetInstance());*/
				m_isNextTo = true;
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;

			}
			else if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE2)
			{

				TitleScene::Create();
				TitleScene::GetInstance().Init();
				GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());
				//Game::GetInstance().GameRelease();
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
			}
		}
		else if (m_isClear)
		{

			ClearScene::Create();
			ClearScene::GetInstance().Init();
			GameObjectManager::GetGameObjectManager().AddGameObject(&ClearScene::GetInstance());
			//Game::GetInstance().GameRelease();
			m_state = WaitFadeOut;
			Fade::GetInstance().StartFadeOut();
			m_isClear = false;
		}
		break;
	case WaitFadeOut:
		if(!Fade::GetInstance().isExecute())
		{
			//Fade::GetInstance().StartFadeOut();
			//Game::GetInstance().GameRelease();
		}
		break;
	default:
		break;
	}

	
}