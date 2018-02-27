#pragma once
//#include "IGameObject.h"
#include "Bullet.h"
#include "BulletWeapon.h"
class BulletManager :
	public IGameObject
{
public:
	//BulletManager();
	//�f�X�g���N�^
	~BulletManager();
	//void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();

	void Release();
	//�o���b�g�̐���
	//Bullet* CreateBullet(int id);
	//�e�̒ǉ�
	void AddBullets(Bullet* bullet)
	{
		m_bullets.push_back(bullet);
	}

	//�e�̎擾
	std::vector<Bullet*> GetBullet()
	{
		return m_bullets;
	}

	//�C���X�^���X�̐���
	static void BulletManager::Create()
	{
		if (!m_bulletManager)
		{
			m_bulletManager = new BulletManager;
		}

	}
	//�o���b�g�G�̒ǉ�
	void AddBulletWeapon(BulletWeapon* enemy)
	{
		m_bulletWeapon.push_back(enemy);
	}
	//�C���X�^���X�̎擾
	static BulletManager& GetInstance()
	{
		return *m_bulletManager;
	}

	//�C���X�^���X�̏���
	static  void BulletManager::Destroy()
	{
		delete m_bulletManager;
		m_bulletManager = nullptr;
	}
private:
	//�R���X�g���N�^
	BulletManager();
	static BulletManager* m_bulletManager;//�C���X�^���X
private:
	std::vector<Bullet*>	m_bullets;			//�o���b�g�̃��X�g
	//std::unique_ptr<Bullet*> m_bullets;
	std::list<BulletWeapon*> m_bulletWeapon;		//�o���b�g
};

