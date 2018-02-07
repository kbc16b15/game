#pragma once

class gameCamera:public IGameObject
{
public:

	//�f�X�g���N�^
	~gameCamera();
	//������
	void Init();
	//�X�V
	void Update();
	//�J�����̉�]
	void RotCamera();

	//�Ǐ]�J����
	void TrackingCamera();

	//�Ə��J����
	void RockCamera();
	//�{�X��X�^�[�g�J�����@�J�������o�������H
	void BossStartCamera();
	//�{�X��J����
	void BossCamera();
	//�{�X��G���h�J����
	void BossEndCamera();
	//�{�X�Œ�J����
	void BossRockCamera();
	//�Ə��t���O
	void SetRockCamera(bool isRock)
	{
		m_isRockOn = isRock;
	}

	//�C���X�^���X�̐���
	static void gameCamera::Create()
	{
		if (!m_gameCamera)
		{
			m_gameCamera = new gameCamera;
		}

	}

	//�C���X�^���X�̏���
	static  void gameCamera::Destroy()
	{
		delete m_gameCamera;
		m_gameCamera = nullptr;
	}
	//�C���X�^���X�̎擾
	static gameCamera& GetInstance()
	{
		return *m_gameCamera;
	}
private:
	//�R���X�g���N�^
	gameCamera();
	static gameCamera* m_gameCamera;			//�C���X�^���X
	D3DXVECTOR3		m_position;					//�J�������W
	const float		m_rotSpeed = 2.0f;			//��]���x
	bool			m_isBossStartCamera = false;//�{�X��J����
	int				m_stateCameraTime = 250;	//�J�n�J�����̎���
	bool			m_isBossEndCamera = false;	//�{�X��J����
	int				m_endCameraTime = 300;		//�I���J�����̎���
	bool			m_isBossCamera = false;
	bool			m_isRockOn = false;
	//const float CameraUpLimit = 30.0f;		//�J�����㉺���x
	//bool			m_istoCamera = false;			//�J�����𑀍쒆���ǂ���
	D3DXVECTOR3 vec = { 0.0f, 0.0f, 0.0f };


};