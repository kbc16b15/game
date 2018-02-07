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
	//�V�[��
	enum SCENE
	{
		TITLE,			//�^�C�g���V�[��
		GAME,			//�Q�[���V�[��
		GAME2,
		END,
		CHANGEGAME,
		CHANGEGAME2,
		CHANGETITLE,
		CHANGEEND
	};

	//�V�[���`�F���W
	void SceneChange(SCENE SceneNo);

	//�p�b�h�̎擾
	Pad GetPad()
	{
		return m_pad;
	}
private:
	TitleScene*		m_title=nullptr;	//�^�C�g��
	ResultScene*	m_end = nullptr;	//���U���g
	SCENE			m_scene;			//�V�[���̏��
	Pad			m_pad;		//�p�b�h
	//BaseScene*	m_bScene=nullptr;
};

extern Scene* g_scene;

