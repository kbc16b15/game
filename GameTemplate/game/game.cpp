/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "SceneManager.h"
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
#include "BossEnemy.h"
#include "BossHp.h"
#include "Silhouette.h"

//�R���X�g���N�^�B
Game::Game()
{
	Player::Create();
	PlayerHp::Create();
	BulletManager::Create();
	EnemyManager::Create();
	Map::Create();
	gameCamera::Create();
	Bloom::Create();
	m_silhouette = new Silhouette;
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
	if (m_bgmSound != nullptr)
	{
		m_bgmSound->Release();
		m_bgmSound = nullptr;
	}
	
	Player::GetInstance().Destroy();
	PlayerHp::GetInstance().Destroy();
	EnemyManager::GetInstance().Release();
	BulletManager::GetInstance().Release();
	Map::GetInstance().Destroy();
	gameCamera::GetInstance().Destroy();
	Bloom::GetInstance().Destroy();
	delete m_silhouette;
}

void Game::GameRelease()
{
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Map::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(m_silhouette);
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Player::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&EnemyManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Bloom::GetInstance());

}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Init()
{


	const float SoundVolume = 0.2f;
	m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/�A�o�^�[��.wav", false);
	m_bgmSound->SetVolume(SoundVolume);
	m_bgmSound->Play(true);
	//�v���C���[������
	Player::GetInstance().Init();
	PlayerHp::GetInstance().Init();
	//�}�b�v��������
	Map::GetInstance().SetStage(m_stageNo);
	Map::GetInstance().Init();

	//�J�����������B
	gameCamera::GetInstance().Init();
	//�o�^
	GameObjectManager::GetGameObjectManager().AddGameObject(&Map::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(m_silhouette);
	GameObjectManager::GetGameObjectManager().AddGameObject(&Player::GetInstance());
	
	GameObjectManager::GetGameObjectManager().AddGameObject(&PlayerHp::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&gameCamera::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&BulletManager::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&EnemyManager::GetInstance());


	GameObjectManager::GetGameObjectManager().AddGameObject(&Bloom::GetInstance());

}

/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	if (m_bgmSound != nullptr) {
		if (m_bgmSound->IsPlaying())
			m_bgmSound->Update();
	}

	//�V���h�E
	SetShadow();
	//�t�F�[�h
	SceneFade();//�Q�[���V�[�����f���[�g����\��������?

}
/*!
 * @brief	�`��B
 */
void Game::Draw()
{
	if (!m_isLoadEnd)
	{
		m_isLoadEnd = true;
	}
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
		if (!Fade::GetInstance().isExecute()&&m_isLoadEnd) {
			Fade::GetInstance().StartFadeIn();
			m_state = Run;
		}
		break;
	case Run:
		//�Q�[���I�[�o�[
		if (Player::GetInstance().GetPlayerDeath() || toPos.y < m_killZ) {
			Player::GetInstance().SetDeath(true);
			if (&BossEnemy::GetInstance()!=NULL)
			{
				GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossEnemy::GetInstance());
				GameObjectManager::GetGameObjectManager().DeleteGameObject(&BossHp::GetInstance());
				BossHp::GetInstance().Destroy();
				BossEnemy::GetInstance().Destroy();
			}
			m_isEnd = true;
			Fade::GetInstance().StartFadeOut();
			m_state = WaitFadeOut;
			
		}
		//���̃X�e�[�W��
		else if (m_isNext)
		{
			if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE1&&!m_isNextTo)
			{
				m_stageNo = 1;
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
				m_isNextTo = true;

			}
			else if (Map::GetInstance().GetStage() == Map::GetInstance().STAGE2&&!m_isNextTo)
			{
				m_stageNo = 2;
				Fade::GetInstance().StartFadeOut();
				m_state = WaitFadeOut;
				m_isNext = false;
				m_isNextTo = true;
			}
		}
		//�N���A�V�[��
		else if (m_isClear)
		{
			m_state = WaitFadeOut;
			//m_isClear = false;
		}
		break;
	case WaitFadeOut:
		if(!Fade::GetInstance().isExecute())
		{
			GameRelease();
			if (m_isClear)
			{
				SceneManager::ChangeScene(SceneManager::CLEAR);
			}
			else if (m_isEnd)
			{
				SceneManager::ChangeScene(SceneManager::RESULT);
			}
			else if (m_stageNo == 1 && m_isNextTo)
			{
				SceneManager::ChangeScene(SceneManager::GAME2);
			}
			else if(m_stageNo==2&&m_isNextTo)
			{
				SceneManager::ChangeScene(SceneManager::GAME3);
			}
		}
		
		break;
	default:
		break;
	}
}