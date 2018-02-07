#pragma once
#include "MapObject.h"
class BoxChip :
	public MapObject
{
public:
	//BoxChip();
	//~BoxChip();

	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION	rot) override;
	//更新
	//void Update();
	//描画
	//void Draw();
private:
	BoxCollider			m_boxCollider;			//ボックスコライダー
//	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//法線マップ
//
};

