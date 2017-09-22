#pragma once
#include "myEngine\HID\Pad.h"
class gameCamera
{
public:
	//�R���X�g���N�^
	gameCamera();
	//�f�X�g���N�^
	~gameCamera();
	//������
	void Init();
	//�X�V
	void Update();
	//�J�����̎擾
	Camera Getcamera()
	{
		return m_camera;
	}
private:
	Pad			pad;			//�p�b�h
	Camera		m_camera;		//�J����
	D3DXVECTOR3 position;		//���W
	float		angleX = 0.0f;	//�J�����㉺���
	D3DXVECTOR3	toCameraPos;	//�J�������W
	float angle = 0.0f;			//�p�x
	//bool	CameraTypeflg = false;
};

