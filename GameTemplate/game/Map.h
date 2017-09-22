#pragma once
//#include "IGameObject.h"
class MapChip;
class MoveObject;
class TrapObject;
class RotObject;
class FallObject;
class Map/*:public IGameObject*/
{
public:
	//コンストラクタ
	Map();
	//デストラクタ
	~Map();
	//初期化
	void Init();
	//描画
	void Draw();
	//更新
	void Update();
	
	//ムーブオブジェクトのリストの取得
	//戻り値　std::vector<MoveObject*>
	//std::vector<MoveObject*>& GetMobject()
	//{
	//	return moveList;
	//}
private:
	std::vector<MapChip*>	mapChipList;	//マップチップのリスト。
	std::vector<MoveObject*> moveList;		//ムーブオブジェクトのリスト
	std::vector<TrapObject*> trapList;		//ダメージオブジェクトのリスト
	std::vector<RotObject*> rotList;		//回転オブジェクトのリスト
	std::vector<FallObject*> fallList;		//落下オブジェクトのリスト

	D3DXVECTOR3 RDir = { 0.0f,1.0f,0.0f };	//回転の向き
	D3DXVECTOR3 RSpeed= { 0.0f,1.0f,0.0f };	//回転速度


};
