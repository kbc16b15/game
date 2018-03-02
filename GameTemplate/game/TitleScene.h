#pragma once
#include "Sound.h"
#include "IScene.h"
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
	Sprite				m_titleSprite;					//�^�C�g����ʂ̔w�i�̃X�v���C�g�B
	Texture				m_titleTexture;					//�^�C�g����ʂ̔w�i�̃e�N�X�`���B
	const D3DXVECTOR2	m_titlePos = { 0.0f,0.0f };		//�^�C�g���摜�̍��W
	const D3DXVECTOR2	m_titleScale = { 1300.0f,1200.0f };//�^�C�g���摜�̊g��
	bool				m_isStart = false;
	Sound*				m_buttonSound = nullptr;		//�T�E���h
};

