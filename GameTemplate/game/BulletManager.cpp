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
	//bullet�̏���
	for (auto bullet : m_bullets) {
		delete bullet;
	}
	auto bulletIt = m_bullets.begin();
	while (bulletIt != m_bullets.end())
	{
		bulletIt = m_bullets.erase(bulletIt);
	}


	//bulletWeapon�̏���
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
	//�o���b�g�̃A�b�v�f�[�g
	for (auto bullet : m_bullets)
	{
		bullet->Update();
	}

	//�G�̃A�b�v�f�[�g
	for (auto BulletWeaponIt : m_bulletWeapon)
	{
		BulletWeaponIt->Update();
	}

	BulletHud::GetInstance().Update();
	//�o���b�g�̎��S����
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
	//�o���b�g�̕`��
	for (auto bullet : m_bullets)
	{
		bullet->Draw();
	}
	//BulletHud::GetInstance().Draw();

	//�G�̕`��
	for (auto BulletWeaponIt : m_bulletWeapon)
	{
		BulletWeaponIt->Draw();
	}
}

Bullet* BulletManager::CreateBullet(int id)
{
	//�o���b�g�̎g���܂킵��������
	for (int i=0;i < m_bullets.size();i++)
	{
		if (m_bullets[i]->GetDeathflg() && id == m_bullets[i]->GetID()) {
			return m_bullets[i];//������Bullet���g�p����
		}
	}
	Bullet* newBullet = new Bullet;//�V����Bullet�̐���

	if (newBullet)
	{
		m_bullets.push_back(newBullet);
	}
	return newBullet;
}