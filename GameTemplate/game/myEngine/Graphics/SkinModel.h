/*!
*@brief	スキンモデル
*/
#pragma once

#include "myEngine/Graphics/Animation.h"


class SkinModelData;
class RenderContext;
class Light;
//class ShadowMap;
/*!
*@brief	スキンモデル
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	初期化
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	描画。
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
	
	/*!
	*@brief	ワールド行列を更新。
	*@details
	* 後でCMotionクラスに移動させます。
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );
	/*!
	*@brief	ライトを設定。
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	//スペキュラマップの設定
	void SetSpecularMap(LPDIRECT3DTEXTURE9 specMap)
	{
		specularMap = specMap;
	}
	//法線マップの設定
	void SetnormalMap(LPDIRECT3DTEXTURE9 normMap)
	{
		normalMap = normMap;
	}
	//キューブマップの設定
	void SetcubeMap(LPDIRECT3DCUBETEXTURE9 CubeMap)
	{
		cubeMap = CubeMap;
	}

	void SetCubeflg(bool cubeflg)
	{
		Cubeflg = true;
	}

	void SetCasterflg(bool Caster)
	{
		ShadowCaster = Caster;
	}

	void SetReciveflg(bool Recive)
	{
		ShadowRecive = Recive;
	}
	/*!
	*@brief	オリジナルメッシュの先頭を取得する。
	*/
	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX			worldMatrix;				//!<ワールド行列。
	D3DXMATRIX			rotationMatrix;				//!<回転行列。
	SkinModelData*		skinModelData = nullptr;	//!<スキンモデルデータ。
	ID3DXEffect*		pEffect = nullptr;			//!<エフェクト。
	Animation			animation;					//!<アニメーション。
	Light*				light = nullptr;			//!<ライト。
	LPDIRECT3DTEXTURE9		normalMap = NULL;		//!法線マップ
	LPDIRECT3DTEXTURE9		specularMap = NULL;		//!スペキュラマップ
	LPDIRECT3DTEXTURE9		shadowMap = NULL;		//!シャドウマップ
	LPDIRECT3DCUBETEXTURE9	cubeMap = NULL;			//!キューブマップ
	bool				Cubeflg = false;
	bool				ShadowCaster = false;
	bool				ShadowRecive = false;

};
