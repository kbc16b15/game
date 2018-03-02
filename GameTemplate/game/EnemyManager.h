#pragma once
#include "Enemy.h"
#include "trackingEnemy.h"

#include "IGameObject.h"
class EnemyManager :
	public IGameObject
{
public:
	//�R���X�g���N�^
	//�f�X�g���N�^
	EnemyManager();
	~EnemyManager();

	//������
	//void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();

	void Release();
	
	//�G�̎擾
	std::list<trackingEnemy*> GetEnemy()
	{
		return m_tenem;
	}
	//�Ǐ]�G�̒ǉ�
	void AddTrackingEnemy(trackingEnemy* enemy)
	{
		m_tenem.push_back(enemy);
	}

//	//�C���X�^���X�̐���
//	static void EnemyManager::Create()
//	{
//		if (!m_enemyManager)
//		{
//			m_enemyManager = new EnemyManager;
//		}
//
//	}
//
//	//�C���X�^���X�̎擾
//	static EnemyManager& GetInstance()
//	{
//		return *m_enemyManager;
//	}
//
//	//�C���X�^���X�̏���
//	static  void EnemyManager::Destroy()
//	{
//		delete m_enemyManager;
//		m_enemyManager = nullptr;
//	}
//
//private:
//	static EnemyManager* m_enemyManager;//�C���X�^���X
private:
	//std::list<Enemy*>	m_enem;				//�G�l�~�[
	std::list<trackingEnemy*> m_tenem;		//�Ǐ]�G�l�~�[

};

