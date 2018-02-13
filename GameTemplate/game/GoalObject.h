#pragma once
#include "MapObject.h"
class GoalObject :public MapObject
{
public:
	//コンストラクタ
	//GoalObject();
	//デストラクタ
	//~GoalObject();
	//初期化
	//modelName モデル名
	//pos		モデルの座標
	//rotation	モデルの回転
	//void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation) override;
	//更新
	void Update() override;
	//描画
	//void Draw();

private:
	//ParticleEmitter		m_particleEmitter;	//パーティクル
};

