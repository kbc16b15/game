#pragma once
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
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
	//�V�[���`�F���W
	void SceneChange();

	void SetScene(int SceneNo)
	{
		m_Scene = SceneNo;
	}
	enum SCENE
	{
		TITLE,			//�^�C�g���V�[��
		GAME,			//�Q�[���V�[��
		GAME2,
		END,
		CHANGEGAME,		//�Q�[���V�[���ɑJ��
		CHANGEGAME2,
		CHANGETITLE,	//�^�C�g���V�[���ɑJ��
		CHANGEEND,
	};
private:
	TitleScene* title=nullptr;	//�^�C�g��
	ResultScene* end = nullptr;
	int m_Scene = TITLE;	//�V�[���̏��
};

extern Scene* scene;

