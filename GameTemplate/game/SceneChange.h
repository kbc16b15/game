#pragma once
#include "IGameObject.h"
class SceneChange :
	public IGameObject
{
public:

	//�f�X�g���N�^
	~SceneChange();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	//void Draw();

	int GetMapNo()
	{
		return m_stageNo;
	}

	void SetMapNo(int No)
	{
		m_stageNo = No;
	}

	void SetChange(bool Change)
	{
		m_isChange = Change;
	}

	bool GetChange()
	{
		return m_isChange;
	}
	//�C���X�^���X�̎擾
	static SceneChange& GetInstance()
	{
		return *m_change;
	}
	//�C���X�^���X�̐���
	static void SceneChange::Create()
	{
		if (!m_change)
		{
			m_change = new SceneChange;
		}

	}
	//�C���X�^���X�̏���
	static  void SceneChange::Destroy()
	{
		delete m_change;
		m_change = nullptr;
	}
private:

	//�R���X�g���N�^
	SceneChange();
	static SceneChange* m_change;//�C���X�^���X
	int m_stageNo = 0;
	bool m_isChange=false;
};

