#pragma once
//#include "MapInfo.h"
class HealItem;

struct SMapChipLocInfo {
	const char* modelName;	//モデル。
	D3DXVECTOR3	pos;		//座標。
	D3DXQUATERNION	rot;	//回転。
};


//template <typename T>
class Map :public IGameObject
{
public:
	//ステージnum
	enum STAGE
	{
		STAGE1,
		STAGE2
	};


	//デストラクタ
	~Map();
	//初期化
	void Init();
	//描画
	void Draw();
	//更新
	void Update();

	void MapLoad1();
	void MapLoad2();
	void MapCreate(const char* mapName, int no, SMapChipLocInfo Info[]);


	//ステージ切り替え
	void SetStage(int StageNum)
	{
		m_stageNum = StageNum;

	}
	//ステージナンバーの取得
	int GetStage()
	{
		return m_stageNum;

	}

	//インスタンスの生成
	static void Map::Create()
	{
		if (!m_map)
		{
			m_map = new Map;
		}

	}

	//インスタンスの消去
	static  void Map::Destroy()
	{
		delete m_map;
		m_map = nullptr;
	}
	//インスタンスの取得
	static Map& GetInstance()
	{
		return *m_map;
	}
private:
	//コンストラクタ
	Map();
	static Map* m_map;//インスタンス
	int m_stageNum = STAGE1;
	std::vector<HealItem*>	m_healList;		//回復アイテム

};