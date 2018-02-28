#pragma once
#include "HUD.h"
#include "Sound.h"
#include "IScene.h"
//#include "IGameObject.h"
class TitleScene :public IScene
{
public:
	//�R���X�g���N�^
	TitleScene();
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
	//���񂾂��t�F�[�h�C�����Ȃ���
	void SetStart(bool start)
	{
		m_isStart = start;
	}

private:

	//�X�e�[�g
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;			//�t�F�[�h
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD*				m_titleHud;						//�^�C�g���摜
	const D3DXVECTOR2	m_titlePos = { 595.0f,400.0f };	//�^�C�g���摜�̍��W
	bool				m_isStart = false;
	Sound*				m_buttonSound = nullptr;			//�T�E���h
};

