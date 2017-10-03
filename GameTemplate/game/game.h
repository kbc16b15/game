/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "HUD.h"
#include "gameCamera.h"
//#include "IGameObject.h"
//#include "GameObjectManager.h"

/*!
 * @brief	�Q�[���N���X�B
 */
class Game{
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
	void Start();
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
	void NextStage();

	//�J�����̎擾
	Camera* GetCamera()
	{
		return &camera.Getcamera();
	}
	//�v���C���[�̎擾
	Player* GetPlayer()
	{
		return &player;
	}
	Map* GetMap()
	{
		return &map;
	}
	//�e�̒ǉ�
	void AddBullets(Bullet* bullet)
	{
		Bullets.push_back(bullet);
	}
	//�G�̒ǉ�
	void AddEnemy(Enemy* enemy)
	{
		enem.push_back(enemy);
	}
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();
	//�_���[�W����
	void Damage(int dame)
	{
		Hpnum -= dame;
	}
	//�̗͂̉�
	void Heal(int healval)
	{
		
		Hpnum += healval;
		if (Hpnum > 3) { Hpnum = 3; }
	}
	//HP�̎擾
	int GetHp()
	{
		return Hpnum;
	}
private:
	//GameObjectManager GoMgr;
	std::list<Bullet*>	Bullets;				//�o���b�g�̃��X�g
	std::vector<Enemy*>	enem;					//�G�l�~�[��vector
	gameCamera			camera;					//�Q�[���J����
	Player				player;					//�v���C���[
	Map					map;					//�}�b�v
	int				Hpnum = 3;					//HP��
	HUD				m_Hud[3];					//�摜�\���̕ϐ�
	HUD				Key;						//��
	LPD3DXSPRITE	m_Sprite;					//�X�v���C�g
	D3DXVECTOR2 Hppos = { 120.0f,80.0f };		//HP���W
	D3DXVECTOR2 Keypos = { 120.0f, 200.0f };	//�����W
};

extern Game* game;