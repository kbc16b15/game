#pragma once
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
//#include "BaseScene.h"
class Scene
{
public:
	//�R���X�g���N�^
	Scene();
	//�f�X�g���N�^
	~Scene();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Render();

	enum SCENE
	{
		TITLE,			//�^�C�g���V�[��
		GAME,			//�Q�[���V�[��
		END,
		CHANGEGAME,
		CHANGETITLE,
		CHANGEEND
	};

	//�V�[���`�F���W
	void SceneChange(SCENE SceneNo);

private:
	TitleScene* title=nullptr;
	ResultScene* end = nullptr;
	//BaseScene* m_bScene=nullptr;
	SCENE m_Scene;
};

extern Scene* scene;

