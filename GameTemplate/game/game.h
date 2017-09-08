/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "Image.h"
 //#include "HUD.h"
//#include "MoveObject.h"
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

	Camera* GetCamera()
	{
		return &camera;
	}

	Player* GetPlayer()
	{
		return &player;
	}
	Image* GetImage()
	{
		return &image;
	}

	void AddBullets(Bullet* bullet)
	{
		Bullets.push_back(bullet);
	}

	void AddEnemy(Enemy* enemy)
	{
		enem.push_back(enemy);
	}

private:
	//GameObjectManager GoMgr;
	std::list<Bullet*> Bullets;
	std::vector<Enemy*> enem;
	D3DXVECTOR3		toCameraPos;
	Camera			camera;
	Player			player;
	Map				map;
	Image			image;
};

extern Game* game;