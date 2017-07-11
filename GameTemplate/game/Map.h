#pragma once
class MapChip;

class Map
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
