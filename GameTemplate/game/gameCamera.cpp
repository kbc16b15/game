#include "stdafx.h"
#include "gameCamera.h"
#include "SpringCamera.h"
#include "BossEnemy.h"
#include "Player.h"
#include "BulletManager.h"
#include "BulletHud.h"

gameCamera *gameCamera::m_gameCamera = NULL;

gameCamera::gameCamera()
{
}

gameCamera::~gameCamera()
{
}

void gameCamera::Init()
{
	Camera::Create();
	SpringCamera::Create();
	D3DXVECTOR3 targetPos = Player::GetInstance().Getpos();
	targetPos.y += 1.0f;
	D3DXVECTOR3 cameraPos= Player::GetInstance().Getpos();
	cameraPos.y += 5.0f;
	cameraPos.x += 5.0f;
	float cameraSpeed = 10.0f;
	SpringCamera::GetInstance().Init(targetPos, cameraPos, cameraSpeed);
	
	//SpringCamera::GetInstance().SetTarget(Player::GetInstance().Getpos());

	//SpringCamera::GetInstance().SetFar(Far);//奥行きの見える範囲
	//カメラの注視点を設定する。
	SpringCamera::GetInstance().SetTarTarget(targetPos);
	SpringCamera::GetInstance().SetTarPosition(cameraPos);
	TrackingCamera();
	SpringCamera::GetInstance().Update();
	
}

void gameCamera::Update()
{
	//if (&SpringCamera::GetInstance() == NULL || &gameCamera::GetInstance() == NULL) { return; };
	if (m_isBossStartCamera)
	{
		BossStartCamera();
	}
	else if (m_isBossEndCamera)
	{
		BossEndCamera();
	}
	else if (m_isBossCamera)
	{
		RotCamera();
		//BossCamera();
	}
	//else if (m_isRockOn)
	//{
	//	//TrackingCamera();
	//	RockCamera();
	//}
	else
	{
		RotCamera();
		TrackingCamera();
	}
	SpringCamera::GetInstance().Update();
}

void gameCamera::RotCamera()
{
	
	D3DXMATRIX XRot;
	D3DXMATRIX YRot;
	//D3DXMatrixIdentity(&Rot);
	D3DXMatrixRotationY(&YRot, D3DXToRadian(m_rotSpeed) * Pad::GetInstance().GetRStickXF());

	D3DXVec3TransformCoord(&m_position, &m_position, &YRot);

	D3DXVECTOR3 vUP(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 Axis(0.0f,0.0f,0.0f);
	D3DXVec3Cross(&Axis, &m_position, &vUP);
	

	D3DXMatrixRotationAxis(&XRot, &Axis, D3DXToRadian(-m_rotSpeed) * Pad::GetInstance().GetRStickYF());
	D3DXVec3TransformCoord(&m_position, &m_position, &XRot);
	//カメラの視点を設定する。
	SpringCamera::GetInstance().SetTarPosition(SpringCamera::GetInstance().GetTarTarget() +m_position);
}

void gameCamera::TrackingCamera()
{
	//XZ平面上の注視点から視点までのベクトルを求めると長さを求める
	D3DXVECTOR3 CameraPosXZ = SpringCamera::GetInstance().GetTarPosition() - SpringCamera::GetInstance().GetTarTarget();

	float height = CameraPosXZ.y;
	CameraPosXZ.y = 0.0f;

	float CameraPosXZLen =D3DXVec3Length(&CameraPosXZ);

	D3DXVec3Normalize(&CameraPosXZ, &CameraPosXZ);

	//新しい注視点をアクターの座標から求める

	D3DXVECTOR3 target = Player::GetInstance().Getpos();
	target.y += 1.0f;

	//新しい注視点と現在のカメラの視点を使って、XZ平面上での、
	//注視点から視点までのベクトルを求める

	//D3DXVECTOR3 NewCameraPos = m_camera.GetEyePt() - target;

	D3DXVECTOR3 NewCameraPos = SpringCamera::GetInstance().GetTarPosition() - target;

	NewCameraPos.y = 0.0f;

	D3DXVec3Normalize(&NewCameraPos,&NewCameraPos);

	//新しい視点の決定

	float weight = 0.7f;

	NewCameraPos = NewCameraPos*weight + CameraPosXZ*(1.0f - weight);

	D3DXVec3Normalize(&NewCameraPos,&NewCameraPos);

	NewCameraPos *= CameraPosXZLen;

	NewCameraPos.y = height;

	D3DXVECTOR3 pos = target + NewCameraPos;

	//視点と注視点を設定
	
	SpringCamera::GetInstance().SetTarTarget(target);
	SpringCamera::GetInstance().SetTarPosition(pos);
	m_position = pos - target;

}

void gameCamera::BossStartCamera()
{
	m_stateCameraTime--;
	if (m_stateCameraTime > 0) {
		m_isBossStartCamera = true;
	}
	BossRockCamera();

	if (m_stateCameraTime < 0) {
		m_isBossStartCamera = false;
		//m_bossCamera = true;
	}
}

void gameCamera::BossEndCamera()
{
	m_endCameraTime--;
	if (m_endCameraTime > 0) {
		m_isBossEndCamera = true;
		m_isBossCamera = false;
	}
	BossRockCamera();

	if (m_endCameraTime < 0) {
		m_isBossEndCamera = false;
		//for(int i=0;i<10;i++)
		//TrackingCamera();
	}
}

//ボスとプレイヤーが常に移されるカメラ
void gameCamera::BossCamera()
{
	if (&BossEnemy::GetInstance() == NULL||&Player::GetInstance()==NULL) {
		m_isBossCamera = false; 
		return;
	}
	m_isBossCamera = true;

	//XZ平面上の注視点から視点までのベクトルを求めると長さを求める
	D3DXVECTOR3 CameraPosXZ = Player::GetInstance().Getpos() - BossEnemy::GetInstance().Getpos();;
	//CameraPosXZ.y -= 1.0f;
	float height = CameraPosXZ.y;
	CameraPosXZ.y = 0.0f;

	float CameraPosXZLen = D3DXVec3Length(&CameraPosXZ);

	D3DXVec3Normalize(&CameraPosXZ, &CameraPosXZ);

	//新しい注視点をアクターの座標から求める

	D3DXVECTOR3 target = BossEnemy::GetInstance().Getpos();
	target.y += 1.0f;

	//新しい注視点と現在のカメラの視点を使って、XZ平面上での、
	//注視点から視点までのベクトルを求める
	D3DXVECTOR3 NewCameraPos = SpringCamera::GetInstance().GetTarPosition() - target;

	NewCameraPos.y = 0.0f;

	D3DXVec3Normalize(&NewCameraPos, &NewCameraPos);

	//新しい視点の決定

	float weight = 0.7f;

	NewCameraPos = NewCameraPos*weight + CameraPosXZ*(1.0f - weight);

	D3DXVec3Normalize(&NewCameraPos, &NewCameraPos);

	NewCameraPos *= CameraPosXZLen*1.2f;//距離を後ろにずらす?

	NewCameraPos.y = height;

	D3DXVECTOR3 pos = target+NewCameraPos;
	pos.y += 0.7f;
	//視点と注視点を設定
	SpringCamera::GetInstance().SetTarTarget(target);
	SpringCamera::GetInstance().SetTarPosition(pos);
	if (BossEnemy::GetInstance().GetDeathflg())
	{
		m_isBossCamera = false;
	}

	//m_position = pos - target;
}

void gameCamera::BossRockCamera()
{
	const float flontUp = 2.0f;

	D3DXVECTOR3 targetPos = Player::GetInstance().Getpos();
	D3DXMATRIX matrix = Player::GetInstance().GetSkinModel()->GetWorldMatrix();//原点からのプレイヤーの向き
																			   //D3DXMatrixInverse(&matrix, NULL, &matrix);
	D3DXVECTOR3 flont;
	flont.x = matrix.m[2][0];
	flont.y = flontUp;
	flont.z = matrix.m[2][2];
	D3DXVec3Add(&flont, &flont, &targetPos);
	SpringCamera::GetInstance().SetTarPosition(flont);
	SpringCamera::GetInstance().SetTarTarget(BossEnemy::GetInstance().Getpos());

}