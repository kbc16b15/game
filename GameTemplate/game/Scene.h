#pragma once
#include "TitleScene.h"
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

	enum SCENE
	{
		TITLE,			//�^�C�g���V�[��
		GAME,			//�Q�[���V�[��
		CHANGEGAME,		//�Q�[���V�[���ɑJ��
		CHANGETITLE		//�^�C�g���V�[���ɑJ��
	};
private:
	TitleScene* title=nullptr;	//�^�C�g��
	int m_Scene = TITLE;	//�V�[���̏��
};

extern Scene* scene;

