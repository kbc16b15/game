/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"


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

	Camera* GetCamera()
	{
		return &camera;
	}

	Bullet* GetBullet()
	{
		return &bullet;
	}

	Player* GetPlayer()
	{
		return &player;
	}
	void AddBullets(Bullet* bullet)
	{

		Bullets.push_back(bullet);

	}
	std::vector<Bullet*>& GetBullets()
	{
		return Bullets;
	}
private:
	D3DXVECTOR3 toCameraPos;
	Camera camera;
	Player player;
	Enemy enemy;
	Map map;
	Bullet bullet;
	std::vector<Bullet*> Bullets;
};

extern Game* game;