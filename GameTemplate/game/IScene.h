#pragma once
class IScene
{
public:
	IScene();

	virtual ~IScene();
	virtual void Init() = 0; // �V�[��
	virtual void Draw() = 0; // �V�[���̕`��
	virtual void Update() = 0; // �V�[��
};

