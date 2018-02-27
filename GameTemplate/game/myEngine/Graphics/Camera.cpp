#include "stdafx.h"
#include "Camera.h"

Camera *Camera::m_camera = NULL;

//コンストラクタ。
Camera::Camera()
{
	m_near = 0.1f;
	m_far = 1000.0f;
	m_aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
}
//デストラクタ
Camera::~Camera()
{
}
//アスペクト比を設定。
void Camera::SetAspect(float _aspect)
{
	m_aspect = _aspect;
}
//アスペクト比を取得。
float Camera::GetAspect()
{
	return m_aspect;
}
//ファーを設定。
void Camera::SetFar(float _far)
{
	m_far = _far;
}
//ニアーの取得。
float Camera::GetNear()
{
	return m_near;
}
//ファーの取得。
float Camera::GetFar()
{
	return m_far;
}
//ニアーを設定。
void Camera::SetNear(float _near)
{
	m_near = _near;
}
//視点のセッター
void Camera::SetEyePt(D3DXVECTOR3 pt)
{
	m_vEyePt = pt;
}
//視点のゲッター
D3DXVECTOR3 Camera::GetEyePt()
{
	return m_vEyePt;
}
//注視点のセッター
void Camera::SetLookatPt(D3DXVECTOR3 pt)
{
	m_vLookatPt = pt;
}
//注視点のゲッター。
D3DXVECTOR3 Camera::GetLookatPt()
{
	return m_vLookatPt;
}
//上方向のセッター
void Camera::SetUpVec(D3DXVECTOR3 up)
{
	m_vUpVec = up;
}
//上方向のゲッター
D3DXVECTOR3 Camera::GetUpVec()
{
	return m_vUpVec;
}
//ビュー行列のセッター。
void Camera::SetViewMatrix(D3DXMATRIX mView)
{
	m_viewMatrix = mView;
}
//ビュー行列のゲッター
D3DXMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}
//プロジェクション行列のセッター
void Camera::SetProjectionMatrix(D3DXMATRIX mProj)
{
	m_projectionMatrix = mProj;
}
//プロジェクション行列のゲッター
D3DXMATRIX Camera::GetProjectionMatrix()
{
	return m_projectionMatrix;
}
//カメラの更新処理。
void Camera::Update()
{
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_vEyePt, &m_vLookatPt, &m_vUpVec);
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, m_aspect, m_near, m_far);
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);

	//カメラの回転行列を取得。
	m_rotationMatrix = m_viewMatrixInv;
	m_rotationMatrix.m[3][0] = 0.0f;
	m_rotationMatrix.m[3][1] = 0.0f;
	m_rotationMatrix.m[3][2] = 0.0f;
	m_rotationMatrix.m[3][3] = 1.0f;
}
//カメラの初期化。
void Camera::Init()
{
	m_vEyePt = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	m_vLookatPt = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	m_vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Update();
}