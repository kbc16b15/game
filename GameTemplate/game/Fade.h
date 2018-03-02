#pragma once
class Fade:public IGameObject
{
public:

	~Fade();

	void Init();

	void Update();

	void PostDraw();

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
		m_fadeSprite.SetAlpha(1.0f);
		m_timer = 0.0f;
		m_isActive = true;
		m_isExecute = true;
		m_state = eFadeOut;
	}
	//!<�t�F�[�h�C���B
	void StartFadeIn()
	{
		if (m_fadeSprite.GetAlpha() > 0)
		{
			m_timer = 0.0f;
			m_isActive = true;
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
	EnState				m_state = eFadeOut;				//�t�F�[�h�̏��
	float				m_timer=1.0f;					//�^�C�}�[
	float				m_outtimer = 0.0f;
	bool				m_isExecute = false;			//�t�F�[�h�����s��
	Sprite				m_fadeSprite;					//!<�w�i�̃X�v���C�g�B
	Texture				m_fadeTex;						//!<�w�i�̃e�N�X�`���B
	const D3DXVECTOR2	m_fadepos = { 680.0f,300.0f };	//���W
	const D3DXVECTOR2	m_fadeScale = { 1300.0f,1200.0f };//�g��
	const float			FADE_TIME = 0.3f;				//�t�F�[�h����
	float				m_frameDeltaTime = 1.0f / 60.0f;//1�t���[���̎���
};
//extern Fade*   g_fade;

