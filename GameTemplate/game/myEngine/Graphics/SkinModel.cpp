#include "stdafx.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/Light.h"
#include <d3d9types.h>
#include "ShadowMap.h"

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices ;
extern ShadowMap*		g_shadowmap;
namespace {
	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice, 
		LPD3DXMESHCONTAINER pMeshContainerBase, 
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		Light* light,
		LPDIRECT3DTEXTURE9 normalMap,
		LPDIRECT3DTEXTURE9 specularMap,
		LPDIRECT3DTEXTURE9 shadowMap,
		LPDIRECT3DCUBETEXTURE9 cubeMap,
		bool ShadowCaster,
		bool ShadowRecive,
		bool Cubeflg
	)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
		UINT iAttrib;
		LPD3DXBONECOMBINATION pBoneComb;

		D3DXMATRIXA16 matTemp;
		D3DCAPS9 d3dCaps;
		pd3dDevice->GetDeviceCaps(&d3dCaps);
		D3DXMATRIX viewProj;
		D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);
		//テクニックを設定。
		{
			if (Cubeflg)
			{
				pEffect->SetTechnique("SkyModel");
			}
			else if (pMeshContainer->pSkinInfo != NULL)
			{

				if (ShadowCaster)
				{
					pEffect->SetTechnique("ShadowSkinModel");
				}
				else
				{
					pEffect->SetTechnique("SkinModel");
				}
			}
			else if(pMeshContainer->pSkinInfo == NULL)
			{
				if (ShadowCaster) {
					pEffect->SetTechnique("ShadowNoSkinModel");
				}
				else {
					pEffect->SetTechnique("NoSkinModel");
				}
			}
			
		}
		//共通の定数レジスタを設定
		{
			pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			pEffect->BeginPass(0);
			pEffect->SetInt("g_Reciver",ShadowRecive);
	
			pEffect->SetMatrix("g_projectionMatrix", projMatrix);
			pEffect->SetMatrix("g_viewMatrix", viewMatrix);
			
			
			//ビュープロジェクション
			pEffect->SetMatrix("g_mViewProj", &viewProj);
			//ライト
			pEffect->SetValue(
				"g_light",
				light,
				sizeof(Light)
			);
		}

		if (cubeMap != NULL)
		{
			pEffect->SetTexture("g_cubeTex", cubeMap);
		}

		//if (specularMap != NULL)
		//{
		//	//スペキュラマップがあるから、シェーダーに転送
		//	pEffect->SetTexture("g_specularTexture", specularMap);
		//	//スペキュラマップのフラグをtrueにする。
		//	pEffect->SetBool("g_isHasSpecularMap",true);
		//}
		//else {
		//	pEffect->SetBool("g_isHasSpecularMap", false);
		//}

		//if (normalMap != NULL)
		//{
		//	//法線マップがあるから、シェーダーに転送
		//	pEffect->SetTexture("g_normalTexture", normalMap);
		//	//法線マップのフラグをtrueにする。
		//	pEffect->SetBool("g_isHasNormalMap", true);
		//}
		/*else {
			pEffect->SetBool("g_isHasNormalMap", false);
		}*/

		if (ShadowRecive){

			pEffect->SetMatrix("g_viewlightMatrix", &g_shadowmap->GetlightViewMatrix()/*&g_shadowmap->lightViewMatrix*/);
			pEffect->SetMatrix("g_projlightMatrix", &g_shadowmap->GetlightProjectionMatrix()/*&g_shadowmap->lightProjectionMatrix*/);
			pEffect->SetTexture("g_shadowMapTexture", g_shadowmap->GetTexture());
		}

		if (pMeshContainer->pSkinInfo != NULL)
		{
			//スキン情報有り。
			pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
			for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
			{
				// first calculate all the world matrices
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(
							&g_pBoneMatrices[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
						);
						//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &g_matView);
					}
				}
				D3DXVECTOR4 CameraEye = game->GetCamera()->GetEyePt();//カメラの視点の座標
				CameraEye.w = 1.0f;
				pEffect->SetVector("Eye", &CameraEye);
				
				pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
				pEffect->SetInt("g_numBone", pMeshContainer->NumInfl);
				// ディフューズテクスチャ。
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);
				//ボーン数。
				pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
				D3DXMATRIX viewRotInv;
				D3DXMatrixInverse(&viewRotInv, NULL, viewMatrix);
				viewRotInv.m[3][0] = 0.0f;
				viewRotInv.m[3][1] = 0.0f;
				viewRotInv.m[3][2] = 0.0f;
				viewRotInv.m[3][3] = 1.0f;
				D3DXMatrixTranspose(&viewRotInv, &viewRotInv);
				pEffect->SetMatrix("g_viewMatrixRotInv", &viewRotInv);
				pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
				pEffect->BeginPass(0);
				pEffect->CommitChanges();
				// draw the subset with the current world matrix palette and material state
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				pEffect->EndPass();
				pEffect->End();
			}
		}
		else {
						
			D3DXMATRIX mWorld;
			if (pFrame != NULL) {
				mWorld = pFrame->CombinedTransformationMatrix;
			}
			else {
				mWorld = *worldMatrix;
			}

			pEffect->SetMatrix("g_worldMatrix", &mWorld);
			pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);
			pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
			pEffect->BeginPass(0);
			
			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
				pEffect->CommitChanges();
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
			
			pEffect->EndPass();
			pEffect->End();
		}
	}
	void DrawFrame(
		IDirect3DDevice9* pd3dDevice, 
		LPD3DXFRAME pFrame, 
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix,
		Light* light,
		LPDIRECT3DTEXTURE9 normalMap,
		LPDIRECT3DTEXTURE9 specularMap,
		LPDIRECT3DTEXTURE9 shadowMap,
		LPDIRECT3DCUBETEXTURE9 cubeMap,
		bool ShadowCaster,
		bool ShadowRecive,
		bool Cubeflg
	)
	{
		LPD3DXMESHCONTAINER pMeshContainer;

		pMeshContainer = pFrame->pMeshContainer;
		while (pMeshContainer != NULL)
		{
			DrawMeshContainer(
				pd3dDevice, 
				pMeshContainer, 
				pFrame, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				normalMap,
				specularMap,
				shadowMap,
				cubeMap,
				ShadowCaster,
				ShadowRecive,
				Cubeflg
				);

			pMeshContainer = pMeshContainer->pNextMeshContainer;
		}

		if (pFrame->pFrameSibling != NULL)
		{
			DrawFrame(
				pd3dDevice, 
				pFrame->pFrameSibling, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				normalMap,
				specularMap,
				shadowMap,
				cubeMap,
				ShadowCaster,
				ShadowRecive,
				Cubeflg
				);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			DrawFrame(
				pd3dDevice,
				pFrame->pFrameFirstChild, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				normalMap,
				specularMap,
				shadowMap,
				cubeMap,
				ShadowCaster,
				ShadowRecive,
				Cubeflg
				);
		}
	}

	
}
SkinModel::SkinModel() :
	skinModelData(nullptr),
	light(nullptr),
	pEffect(nullptr)
{
}
SkinModel::~SkinModel()
{

}

void SkinModel::Init(SkinModelData* modelData)
{

	pEffect = g_effectManager->LoadEffect("Assets/Shader/model.fx");

	skinModelData = modelData;

}

void SkinModel::UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale)
{
	D3DXMATRIX mTrans, mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

	worldMatrix = mScale * rotationMatrix * mTrans;

	if (skinModelData) {
		skinModelData->UpdateBoneMatrix(worldMatrix);	//ボーン行列を更新。
	}
}

void SkinModel::Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix)
{
	if (skinModelData) {
		DrawFrame(
			g_pd3dDevice,
			skinModelData->GetFrameRoot(), 
			pEffect,
			&worldMatrix,
			&rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			normalMap,
			specularMap,
			shadowMap,
			cubeMap,
			ShadowCaster,
			ShadowRecive,
			Cubeflg
		);
	}
}
LPD3DXMESH SkinModel::GetOrgMeshFirst()
{
	if(skinModelData != nullptr){
		return skinModelData->GetOrgMeshFirst();
	}
	return nullptr;
}