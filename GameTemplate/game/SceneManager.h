#pragma once
#include "IScene.h"
#include "IGameObject.h"
class Game;
class SceneManager:public IGameObject
{

private:
	static SceneManager* m_sMgr;
	static IScene* m_pScene/*=nullptr*/; // �V�[���I�u�W�F�N�g
	static Game* m_game/*=nullptr*/;
	static void ChangeState(IScene* scene); // �V�[���̑J��
	SceneManager();
	~SceneManager();
public:
	// �V�[���񋓌^
	enum SCENE
	{
		TITLE,       // �^�C�g�����
		GAME,   // �Q�[�����C�����
		GAME2,   // �Q�[�����C�����2
		GAME3,   // �Q�[�����C�����2
		RESULT,      // ���ʉ��
		CLEAR,		//�N���A�V�[��
	};
	static void ChangeScene(SCENE scene); // �V�[���̑J��
	
	void PrePostDraw(); // �V�[���̕`��
	void Update();


	//�C���X�^���X�̐���
	static void SceneManager::Create()
	{
		if (!m_sMgr)
		{
			m_sMgr = new SceneManager;
		}

	}

	//�C���X�^���X�̏���
	static void SceneManager::Destroy()
	{
		delete m_sMgr;
		m_sMgr = nullptr;
	}
	//�C���X�^���X�̎擾
	static SceneManager& GetInstance()
	{
		return *m_sMgr;
	}
	//�Q�[���V�[���̎擾
	static Game& GetGame()
	{
		return *m_game;
	}
	//���݂̃V�[���̎擾
	static int GetScene()
	{
		return m_scene;
	}
private:
	static int m_scene;
};

