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
	
	std::vector<MoveObject*>& GetMobject()
	{
		return moveList;
	}
private:
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
	std::vector<MoveObject*> moveList;

};
