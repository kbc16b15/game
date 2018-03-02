#pragma once
#include "IGameObject.h"
class Silhouette :
	public IGameObject
{
public:
	Silhouette();
	~Silhouette();

	void Draw();
	
	void Update() {};

};

