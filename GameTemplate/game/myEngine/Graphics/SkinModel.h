/*!
*@brief	�X�L�����f��
*/
#pragma once

#include "myEngine/Graphics/Animation.h"


class SkinModelData;
class RenderContext;
class Light;
//class ShadowMap;
/*!
*@brief	�X�L�����f��
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	������
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	�`��B
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
	
	/*!
	*@brief	���[���h�s����X�V�B
	*@details
	* ���CMotion�N���X�Ɉړ������܂��B
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );

	void UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale,D3DXMATRIX mat, D3DXMATRIX rotmat);
	/*!
	*@brief	���C�g��ݒ�B
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	//�X�y�L�����}�b�v�̐ݒ�
	void SetSpecularMap(LPDIRECT3DTEXTURE9 specMap)
	{
		specularMap = specMap;
	}
	//�X�y�L�������C�g�̐ݒ�
	void SetSpecularlight(bool speclight)
	{
		Specularlight = speclight;
	}
	//�@���}�b�v�̐ݒ�
	void SetnormalMap(LPDIRECT3DTEXTURE9 normMap)
	{
		normalMap = normMap;
	}
	//�L���[�u�}�b�v�̐ݒ�
	void SetcubeMap(LPDIRECT3DCUBETEXTURE9 CubeMap)
	{
		cubeMap = CubeMap;
	}

	//�e�𗎂Ƃ����f���̐ݒ�
	void SetCasterflg(bool Caster)
	{
		ShadowCaster = Caster;
	}
	//�e�𗎂Ƃ���郂�f���̐ݒ�
	void SetReciveflg(bool Recive)
	{
		ShadowRecive = Recive;
	}
	/*!
	* @brief	���[���h�s����擾�B
	*/
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return worldMatrix;
	}
	/*!
	*@brief	�I���W�i�����b�V���̐擪���擾����B
	*/
	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX			worldMatrix;				//!<���[���h�s��B
	D3DXMATRIX			rotationMatrix;				//!<��]�s��B
	SkinModelData*		skinModelData = nullptr;	//!<�X�L�����f���f�[�^�B
	ID3DXEffect*		pEffect = nullptr;			//!<�G�t�F�N�g�B
	Animation			animation;					//!<�A�j���[�V�����B
	Light*				light = nullptr;			//!<���C�g�B
	LPDIRECT3DTEXTURE9		normalMap = NULL;		//!�@���}�b�v
	LPDIRECT3DTEXTURE9		specularMap = NULL;		//!�X�y�L�����}�b�v
	LPDIRECT3DTEXTURE9		shadowMap = NULL;		//!�V���h�E�}�b�v
	LPDIRECT3DCUBETEXTURE9	cubeMap = NULL;			//!�L���[�u�}�b�v
	//bool				Cubeflg = false;
	bool				Specularlight = false;
	bool				ShadowCaster = false;
	bool				ShadowRecive = false;
	
};
