#include "stdafx.h"
#include "BulletManager.h"
#include "BulletHud.h"
#include "GameObjectManager.h"

BulletManager *BulletManager::m_bulletManager = NULL;

BulletManager::BulletManager()
{
	BulletHud::Create();
	BulletHud::GetInstance().Init();
}


BulletManager::~BulletManager()
{
	//bulletの消去
	for (auto bullet : m_bullets) {
		delete bullet;
	}
	auto bulletIt = m_bullets.begin();
	while (bulletIt != m_bullets.end())
	{
		bulletIt = m_bullets.erase(bulletIt);
	}


	//bulletWeaponの消去
	auto BulletWeaponIt = m_bulletWeapon.begin();
	while (BulletWeaponIt != m_bulletWeapon.end()) {

		BulletWeaponIt = m_bulletWeapon.erase(BulletWeaponIt);
	}
	for (auto BulletWeaponnum : m_bulletWeapon)
	{
		if (BulletWeaponnum != nullptr)
		{
			delete BulletWeaponnum;
			BulletWeaponnum = nullptr;
		}
	}
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&BulletHud::GetInstance());
	BulletHud::GetInstance().Destroy();
}

void BulletManager::Update()
{
	//バレットのアップデート
	for (auto bullet : m_bullets)
	{
		bullet->Update();
	}

	//敵のアップデート
	for (auto BulletWeaponIt : m_bulletWeapon)
	{
		BulletWeaponIt->Update();
	}

	BulletHud::GetInstance().Update();
	//バレットの死亡判定
	//auto bulletIt = m_bullets.begin();
	//while (bulletIt != m_bullets.end()) {
	//	if (!(*bulletIt)->GetBulletflg()) {
	//		bulletIt = m_bullets.erase(bulletIt);
	//	}
	//	else {
	//		bulletIt++;
	//	}
	//}
}

void BulletManager::Draw()
{
	//バレットの描画
	for (auto bullet : m_bullets)
	{
		bullet->Draw();
	}
	//BulletHud::GetInstance().Draw();

	//敵の描画
	for (auto BulletWeaponIt : m_bulletWeapon)
	{
		BulletWeaponIt->Draw();
	}
}

Bullet* BulletManager::CreateBullet(int id)
{
	//バレットの使いまわしをしたい
	for (int i=0;i < m_bullets.size();i++)
	{
		if (m_bullets[i]->GetDeathflg() && id == m_bullets[i]->GetID()) {
			return m_bullets[i];//既存のBulletを使用する
		}
	}
	Bullet* newBullet = new Bullet;//新しいBulletの生成

	if (newBullet)
	{
		m_bullets.push_back(newBullet);
	}
	return newBullet;
}