#pragma once
//#include "IGameObject.h"
class MapChip;
class MoveObject;

class Map/*:public IGameObject*/
{
public:
	Map();
	~Map();
	void Init();
	void Draw();
	void Update();
private:
	std::vector<MapChip*>	mapChipList;	//マップチップのリスト。
	std::vector<MoveObject*> moveList;

};
