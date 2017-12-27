#pragma once
#include "MapObject.h"
class Sky:public MapObject
{
public:
	//コンストラクタ
	Sky();
	//デストラクタ
	~Sky();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	////更新
	void Update();
	////描画
	void Draw();

private:
	SkinModel				m_model;								//スキンモデル
	SkinModelData			m_modelData;							//スキンモデルデータ
	D3DXVECTOR3				m_position;								//座標
	D3DXQUATERNION			m_rotation = {0.0f,0.0f,0.0f,1.0f};		//回転
	Light					m_light;								//ライト
	LPDIRECT3DCUBETEXTURE9	m_cubeTex = nullptr;				//!<キューブテクスチャ。
};

