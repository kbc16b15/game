#pragma once
//#include "IGameObject.h"
#include "HUD.h"
class ClearScene :public IGameObject
{
public:
	//�f�X�g���N�^
	~ClearScene();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void PrePostDraw();
	//�t�F�[�h
	void SceneFade();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();

	//�C���X�^���X�̐���
	static  void ClearScene::Create()
	{
		if (!m_clear)
		{
			m_clear = new ClearScene;

		}
	}
	//�C���X�^���X�̏���
	static  void ClearScene::Destroy()
	{
		delete m_clear;
		m_clear = nullptr;
	}
	//�C���X�^���X�̎擾
	static ClearScene& GetInstance()
	{
		return *m_clear;
	}
private:

	//�R���X�g���N�^
	ClearScene();
	static ClearScene* m_clear;//�C���X�^���X
								 //�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = Run;
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_clearHud;							//�^�C�g���摜
	const D3DXVECTOR2	m_clearHudPos = { 595.0f,400.0f };	//�^�C�g���摜�̍��W
};

