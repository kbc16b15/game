#include "stdafx.h"
#include "gameCamera.h"

gameCamera::gameCamera()
{
}


gameCamera::~gameCamera()
{
}

void gameCamera::Start()
{
	camera.SetEyePt({0.0f, 0.0f,0.0f}); //�v���C���[�̐^���ւ�
	camera.SetLookatPt({0.0f,0.0f,0.0f});   //�v���C���[�̍��W

}

void gameCamera::Update()
{


}
