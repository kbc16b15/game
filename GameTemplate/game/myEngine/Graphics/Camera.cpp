#include "stdafx.h"
#include "Camera.h"

//�R���X�g���N�^�B
Camera::Camera()
{
	Near = 0.1f;
	Far = 100.0f;
	aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
}
//�f�X�g���N�^
Camera::~Camera()
{
}
//�A�X�y�N�g���ݒ�B
void Camera::SetAspect(float _aspect)
{
	aspect = _aspect;
}
//�A�X�y�N�g����擾�B
float Camera::GetAspect()
{
	return aspect;
}
//�t�@�[��ݒ�B
void Camera::SetFar(float _far)
{
	Far = _far;
}
//�j�A�[�̎擾�B
float Camera::GetNear()
{
	return Near;
}
//�t�@�[�̎擾�B
float Camera::GetFar()
{
	return Far;
}
//�j�A�[��ݒ�B
void Camera::SetNear(float _near)
{
	Near = _near;
}
//���_�̃Z�b�^�[
void Camera::SetEyePt(D3DXVECTOR3 pt)
{
	vEyePt = pt;
}
//���_�̃Q�b�^�[
D3DXVECTOR3 Camera::GetEyePt()
{
	return vEyePt;
}
//�����_�̃Z�b�^�[
void Camera::SetLookatPt(D3DXVECTOR3 pt)
{
	vLookatPt = pt;
}
//�����_�̃Q�b�^�[�B
D3DXVECTOR3 Camera::GetLookatPt()
{
	return vLookatPt;
}
//������̃Z�b�^�[
void Camera::SetUpVec(D3DXVECTOR3 up)
{
	vUpVec = up;
}
//������̃Q�b�^�[
D3DXVECTOR3 Camera::GetUpVec()
{
	return vUpVec;
}
//�r���[�s��̃Z�b�^�[�B
void Camera::SetViewMatrix(D3DXMATRIX mView)
{
	viewMatrix = mView;
}
//�r���[�s��̃Q�b�^�[
D3DXMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}
//�v���W�F�N�V�����s��̃Z�b�^�[
void Camera::SetProjectionMatrix(D3DXMATRIX mProj)
{
	projectionMatrix = mProj;
}
//�v���W�F�N�V�����s��̃Q�b�^�[
D3DXMATRIX Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}
//�J�����̍X�V�����B
void Camera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//�J�����̏������B
void Camera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	vLookatPt = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Update();
}