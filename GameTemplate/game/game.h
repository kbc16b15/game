/*!
 * @brief	ゲームクラス。
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

	//ゲームオーバー
	void GameEnd();

	//次のステージに行く
	void NextStage();

	//カメラの取得
	Camera* GetCamera()
	{
		return &camera.Getcamera();
	}
	//プレイヤーの取得
	Player* GetPlayer()
	{
		return &player;
	}
	Map* GetMap()
	{
		return &map;
	}
	//弾の追加
	void AddBullets(Bullet* bullet)
	{
		Bullets.push_back(bullet);
	}
	//弾の取得
	std::list<Bullet*>* GetBullet()
	{
		return &Bullets;
	}
	//敵の追加
	void AddEnemy(Enemy* enemy)
	{
		enem.push_back(enemy);
	}
	//追従敵の追加
	void AddTEnemy(trackingEnemy* enemy)
	{
		Tenem.push_back(enemy);
	}
	//スプライト生成関数
	HRESULT CreateSprite();
	//ダメージ処理
	void Damage(int dame)
	{
		Hpnum -= dame;
	}
	//体力の回復
	void Heal(int healval)
	{
		
		Hpnum += healval;
		if (Hpnum > 3) { Hpnum = 3; }
	}
	//HPの取得
	int GetHp()
	{
		return Hpnum;
	}
private:
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};

	enum Select {
		NO,
		START,
		BREAK,
	};
	Select GAME = START;
	EState      m_state = Run;
	//GameObjectManager GoMgr;
	Sound			m_Sound;
	std::list<Bullet*>	Bullets;				//バレットのリスト
	std::vector<Enemy*>	enem;					//エネミーのvector
	std::vector<trackingEnemy*> Tenem;			//追従エネミー
	ShadowMap			shadowMap;				//シャドウマップ
	gameCamera			camera;					//ゲームカメラ
	Player				player;					//プレイヤー
	Map					map;					//マップ
	int				Hpnum = 3;					//HP量
	HUD				m_Hud[3];					//画像表示の変数
	HUD				Key;						//鍵
	HUD				rock;
	LPD3DXSPRITE	m_Sprite;					//スプライト
	D3DXVECTOR2 Hppos = { 120.0f,80.0f };		//HP座標
	D3DXVECTOR2 Keypos = { 120.0f, 200.0f };	//鍵座標
	D3DXVECTOR2 rockpos = { 700.0f,250.0f };	//照準座標
	bool Gunflg = false;
	Pad				m_pad;
	D3DXVECTOR3 rockCamera;
};

extern Game* game;