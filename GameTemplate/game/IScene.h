#pragma once
class IScene
{
public:
	IScene();

	virtual ~IScene();
	virtual void Init() = 0; // シーン
	virtual void Draw() = 0; // シーンの描画
	virtual void Update() = 0; // シーン
};

