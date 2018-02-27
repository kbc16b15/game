#include "stdafx.h"
#include "Camera.h"

Camera *Camera::m_camera = NULL;

//�R���X�g���N�^�B
Camera::Camera()
{
	m_near = 0.1f;
	m_far = 1000.0f;
	m_aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
}
//�f�X�g���N�^
Camera::~Camera()
{
}
//�A�X�y�N�g���ݒ�B
void Camera::SetAspect(float _aspect)
{
	m_aspect = _aspect;
}
//�A�X�y�N�g����擾�B
float Camera::GetAspect()
{
	return m_aspect;
}
//�t�@�[��ݒ�B
void Camera::SetFar(float _far)
{
	m_far = _far;
}
//�j�A�[�̎擾�B
float Camera::GetNear()
{
	return m_near;
}
//�t�@�[�̎擾�B
float Camera::GetFar()
{
	return m_far;
}
//�j�A�[��ݒ�B
void Camera::SetNear(float _near)
{
	m_near = _near;
}
//���_�̃Z�b�^�[
void Camera::SetEyePt(D3DXVECTOR3 pt)
{
	m_vEyePt = pt;
}
//���_�̃Q�b�^�[
D3DXVECTOR3 Camera::GetEyePt()
{
	return m_vEyePt;
}
//�����_�̃Z�b�^�[
void Camera::SetLookatPt(D3DXVECTOR3 pt)
{
	m_vLookatPt = pt;
}
//�����_�̃Q�b�^�[�B
D3DXVECTOR3 Camera::GetLookatPt()
{
	return m_vLookatPt;
}
//������̃Z�b�^�[
void Camera::SetUpVec(D3DXVECTOR3 up)
{
	m_vUpVec = up;
}
//������̃Q�b�^�[
D3DXVECTOR3 Camera::GetUpVec()
{
	return m_vUpVec;
}
//�r���[�s��̃Z�b�^�[�B
void Camera::SetViewMatrix(D3DXMATRIX mView)
{
	m_viewMatrix = mView;
}
//�r���[�s��̃Q�b�^�[
D3DXMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}
//�v���W�F�N�V�����s��̃Z�b�^�[
void Camera::SetProjectionMatrix(D3DXMATRIX mProj)
{
	m_projectionMatrix = mProj;
}
//�v���W�F�N�V�����s��̃Q�b�^�[
D3DXMATRIX Camera::GetProjectionMatrix()
{
	return m_projectionMatrix;
}
//�J�����̍X�V�����B
void Camera::Update()
{
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_vEyePt, &m_vLookatPt, &m_vUpVec);
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, m_aspect, m_near, m_far);
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);

	//�J�����̉�]�s����擾�B
	m_rotationMatrix = m_viewMatrixInv;
	m_rotationMatrix.m[3][0] = 0.0f;
	m_rotationMatrix.m[3][1] = 0.0f;
	m_rotationMatrix.m[3][2] = 0.0f;
	m_rotationMatrix.m[3][3] = 1.0f;
}
//�J�����̏������B
void Camera::Init()
{
	m_vEyePt = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	m_vLookatPt = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	m_vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Update();
}