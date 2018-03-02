#pragma once
#include "Enemy.h"
#include "trackingEnemy.h"

#include "IGameObject.h"
class EnemyManager :
	public IGameObject
{
public:
	//コンストラクタ
	//デストラクタ
	EnemyManager();
	~EnemyManager();

	//初期化
	//void Init();
	//更新
	void Update();
	//描画
	void Draw();

	void Release();
	
	//敵の取得
	std::list<trackingEnemy*> GetEnemy()
	{
		return m_tenem;
	}
	//追従敵の追加
	void AddTrackingEnemy(trackingEnemy* enemy)
	{
		m_tenem.push_back(enemy);
	}

//	//インスタンスの生成
//	static void EnemyManager::Create()
//	{
//		if (!m_enemyManager)
//		{
//			m_enemyManager = new EnemyManager;
//		}
//
//	}
//
//	//インスタンスの取得
//	static EnemyManager& GetInstance()
//	{
//		return *m_enemyManager;
//	}
//
//	//インスタンスの消去
//	static  void EnemyManager::Destroy()
//	{
//		delete m_enemyManager;
//		m_enemyManager = nullptr;
//	}
//
//private:
//	static EnemyManager* m_enemyManager;//インスタンス
private:
	//std::list<Enemy*>	m_enem;				//エネミー
	std::list<trackingEnemy*> m_tenem;		//追従エネミー

};

