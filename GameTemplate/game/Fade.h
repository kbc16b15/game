#pragma once
class Fade
{
public:
	Fade();
	~Fade();

	void Start();

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
	const D3DXVECTOR2	m_fadepos = { 700.0f,300.0f };	//���W
	const float			FADE_TIME = 0.1f;				//�t�F�[�h����
	float				m_frameDeltaTime = 1.0f / 60.0f;//1�t���[���̎���
};

extern Fade*   g_fade;

