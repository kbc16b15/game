#pragma once
#include "myEngine/Graphics/Camera.h"
class gameCamera
{
public:
	gameCamera();
	~gameCamera();
	void Start();
	void Update();

	D3DXMATRIX& GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}
	D3DXMATRIX& GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}
	Camera& GetCamera()
	{
		return camera;
	}
private:
	Camera camera;

	D3DXVECTOR3 pos = { 0.0f,  2.0f,  3.0f };
	D3DXVECTOR3 tag = { 1.0,1.0,1.0 };


};

