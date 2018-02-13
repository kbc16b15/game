#pragma once
#include "HUD.h"
//#include "IGameObject.h"
class TitleScene :public IGameObject
{
public:
	//�f�X�g���N�^
	~TitleScene();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�t�F�[�h
	void SceneFade();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();

	
	//�C���X�^���X�̎擾
	static TitleScene& GetInstance()
	{
		return *m_title;
	}
	//�C���X�^���X�̐���
	static void TitleScene::Create()
	{
		if (!m_title)
		{
			m_title = new TitleScene;
		}
	
	}
	//�C���X�^���X�̏���
	static  void TitleScene::Destroy()
	{
		delete m_title;
		m_title = nullptr;
	}
private:
	
	//�R���X�g���N�^
	TitleScene();
	static TitleScene* m_title;//�C���X�^���X
	//�X�e�[�g
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//�I��
	//enum Select{
	//	NO,
	//	START,
	//	BREAK,
	//};
	//Select				GAME = START;					//���
	EState				m_state = Run;					//�t�F�[�h
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_titleHud;						//�^�C�g���摜
	const D3DXVECTOR2	m_titlePos = { 595.0f,400.0f };	//�^�C�g���摜�̍��W
	
};

