#pragma once
#include "HUD.h"
class Fade:public IGameObject
{
public:

	~Fade();

	void Init();

	void Update();

	void Draw();

	//�X�v���C�g�����֐�
	HRESULT CreateSprite();

	//�t�F�[�h���s���t���O�̎擾
	bool isExecute()
	{
		return m_isExecute;
	}
	//!<�t�F�[�h�A�E�g�B
	void StartFadeOut()
	{
		m_timer = 0.0f;
		m_active = true;
		m_isExecute = true;
		m_state = eFadeOut;
	}
	//!<�t�F�[�h�C���B
	void StartFadeIn()
	{
		if (m_fadetex.Getalfa() > 0)
		{
			m_timer = 0.0f;
			m_active = true;
			m_isExecute = true;
			m_state = eFadeIn;
		}
	}

	//�C���X�^���X�̐���
	static void Fade::Create()
	{
		if (!m_fade)
		{
			m_fade = new Fade;
		}

	}

	//�C���X�^���X�̏���
	static  void Fade::Destroy()
	{
		Fade::GetInstance().SetDeathflg();//�o�^����
		delete m_fade;
		m_fade = nullptr;
	}
	//�C���X�^���X�̎擾
	static Fade& GetInstance()
	{
		return *m_fade;
	}
private:
	//�R���X�g���N�^
	Fade();
	static Fade* m_fade;//�C���X�^���X
private:
	
	enum EnState {
		eFadeOut,	//!<�t�F�[�h�A�E�g�B
		eFadeIn		//!<�t�F�[�h�C���B
	};
	HUD					m_fadetex;						//�u���b�N�A�E�g�p�̃X�v���C�g�B
	EnState				m_state = eFadeIn;				//�t�F�[�h�̏��
	float				m_timer=1.0f;					//�^�C�}�[
	float				m_outtimer = 0.0f;
	bool				m_isExecute = false;			//�t�F�[�h�����s��
	bool				m_active = false;					//�A�N�e�B�u�t���O
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	const D3DXVECTOR2	m_fadepos = { 680.0f,300.0f };	//���W
	const float			FADE_TIME = 0.5f;				//�t�F�[�h����
	float				m_frameDeltaTime = 1.0f / 60.0f;//1�t���[���̎���
};
//extern Fade*   g_fade;

