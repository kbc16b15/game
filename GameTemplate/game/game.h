/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
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

	/*Bullet* GetBullet()
	{
		return &bullet;
	}*/

	Player* GetPlayer()
	{
		return &player;
	}

	/*Enemy* GetEnemy()
	{
		return &enemy;
	}*/
	void AddBullets(Bullet* bullet)
	{

		Bullets.push_back(bullet);

	}
	std::vector<Bullet*>& GetBullets()
	{
		return Bullets;
	}

	std::vector<Enemy*>& Getenem()
	{
		return enem;
	}
private:
	D3DXVECTOR3 toCameraPos;
	Camera camera;
	Player player;
	//Enemy enemy;
	Map map;
	//Bullet bullet;
	//GameObjectManager GoMgr;
	std::vector<Bullet*> Bullets;
	std::vector<Enemy*> enem;
};

extern Game* game;