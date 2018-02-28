#pragma once
#include "IGameObject.h"
#include "HUD.h"
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
	void PrePostDraw();

	void SceneFade();

	void Change();
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

	//�X�v���C�g�����֐�
	HRESULT CreateSprite();
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

	//enum EState {
	//	WaitFadeIn,
	//	Run,
	//	WaitFadeOut
	//};
	//EState				m_state = WaitFadeIn;				//�t�F�[�h
	LPD3DXSPRITE		m_sprite;							//�X�v���C�g
	HUD					m_changeHud;						//�^�C�g���摜
	const D3DXVECTOR2	m_changePos = { 595.0f,400.0f };	//�^�C�g���摜�̍��W
};

