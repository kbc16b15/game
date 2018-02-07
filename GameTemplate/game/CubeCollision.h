#pragma once
class CubeCollision
{
public:

	//デストラクタ
	~CubeCollision();
	//球と球の当たり判定
	//p1	一つ目の球の座標
	//p2	二つ目の球の座標
	//r1	一つ目の球の半径(大きさ)
	//r2	二つ目の球の半径(大きさ)
	bool Cube(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float r1, float r2);

	//インスタンスの生成
	static void CubeCollision::Create()
	{
		if (!m_cube)
		{
			m_cube = new CubeCollision;
		}

	}

	//インスタンスの消去
	static  void CubeCollision::Destroy()
	{
		delete m_cube;
		m_cube = nullptr;
	}
	//インスタンスの取得
	static CubeCollision& GetInstance()
	{
		return *m_cube;
	}
private:
	//コンストラクタ
	CubeCollision();
	static CubeCollision* m_cube;
};