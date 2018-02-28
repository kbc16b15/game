#pragma once
class Player;
class IGameObject
{
public:
	IGameObject();
	virtual ~IGameObject();
	virtual void Init() {};
	virtual void Update() =0;
	virtual void Draw() {};
	virtual void HudDraw() {};
	virtual void PrePostDraw() {};
	virtual void PostDraw() {};
	IGameObject* ObjectFactory(const char* ObjctName);
	bool GetActive()
	{
		return m_isActive;
	}
	void SetActive(bool active)
	{
		m_isActive = active;
	}
	Player& GetPlayer()
	{
		return *m_player;
	}
protected:
	Player* m_player=nullptr;
	bool m_isActive = true;
};

