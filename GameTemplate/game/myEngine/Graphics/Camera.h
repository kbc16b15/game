#pragma once

/*!
 *@brief	�J�����N���X�B
 */

class Camera {
private:
	static Camera*			m_camera;
	D3DXMATRIX				m_viewMatrix;			//!<�r���[�s��B�J�����s��Ƃ������B
	D3DXMATRIX				m_projectionMatrix;		//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXMATRIX				m_viewMatrixInv;		//�J�����s��̋t�s��
	D3DXMATRIX				m_rotationMatrix;		//��]�s��
	D3DXVECTOR3				m_vEyePt;				//!<�J�����N���X����邽�߂̃q���g�B�J�����̎��_�B���̕ӂ�̓����o�ϐ��ɕύX����B
	D3DXVECTOR3				m_vLookatPt;			//!<�J�����N���X����邽�߂̃q���g�B�J�����̒����_�B�ǂ������Ă��邩�Ƃ������B���̕ӂ�̓����o�ϐ��ɕύX����B
	D3DXVECTOR3				m_vUpVec;				//!<�J�����N���X����邽�߂̃q���g�B�J�����̏�����B��{�I��Y�����ł��܂�Ȃ��B��{�I�ɂ́E�E�E�B���̕ӂ�̓����o�ϐ��ɕύX����B
	float					m_far;					//!<�����ʁB
	float					m_near;					//!<�ߕ��ʁB
	float					m_aspect;				//!<�A�X�y�N�g��
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	Camera();
	/*!
	 *@brief	�f�X�g���N�^
	 */
	~Camera();
	/*!
	 *@brief	�A�X�y�N�g���ݒ�B
	 */
	void SetAspect(float _aspect);
	/*!
	 *@brief	�A�X�y�N�g����擾�B
	 */
	float GetAspect();
	/*!
	 *@brief	�t�@�[��ݒ�B
	 */
	void SetFar(float _far);
	/*!
	 *@brief	�j�A���擾�B
	 */
	float GetNear();
	/*!
	 *@brief	�t�@�[���擾�B
	 */
	float GetFar();
	/*!
	 *@brief	�j�A��ݒ�B
	 */
	void SetNear(float _near);
	/*!
	 *@brief	���_��ݒ�B
	 */
	void SetEyePt(D3DXVECTOR3 pt);
	/*!
	 *@brief	���_���擾�B
	 */
	D3DXVECTOR3 GetEyePt();
	/*!
	 *@brief	�����_��ݒ�B
	 */
	void SetLookatPt(D3DXVECTOR3 pt);
	/*!
	 *@brief	�����_�̎擾�B
	 */
	D3DXVECTOR3 GetLookatPt();
	/*!
	 *@brief	������̐ݒ�B
	 */
	void SetUpVec(D3DXVECTOR3 up);
	/*!
	 *@brief	������̎擾�B
	 */
	D3DXVECTOR3 GetUpVec();
	/*!
	 *@brief	�r���[�s��̐ݒ�B
	 */
	void SetViewMatrix(D3DXMATRIX mView);
	/*!
	 *@brief	�r���[�s��̎擾�B
	 */
	D3DXMATRIX GetViewMatrix();
	/*!
	 *@brief	�v���W�F�N�V�����s��̐ݒ�B
	 */
	void SetProjectionMatrix(D3DXMATRIX mProj);
	/*!
	 *@brief	�v���W�F�N�V�����s��̎擾�B
	 */
	D3DXMATRIX GetProjectionMatrix();
	/*!
	 *@brief	�J�����̍X�V�����B
	 */
	void Update();
	/*!
	 *@brief	�J�����̏������B
	 */
	void Init();

	//�J�����̉�]�s����擾�B
	const D3DXMATRIX& GetCameraRotation() const
	{
		return m_rotationMatrix;
	}

	//�r���[�s��̋t�s����擾�B
	
	const D3DXMATRIX& GetViewMatrixInv() const
	{
		return m_viewMatrixInv;
	}

	//�C���X�^���X�̐���
	static void Camera::Create()
	{
		if (!m_camera)
		{
			m_camera = new Camera;
		}
	}

	//�C���X�^���X�̏���
	static  void Camera::Destroy()
	{
		delete m_camera;
		m_camera = nullptr;
	}
	//�C���X�^���X�̎擾
	static Camera& GetInstance()
	{
		return *m_camera;
	}

};