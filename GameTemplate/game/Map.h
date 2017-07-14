#pragma once
//#include "IGameObject.h"
class MapChip;

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
};
