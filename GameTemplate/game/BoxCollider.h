#pragma once
#include "myEngine\Physics\ICollider.h"
class BoxCollider ://ラッパークラス
	public ICollider
{
public:
	//コンストラクタ
	BoxCollider();
	//デストラクタ
	~BoxCollider();
	//ボックスの作成
	//halfSize サイズ
	void Create(const D3DXVECTOR3& halfSize);
	//ボックスの取得
	btCollisionShape* GetBody() override
	{
		return m_boxShape;
	}
private:
	btBoxShape* m_boxShape=nullptr;//ボックスコライダー
};

