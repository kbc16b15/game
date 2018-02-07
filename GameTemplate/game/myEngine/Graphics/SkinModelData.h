/*!
 *@brief	スキンモデルデータ
 */
 
#pragma once


struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	LPDIRECT3DTEXTURE9* ppTextures;
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;
};
class Animation;
/*!
 *@brief	スキンモデルデータ
 */
class SkinModelData{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	SkinModelData();
	/*!
	 *@brief	デストラクタ。
	 */
	~SkinModelData();
	/*!
	 * @brief	モデルデータをロード。
	 *@param[in]	filePath	ファイルパス。
	 *@param[out]	anim		アニメーション付きモデルデータの場合、アニメーションクラスも構築されます。
	 */
	void LoadModelData( const char* filePath, Animation* anim );
	/*!
	* @brief	モデルデータのクローンを作成。
	* @details
	*	スケルトンは新しく作成され、メッシュデータは共通のものが使用されます。
	*@param[in]		modelData		モデルデータ。
	*/
	void CloneModelData(const SkinModelData& modelData, Animation* anim);
	/*!
	* @brief	リリース。
	*/
	void Release();
	LPD3DXFRAME GetFrameRoot()
	{
		return frameRoot;
	}
	ID3DXAnimationController* GetAnimationController()
	{
		return pAnimController;
	}
	//オリジナルのスケルトンを消去
	//frame スケルトン
	void DeleteSkeleton(LPD3DXFRAME frame);
	//スケルトンのクローンを作成
	//dstFrame　クローン先のスケルトンの格納先
	//srcFrame　クローン元のスケルトン
	void CloneSkeleton(LPD3DXFRAME& dstFrame, LPD3DXFRAME srcFrame);
	//スケルトンのクローンを消去
	//frame 消去するスケルトン
	void DeleteCloneSkeleton(LPD3DXFRAME frame);
	/*!
	* @brief	ボーン行列を更新。
	*/
	void UpdateBoneMatrix( const D3DXMATRIX& matWorld );
	/*!
	* @brief	一番最初に見つかったオリジナルメッシュを取得。
	*/
	LPD3DXMESH GetOrgMeshFirst();
	/*!
	* @brief	ルートのボーンを取得。
	*/
	D3DXMATRIX* GetRootBoneWorldMatrix()
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}
private:
	/*!
	* @brief	一番最初に見つかったオリジナルメッシュを取得。
	*/
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) ;
private:
	LPD3DXFRAME					frameRoot;		//フレームルート。
	ID3DXAnimationController*   pAnimController;	//アニメーションコントローラ。
	bool						m_isClone;//クローン
	const SkinModelData*		m_original = nullptr;
};
