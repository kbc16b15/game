/*!
 * @brief	ゲームクラス。
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
 * @brief	ゲームクラス。
 */
class Game{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	Game();
	/*!
	 * @brief	デストラクタ。
	 */
	~Game();
	/*!
	 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
	 */
	void Start();
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	描画。
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