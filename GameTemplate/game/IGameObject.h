#pragma once
//class Player;

class IGameObject
{
public:
	IGameObject();
	virtual ~IGameObject();
	virtual void Init() {};
	virtual void Update() = 0;
	virtual void Draw() {};
	virtual void HudDraw() {};
	virtual void PrePostDraw() {};
	virtual void PostDraw() {};
	//template<typename T>
	//virtual T& GetInstance() {};
	//IGameObject* ObjectFactory(const char* ObjctName);
	bool GetActive()
	{
		return m_isActive;
	}
	void SetActive(bool active)
	{
		m_isActive = active;
	}
	
	const char* GetName()
	{
		return m_modelName;
	}

	void SetName(char* Name)
	{
		m_modelName = Name;
	}
protected:
	bool	m_isActive = true;
	char*	m_modelName=nullptr;
};