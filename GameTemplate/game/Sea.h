#pragma once
#include "MapObject.h"
class Sea:public MapObject
{
public:
	//コンストラクタ
	Sea();
	//デストラクタ
	~Sea();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//更新
	void Update();
	//描画
	void Draw();

private:
	SkinModel			model;							//スキンモデル
	SkinModelData		modelData;						//スキンモデルデータ
	D3DXVECTOR3			position;						//座標
	D3DXQUATERNION		rotation;						//回転
	Light				light;							//ライト
	//LPDIRECT3DCUBETEXTURE9 m_cubeTex = nullptr;			//!<キューブテクスチャ。
	//LPDIRECT3DTEXTURE9	normalMap = NULL;				//法線マップ。

};

