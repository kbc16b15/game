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
	m_camera.SetEyePt(D3DXVECTOR3(5.0f, 7.0f, 8.0f));
	m_camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	m_camera.SetFar(1000.0f);
	m_camera.Update();
	toCameraPos = m_camera.GetEyePt() - m_camera.GetLookatPt();
	//position = m_camera.GetEyePt();
}

void gameCamera::Update()
{
	pad.Update();
	D3DXMATRIX m_Rot;
	D3DXMatrixIdentity(&m_Rot);

	if (pad.GetRStickXF()<0.0)
	{
		angle += 3.0f;
		D3DXMatrixRotationY(&m_Rot, D3DXToRadian(angle));

	}
	else if (pad.GetRStickXF()>0.0)
	{
			
		angle -= 3.0f;
		D3DXMatrixRotationY(&m_Rot, D3DXToRadian(angle));
	}
	else if (pad.GetRStickYF()<0.0)
	{
		angle += 1.0f;
		D3DXVECTOR3 Axis;
		D3DXVECTOR3 vUP(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&Axis, &toCameraPos, &vUP);
		if (angleX > 10.0f)
		{
			angle = 0.0f;
		}
		else
		{
			angleX += 1.0f;
		}
		D3DXMatrixRotationAxis(&m_Rot, &Axis, D3DXToRadian(angle));
	}
	else if (pad.GetRStickYF()>0.0)
	{
		angle -= 1.0f;
		D3DXVECTOR3 Axis;
		D3DXVECTOR3 vUP(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&Axis, &toCameraPos, &vUP);
		if (angleX <-10.0f)
		{
			angle = 0.0f;
		}
		else
		{
			angleX -= 1.0f;
		}
		D3DXMatrixRotationAxis(&m_Rot, &Axis, D3DXToRadian(angle));
	}
	angle = 0.0f;
	D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &m_Rot);
	m_camera.SetEyePt(m_camera.GetLookatPt() + toCameraPos);

	//プレイヤー追従カメラ。
	D3DXVECTOR3 targetPos = game->GetPlayer()->Getpos();
	if (targetPos.y < 0.0f)
	{
		targetPos.y = 0.0f;
	}
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;
	m_camera.SetLookatPt(targetPos);
	m_camera.SetEyePt(eyePos);
	m_camera.Update();
}

