#pragma once
class IGameObject
{
public:
	IGameObject();
	virtual ~IGameObject();
	virtual void Init() {};
	virtual void Update()=0;
	virtual void Draw() {};
	virtual void HudDraw() {};
	virtual void PrePostDraw(){};
	virtual void PostDraw() {};

	bool GetActive()
	{
		return m_isActive;
	}
	void SetActive(bool active)
	{
		m_isActive = active;
	}
protected:
	bool m_isActive = true;
};

