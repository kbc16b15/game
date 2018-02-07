#pragma once
#include "myEngine/Graphics/Camera.h"
class SpringCamera
{
public:

	~SpringCamera();

	//�����_
	//���W
	//�ړ��ō����x
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);
	/*!
	* @brief	�ڕW�ƂȂ钍���_��ݒ�B
	*/
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}
	/*!
	* @brief	�ڕW�ƂȂ鎋�_��ݒ�B
	*/
	void SetTarPosition(const D3DXVECTOR3 position)
	{
		m_position = position;
	}
	/*!
	* @brief	�����_��ݒ�B
	*/
	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetLookatPt(target);
	}
	/*!
	* @brief	���_��ݒ�B
	*/
	void SetPosition(const D3DXVECTOR3 position)
	{
		m_camera.SetEyePt(position);
	}
	/*!
	* @brief	�����ʂ�ݒ�B
	*/
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}
	/*!
	* @brief	�����_���擾�B
	*/
	const D3DXVECTOR3& GetTarget()
	{
		return m_camera.GetLookatPt();

	}
	/*!
	* @brief	���_���擾�B
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_camera.GetEyePt();
	}
	//�v���W�F�N�V�����s��̃Q�b�^�[
	D3DXMATRIX GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}
	//�r���[�s��̃Q�b�^�[
	D3DXMATRIX GetViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	* @brief	�J�������擾�B
	*/
	const Camera* GetCamera()
	{
		return &m_camera;
	}
	/*!
	* @brief	�o�l�̌�������ݒ�B
	*@detail
	* �l���傫���قǃJ�������x��ĕt���Ă��܂��B
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}
	/*!
	* @brief	�J�������擾�B
	*/
	/*Camera* GetCamera()
	{
		return &m_camera;
	}*/
	/*void SetViewAngle(float angle)
	{
		m_camera.SetViewAngle(angle);
	}
	float GetViewAngle() const
	{
		return m_camera.GetViewAngle();
	}*/

	/*!
	* @brief	�ڕW�ƂȂ钍���_���擾�B
	*/
	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}
	/*!
	* @brief	�ڕW�ƂȂ鎋�_���擾�B
	*/
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	�o�l�J�����p�̃p�����[�^���N���A�B
	*/
	void ClearSpringParame()
	{
		m_targetMoveSpeed = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

	void UpdateSpringCamera();

	//�C���X�^���X�̐���
	static void SpringCamera::Create()
	{
		if (!m_springCamera)
		{
			m_springCamera = new SpringCamera;
		}

	}

	//�C���X�^���X�̏���
	static  void SpringCamera::Destroy()
	{
		delete m_springCamera;
		m_springCamera = nullptr;
	}
	//�C���X�^���X�̎擾
	static SpringCamera& GetInstance()
	{
		return *m_springCamera;
	}
private:
	SpringCamera();
	static SpringCamera* m_springCamera;
	Camera		m_camera;											//�J����
	D3DXVECTOR3	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ڕW�ƂȂ钍���_
	D3DXVECTOR3	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ڕW�ƂȂ鎋�_
	D3DXVECTOR3	m_targetMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����_�̈ړ����x
	D3DXVECTOR3	m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���_�̈ړ����x
	float		m_maxMoveSpeed = 0.0f;								//�ō��ړ����x
	float		m_targetDampingRate = 1.0f;							//�������B�l���傫���قǃJ�������x��t���Ă���
	float		m_dampingRate = 0.5f;								//������
	
	float		m_dampingRateVel = 0.0f;
};

