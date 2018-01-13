/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once
#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "trackingEnemy.h"
#include "Map.h"
#include "HUD.h"
#include "gameCamera.h"
#include "ShadowMap.h"
#include "Sound.h"
#include "SoundEngine.h"
#include "RenderTarget.h"
#include "bloom.h"
#include "ParticleEmitter.h"
//#include "BaseScene.h"
//#include "IGameObject.h"
//#include "GameObjectManager.h"

/*!
 * @brief	�Q�[���N���X�B
 */
class Game 
{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Game();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	 */
	void Init();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Render();

	//�Q�[���I�[�o�[
	void GameEnd();

	//���̃X�e�[�W�ɍs��
	//void NextStage();

	//�X�v���C�g�����֐�
	HRESULT CreateSprite();
	//�J�����̎擾
	Camera* GetCamera()
	{
		return &m_gameCamera.Getcamera();
		//return camera;
	}
	//�v���C���[�̎擾
	Player* GetPlayer()
	{
		return m_player;
	}
	//�}�b�v�̎擾
	Map* GetMap()
	{
		return m_map;
	}

	//�e�̒ǉ�
	void AddBullets(Bullet* bullet)
	{
		m_bullets.push_back(bullet);
	}
	//�e�̎擾
	std::list<Bullet*> GetBullet()
	{
		return m_bullets;
	}
	//�G�̒ǉ�
	void AddEnemy(Enemy* enemy)
	{
		m_enem.push_back(enemy);
	}
	//�Ǐ]�G�̒ǉ�
	void AddTEnemy(trackingEnemy* enemy)
	{
		m_tenem.push_back(enemy);
	}

	//�Ǐ]�G�̎擾
	/*std::vector<trackingEnemy*> GetTEnemy()
	{
		return m_tenem;
	}*/

	//�_���[�W����
	void Damage(int dame)
	{
		m_hpNum -= dame;
	}
	//�̗͂̉�
	void Heal(int healval)
	{
		m_hpNum += healval;
		if (m_hpNum >= m_hpMaxNum) { m_hpNum = m_hpMaxNum; }
	}
	//HP�̎擾
	int GetHp()
	{
		return m_hpNum;
	}
	//���̃X�e�[�W��
	void NextStage()
	{
		m_nextflg = true;

	}
private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//�I��
	enum Select {
		NO,
		START,
		BREAK,
	};
	//GameObjectManager GoMgr;						//
	CRenderTarget*		m_renderTarget;				//�|�X�g�G�t�F�N�g�p�̃����_�����O�^�[�Q�b�g�H
	Select				GAME = START;				//�I��
	EState				m_state = Run;				//�t�F�[�h�̏��
	Sound*				m_bgmSound=nullptr;			//�T�E���h
	//SoundEngine*		m_soundEngine=nullptr;		//�T�E���h�G���W��
	std::list<Bullet*>	m_bullets;					//�o���b�g�̃��X�g
	std::vector<Enemy*>	m_enem;						//�G�l�~�[��vector
	std::vector<trackingEnemy*> m_tenem;			//�Ǐ]�G�l�~�[
	gameCamera			m_gameCamera;				//�Q�[���J����
	//Camera*			camera;						//�J����
	Player*				m_player;					//�v���C���[
	Map*				m_map;						//�}�b�v
	Bloom				m_bloom;					//�u���[��
	ParticleEmitter		m_particleEmitter;			//�p�[�e�B�N��
	int					m_hpMaxNum = 2;				//�ő�HP��
	int					m_hpNum = 3;				//HP��
	HUD					m_hud[3];					//�摜�\���̕ϐ�
	HUD					m_key;						//��
	HUD					m_rock;						//
	LPD3DXSPRITE		m_sprite;					//�X�v���C�g
	D3DXVECTOR2			m_hppos = { 120.0f,80.0f };		//HP���W
	D3DXVECTOR2			m_keypos = { 120.0f, 200.0f };	//�����W
	D3DXVECTOR2			m_rockpos = { 700.0f,250.0f };	//�Ə����W
	bool				m_gunflg = false;
	bool				m_nextflg = false;
	Pad					m_pad;
	D3DXVECTOR3			m_rockCamera;


};

extern Game* g_game;