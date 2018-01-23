#include "stdafx.h"
#include "gameCamera.h"


gameCamera::gameCamera()
{
}


gameCamera::~gameCamera()
{
}

void gameCamera::Init()
{
	m_camera.Init();
	m_camera.SetEyePt(D3DXVECTOR3(5.0f, 6.0f, 2.0f));
	m_camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	m_camera.SetFar(1000.0f);
	trackingCamera();
	m_camera.Update();
	m_position = m_camera.GetEyePt() - m_camera.GetLookatPt();
	//position = m_camera.GetEyePt();
}

void gameCamera::Update()
{
	pad.Update();
	RotCamera();
	//trackingCamera();
	if (g_game->GetPlayer()->GetPlayerMove())
	{
		//trackingCamera();
	}
	else {
		
		//RotCamera();
	}
	//RockCamera();
	
	m_camera.Update();
}

void gameCamera::RotCamera()
{
	D3DXMATRIX XRot;
	D3DXMATRIX YRot;
	D3DXMatrixIdentity(&XRot);
	D3DXMatrixIdentity(&YRot);
	if (pad.GetRStickXF()<0.0)
	{
		D3DXMatrixRotationY(&XRot, D3DXToRadian(-RotSpeedY));

	}
	if (pad.GetRStickXF()>0.0)
	{

		D3DXMatrixRotationY(&XRot, D3DXToRadian(RotSpeedY));
	}

	D3DXVec3TransformCoord(&m_position, &m_position, &XRot);
	//D3DXVECTOR3 toCpos = toCameraPos;
	if (pad.GetRStickYF()<0.0)
	{
		D3DXVECTOR3 Axis;
		D3DXVECTOR3 vUP(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&Axis, &m_position, &vUP);
		D3DXMatrixRotationAxis(&YRot, &Axis, D3DXToRadian(RotSpeedX));
	}
	if (pad.GetRStickYF()>0.0)
	{
		D3DXVECTOR3 Axis;
		D3DXVECTOR3 vUP(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&Axis, &m_position, &vUP);
		D3DXMatrixRotationAxis(&YRot, &Axis, D3DXToRadian(-RotSpeedX));
	}

	D3DXVec3TransformCoord(&m_position, &m_position, &YRot);
	//toCameraPos=toCpos + toCameraPos;
	//D3DXMatrixMultiply(&YRot,&XRot, &YRot);
	//プレイヤー追従カメラ。
	D3DXVECTOR3 targetPos = g_game->GetPlayer()->Getpos();
	/*if (targetPos.y < 0.0f)
	{
	targetPos.y = 0.0f;
	}*/
	//if (!Rockonflg)
	targetPos.y += 1.0f;
	m_camera.SetLookatPt(targetPos);
	m_camera.SetEyePt(m_camera.GetLookatPt() + m_position);
}

void gameCamera::trackingCamera()
{
	//XZ平面上の注視点から視点までのベクトルを求めると長さを求める
	D3DXVECTOR3 CameraPosXZ = m_camera.GetEyePt() - m_camera.GetLookatPt();

	//CameraPosXZ.y -= 1.0f;
	float height = CameraPosXZ.y;
	CameraPosXZ.y = 0.0f;

	float CameraPosXZLen =D3DXVec3Length(&CameraPosXZ);

	D3DXVec3Normalize(&CameraPosXZ, &CameraPosXZ);

	//新しい注視点をアクターの座標から求める

	D3DXVECTOR3 target = g_game->GetPlayer()->Getpos();
	target.y += 1.0f;

	//新しい注視点と現在のカメラの視点を使って、XZ平面上での、
	//注視点から視点までのベクトルを求める

	D3DXVECTOR3 NewCameraPos = m_camera.GetEyePt() - target;

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
	
	m_camera.SetEyePt(pos);

	m_camera.SetLookatPt(target);


}

void gameCamera::RockCamera()
{
	//if (Rockonflg)
	//{
	//	D3DXVECTOR3 ReyePos = g_game->GetPlayer()->Getpos();
	//	D3DXVECTOR3 RtargetPos = g_game->GetPlayer()->Getpos();
	//	ReyePos.x += 1.0f;
	//	ReyePos.z += 0.8f;
	//	ReyePos.y += 1.2f;
	//	RtargetPos.x -= 10.0f;

	//	/*if (GetAsyncKeyState('H') || pad.GetRStickXF() < 0.0f)
	//	{
	//		vec.z += 0.5f;
	//	}
	//	else if (GetAsyncKeyState('K') || pad.GetRStickXF() > 0.0f)
	//	{
	//		vec.z -= 0.5f;
	//	}
	//	else if (GetAsyncKeyState('N') || pad.GetRStickYF() < 0.0f)
	//	{
	//		vec.y += 0.5f;
	//	}
	//	else if (GetAsyncKeyState('U') || pad.GetRStickYF() > 0.0f)
	//	{
	//		vec.y -= 0.5f;
	//	}*/
	//	RtargetPos += vec;
	//	m_camera.SetLookatPt(RtargetPos);
	//	m_camera.SetEyePt(ReyePos);
	//}
}

