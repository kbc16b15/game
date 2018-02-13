#pragma once

class ResultScene:public IGameObject
{
public:
	//�f�X�g���N�^
	~ResultScene();
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

	//�C���X�^���X�̐���
	static  void ResultScene::Create()
	{
		if (!m_result)
		{
			m_result = new ResultScene;

		}
	}
	//�C���X�^���X�̏���
	static  void ResultScene::Destroy()
	{
		delete m_result;
		m_result = nullptr;
	}
	//�C���X�^���X�̎擾
	static ResultScene& GetInstance()
	{
		return *m_result;
	}
private:
	
	//�R���X�g���N�^
	ResultScene();
	static ResultScene* m_result;//�C���X�^���X
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_resultHud;							//�^�C�g���摜
	const D3DXVECTOR2	m_resultHudPos = { 700.0f,300.0f };	//�^�C�g���摜�̍��W
};

