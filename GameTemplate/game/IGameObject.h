#pragma once
class IGameObject
{
public:
	IGameObject();
	virtual ~IGameObject();
	virtual void Init() {};
	virtual void Update()=0;
	virtual void Draw() {};
	virtual void PrePostDraw(){};
	virtual void PostDraw() {};
};

