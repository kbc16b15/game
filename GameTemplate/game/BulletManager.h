#pragma once
//#include "IGameObject.h"
#include "Bullet.h"
#include "BulletWeapon.h"
class BulletManager :
	public IGameObject
{
public:
	//BulletManager();
	//デストラクタ
	~BulletManager();
	//void Init();
	//更新
	void Update();
	//描画
	void Draw();

	void Release();
	//バレットの生成
	//Bullet* CreateBullet(int id);
	//弾の追加
	void AddBullets(Bullet* bullet)
	{
		m_bullets.push_back(bullet);
	}

	//弾の取得
	std::vector<Bullet*> GetBullet()
	{
		return m_bullets;
	}

	//インスタンスの生成
	static void BulletManager::Create()
	{
		if (!m_bulletManager)
		{
			m_bulletManager = new BulletManager;
		}

	}
	//バレット敵の追加
	void AddBulletWeapon(BulletWeapon* enemy)
	{
		m_bulletWeapon.push_back(enemy);
	}
	//インスタンスの取得
	static BulletManager& GetInstance()
	{
		return *m_bulletManager;
	}

	//インスタンスの消去
	static  void BulletManager::Destroy()
	{
		delete m_bulletManager;
		m_bulletManager = nullptr;
	}
private:
	//コンストラクタ
	BulletManager();
	static BulletManager* m_bulletManager;//インスタンス
private:
	std::vector<Bullet*>	m_bullets;			//バレットのリスト
	//std::unique_ptr<Bullet*> m_bullets;
	std::list<BulletWeapon*> m_bulletWeapon;		//バレット
};

