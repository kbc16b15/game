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

	void SetRockCamera(bool Rcamera)
	{
		Rockonflg = Rcamera;
	}

	D3DXVECTOR3 Getvec()
	{
		return vec;
	}
private:
	Pad			pad;					//�p�b�h
	Camera		m_camera;				//�J����
	D3DXVECTOR3 position;				//���W
	float		angleX = 0.0f;			//�J�����㉺�l
	D3DXVECTOR3	toCameraPos;			//�J�������W
	float angle = 0.0f;					//�p�x
	const float RotSpeedY = 2.0f;		//Y����]���x
	const float RotSpeedX = 1.0f;		//X����]���x
	const float CameraUpLimit = 20.0f;	//�J�����㉺���x
	bool		Rockonflg = false;
	//bool	CameraTypeflg = false;

	D3DXVECTOR3 vec = { 0.0f,0.0f,0.0f };
};

