#pragma once
//#include "IGameObject.h"

class MapChip;
class MoveObject;
class TrapObject;
class RotObject;
class FallObject;
class GoalObject;
class HealItem;
class Sky;
class MoveCube;
class MapObject;

class Map/*:public IGameObject*/
{
public:
	
	//コンストラクタ
	Map();
	//デストラクタ
	~Map();
	//初期化
	void Init(/*struct SMapChipLocInfo Info[]*/);
	//描画
	void Draw();
	//更新
	void Update();

	//void Test(T aa);
	//ステージ切り替え
	void SetStage(int StageNum)
	{
		m_StageNum = StageNum;

	}

	//ステージnum
	enum STAGE
	{
		STAGE1,
		STAGE2,
	};
private:
	int m_Stage = STAGE1;
	int m_StageNum=0;
	//std::vector<std::vector<MapChip*>> aa;
	std::vector<MapChip*>	mapChipList;	//マップチップのリスト。
	std::vector<Sky*>		skyList;		//空と海
	std::vector<MoveObject*> moveList;		//ムーブオブジェクトのリスト
	std::vector<TrapObject*> trapList;		//ダメージオブジェクトのリスト
	std::vector<RotObject*> rotList;		//回転オブジェクトのリスト
	std::vector<FallObject*> fallList;		//落下オブジェクトのリスト
	std::vector<GoalObject*> GoalList;		//ゴール地点
	std::vector<MoveCube*> mCubeList;		//移動床
	std::vector<HealItem*> HealList;		//回復アイテム
	std::vector<MapObject*> mapList;		//基底クラスのリスト

	D3DXVECTOR3 RDir = { 0.0f,1.0f,0.0f };	//回転の向き
	D3DXVECTOR3 RSpeed= { 0.0f,1.0f,0.0f };	//回転速度

};