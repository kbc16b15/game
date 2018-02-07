#pragma once
class IGameObject
{
public:
	IGameObject();
	virtual ~IGameObject();
	virtual void Init() {};
	virtual void Update()=0;
	virtual void Draw() {};
	void SetDeathflg()
	{
		IsDeath=true;
	}

	bool GetDeathflg()
	{
		return IsDeath;
	}
private:
	bool IsDeath=false;
};

