#pragma once
class CubeCollision
{
public:
	//コンストラクタ
	CubeCollision();
	//デストラクタ
	~CubeCollision();
	//球と球の当たり判定
	//p1	一つ目の球の座標
	//p2	二つ目の球の座標
	//r1	一つ目の球の半径(大きさ)
	//r2	二つ目の球の半径(大きさ)
	bool Cubemass(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float r1, float r2);

};

