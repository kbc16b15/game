/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"


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