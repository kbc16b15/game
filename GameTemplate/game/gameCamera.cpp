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
	camera.SetEyePt({0.0f, 0.0f,0.0f}); //プレイヤーの真上らへん
	camera.SetLookatPt({0.0f,0.0f,0.0f});   //プレイヤーの座標

}

void gameCamera::Update()
{


}
