#pragma once
#include "Sound.h"
#include "IScene.h"
#include "GameObjectManager.h"
class Silhouette;
class Player;
class PlayerHp;
class BossEnemy;
class BossHp;
class EnemyManager;
class BulletManager;
class gameCamera;
class Map;
class Bloom;
/*!
 * @brief	�Q�[���N���X�B
 */
class Game :public IScene
{
public:
	//�R���X�g���N�^
	Game();
	//�f�X�g���N�^
	~Game();
	//�N���֐�
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�V���h�E�̈ʒu�ݒ�
	void SetShadow();
	//�t�F�[�h
	void SceneFade();
	//�Q�[���V�[���̊J��
	void GameRelease();

	//�Q�[���I���̃t���O�̎擾
	bool GetGameEnd()
	{
		return m_isEnd;
	}
	//���̃X�e�[�W��
	void StageNext()
	{
		m_isNext = true;
	}
	//�N���A
	void StageClear(bool isClear)
	{
		m_isClear = isClear;
	}
	//BGM�X�g�b�v
	void BgmStop()
	{
		if (m_bgmSound != nullptr)
			m_bgmSound->Stop();
	}
	//�X�e�[�W�Z�b�g
	void SetStage(int No)
	{
		m_stageNo = No;
	}

	Player& GetPlayer()
	{
		return *m_player;
	}

	PlayerHp& GetPlayerHp()
	{
		return *m_playerHp;
	}

	EnemyManager& GetEnemyManager()
	{
		return *m_enemyManager;
	}

	BulletManager& GetBulletManager()
	{
		return *m_bulletManager;
	}

	gameCamera& GetGameCamara()
	{
		return *m_gameCamera;
	}

	Map& GetMap()
	{
		return *m_map;
	}

	/*void CreateBoss(BossEnemy boss)
	{
		m_bossEnemy = &boss;
		GameObjectManager::GetGameObjectManager().AddGameObject(m_bossEnemy);


	}

	void CreateBossHp(BossHp bossHp)
	{
		m_bossHp = &bossHp;
		GameObjectManager::GetGameObjectManager().AddGameObject(m_bossHp);
	}*/

	BossEnemy& GetBoss()
	{
		return *m_bossEnemy;
	}

	BossHp& GetBossHp()
	{
		return *m_bossHp;
	}

	void SetBossBattle(bool isBoss)
	{
		m_isBossBattle = isBoss;
	}
private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState			m_state = WaitFadeIn;		//�t�F�[�h�̏��
	Silhouette*		m_silhouette = nullptr;		
	Player*			m_player = nullptr;			
	PlayerHp*		m_playerHp = nullptr;		
	BossEnemy*		m_bossEnemy = nullptr;		
	BossHp*			m_bossHp = nullptr;			
	EnemyManager*	m_enemyManager = nullptr;
	BulletManager*	m_bulletManager=nullptr;	
	gameCamera*		m_gameCamera=nullptr;		
	Map*			m_map=nullptr;				
	Bloom*			m_bloom=nullptr;			


	Sound*			m_bgmSound=nullptr;			//�T�E���h
	const float		m_killZ = -10.0f;			//�v���C���[�����ʍ���
	bool			m_isNext = false;			//���̃X�e�[�W��
	bool			m_isClear = false;			//�N���A
	bool			m_isEnd = false;			//�Q�[���I�[�o�[
	bool			m_isBossBattle = false;
	int				m_stageNo=0;
};