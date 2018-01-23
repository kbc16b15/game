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
class Sea;

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

	std::vector<FallObject*> GetFall()
	{
		return m_fallList;
	}

	//ステージnum
	enum STAGE
	{
		STAGE1,
		STAGE2,
	};
private:
	//int m_Stage = STAGE1;
	int m_stageNum= STAGE1;
	//std::vector<MapChip*>	mapChipList;	//マップチップのリスト
	//std::vector<Sky*>		skyList;		//空と海
	//std::vector<MoveObject*> moveList;	//ムーブオブジェクトのリスト
	//std::vector<TrapObject*> trapList;	//ダメージオブジェクトのリスト
	//std::vector<RotObject*> rotList;		//回転オブジェクトのリスト
	std::vector<FallObject*> m_fallList;	//落下オブジェクトのリスト
	//std::vector<GoalObject*> GoalList;	//ゴール地点
	//std::vector<MoveCube*> mCubeList;		//移動床
	std::vector<HealItem*>	m_healList;		//回復アイテム
	std::vector<MapObject*> m_mapList;		//基底クラスのリスト

	D3DXVECTOR3 m_rDir = { 0.0f,1.0f,0.0f };//回転の向き
	D3DXVECTOR3 m_rSpeed= { 0.0f,1.0f,0.0f };//回転速度

};