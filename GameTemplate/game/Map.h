#pragma once
//#include "MapInfo.h"
class HealItem;

struct SMapChipLocInfo {
	const char* modelName;	//���f���B
	D3DXVECTOR3	pos;		//���W�B
	D3DXQUATERNION	rot;	//��]�B
};


//template <typename T>
class Map:public IGameObject
{
public:



	//�f�X�g���N�^
	~Map();
	//������
	void Init(/*SMapChipLocInfo Info[]*/);
	//�`��
	void Draw();
	//�X�V
	void Update();

	void MapCreate(const char* mapName,int no,SMapChipLocInfo Info[]);


	//�X�e�[�W�؂�ւ�
	void SetStage(int StageNum)
	{
		m_stageNum = StageNum;

	}
	//�X�e�[�W�i���o�[�̎擾
	int GetStage()
	{
		return m_stageNum;

	}
	
	//�X�e�[�Wnum
	enum STAGE
	{
		STAGE1,
		STAGE2,
	};

	//�C���X�^���X�̐���
	static void Map::Create()
	{
		if (!m_map)
		{
			m_map = new Map;
		}

	}

	//�C���X�^���X�̏���
	static  void Map::Destroy()
	{
		delete m_map;
		m_map = nullptr;
	}
	//�C���X�^���X�̎擾
	static Map& GetInstance()
	{
		return *m_map;
	}
private:
	//�R���X�g���N�^
	Map();
	static Map* m_map;//�C���X�^���X
	int m_stageNum= STAGE1;
	std::vector<HealItem*>	m_healList;		//�񕜃A�C�e��

};