/*!
 *@brief	�X�L�����f���f�[�^
 */
 
#pragma once


struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
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
 *@brief	�X�L�����f���f�[�^
 */
class SkinModelData{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	SkinModelData();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~SkinModelData();
	/*!
	 * @brief	���f���f�[�^�����[�h�B
	 *@param[in]	filePath	�t�@�C���p�X�B
	 *@param[out]	anim		�A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z����܂��B
	 */
	void LoadModelData( const char* filePath, Animation* anim );
	/*!
	* @brief	���f���f�[�^�̃N���[�����쐬�B
	* @details
	*	�X�P���g���͐V�����쐬����A���b�V���f�[�^�͋��ʂ̂��̂��g�p����܂��B
	*@param[in]		modelData		���f���f�[�^�B
	*/
	void CloneModelData(const SkinModelData& modelData, Animation* anim);
	/*!
	* @brief	�����[�X�B
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
	//�I���W�i���̃X�P���g��������
	//frame �X�P���g��
	void DeleteSkeleton(LPD3DXFRAME frame);
	//�X�P���g���̃N���[�����쐬
	//dstFrame�@�N���[����̃X�P���g���̊i�[��
	//srcFrame�@�N���[�����̃X�P���g��
	void CloneSkeleton(LPD3DXFRAME& dstFrame, LPD3DXFRAME srcFrame);
	//�X�P���g���̃N���[��������
	//frame ��������X�P���g��
	void DeleteCloneSkeleton(LPD3DXFRAME frame);
	/*!
	* @brief	�{�[���s����X�V�B
	*/
	void UpdateBoneMatrix( const D3DXMATRIX& matWorld );
	/*!
	* @brief	��ԍŏ��Ɍ��������I���W�i�����b�V�����擾�B
	*/
	LPD3DXMESH GetOrgMeshFirst();
	/*!
	* @brief	���[�g�̃{�[�����擾�B
	*/
	D3DXMATRIX* GetRootBoneWorldMatrix()
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}
private:
	/*!
	* @brief	��ԍŏ��Ɍ��������I���W�i�����b�V�����擾�B
	*/
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) ;
private:
	LPD3DXFRAME					frameRoot;		//�t���[�����[�g�B
	ID3DXAnimationController*   pAnimController;	//�A�j���[�V�����R���g���[���B
	bool						m_isClone;//�N���[��
	const SkinModelData*		m_original = nullptr;
};
