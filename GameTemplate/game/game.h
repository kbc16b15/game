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
#include "SoundEngine.h"
#include "RenderTarget.h"
#include "bloom.h"
#include "ParticleEmitter.h"
//#include "BaseScene.h"
//#include "IGameObject.h"
//#include "GameObjectManager.h"

/*!
 * @brief	ゲームクラス。
 */
class Game 
{
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
	void Init();
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
	//void NextStage();

	//スプライト生成関数
	HRESULT CreateSprite();
	//カメラの取得
	Camera* GetCamera()
	{
		return &m_gameCamera.Getcamera();
		//return camera;
	}
	//プレイヤーの取得
	Player* GetPlayer()
	{
		return m_player;
	}
	//マップの取得
	Map* GetMap()
	{
		return m_map;
	}

	//弾の追加
	void AddBullets(Bullet* bullet)
	{
		m_bullets.push_back(bullet);
	}
	//弾の取得
	std::list<Bullet*> GetBullet()
	{
		return m_bullets;
	}
	//敵の追加
	void AddEnemy(Enemy* enemy)
	{
		m_enem.push_back(enemy);
	}
	//追従敵の追加
	void AddTEnemy(trackingEnemy* enemy)
	{
		m_tenem.push_back(enemy);
	}

	//追従敵の取得
	/*std::vector<trackingEnemy*> GetTEnemy()
	{
		return m_tenem;
	}*/

	//ダメージ処理
	void Damage(int dame)
	{
		m_hpNum -= dame;
	}
	//体力の回復
	void Heal(int healval)
	{
		m_hpNum += healval;
		if (m_hpNum >= m_hpMaxNum) { m_hpNum = m_hpMaxNum; }
	}
	//HPの取得
	int GetHp()
	{
		return m_hpNum;
	}
	//次のステージへ
	void NextStage()
	{
		m_nextflg = true;

	}
private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//選択
	enum Select {
		NO,
		START,
		BREAK,
	};
	//GameObjectManager GoMgr;						//
	CRenderTarget*		m_renderTarget;				//ポストエフェクト用のレンダリングターゲット？
	Select				GAME = START;				//選択
	EState				m_state = Run;				//フェードの状態
	Sound*				m_bgmSound=nullptr;			//サウンド
	//SoundEngine*		m_soundEngine=nullptr;		//サウンドエンジン
	std::list<Bullet*>	m_bullets;					//バレットのリスト
	std::vector<Enemy*>	m_enem;						//エネミーのvector
	std::vector<trackingEnemy*> m_tenem;			//追従エネミー
	gameCamera			m_gameCamera;				//ゲームカメラ
	//Camera*			camera;						//カメラ
	Player*				m_player;					//プレイヤー
	Map*				m_map;						//マップ
	Bloom				m_bloom;					//ブルーム
	ParticleEmitter		m_particleEmitter;			//パーティクル
	int					m_hpMaxNum = 2;				//最大HP量
	int					m_hpNum = 3;				//HP量
	HUD					m_hud[3];					//画像表示の変数
	HUD					m_key;						//鍵
	HUD					m_rock;						//
	LPD3DXSPRITE		m_sprite;					//スプライト
	D3DXVECTOR2			m_hppos = { 120.0f,80.0f };		//HP座標
	D3DXVECTOR2			m_keypos = { 120.0f, 200.0f };	//鍵座標
	D3DXVECTOR2			m_rockpos = { 700.0f,250.0f };	//照準座標
	bool				m_gunflg = false;
	bool				m_nextflg = false;
	Pad					m_pad;
	D3DXVECTOR3			m_rockCamera;


};

extern Game* g_game;