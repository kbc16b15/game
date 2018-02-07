#pragma once
#include "MapObject.h"
class MapManager
{
public:
	//MapManager();
	~MapManager();

	//�}�b�v�̓ǂݍ���
	void AddMap(MapObject* go);
	//�}�b�v�̏���
	void DeleteMap(MapObject* go);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�J��
	void Release();
	//�C���X�^���X�̐���
	static  void MapManager::Create()
	{
		if (!m_mapManager)
		{
			m_mapManager = new MapManager;
		}
	}

	//�C���X�^���X�̏���
	static  void MapManager::Destroy()
	{
		delete m_mapManager;
		m_mapManager = nullptr;
	}
	//�C���X�^���X�̎擾
	static MapManager& GetMapManager()
	{
		return *m_mapManager;
	}


private:
	MapManager();
	std::list<MapObject*> m_mapList;		//���N���X�̃��X�g
	static MapManager* m_mapManager;
};

