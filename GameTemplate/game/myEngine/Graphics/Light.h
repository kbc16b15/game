#pragma once

/*!
 * @brief	���C�g�N���X�B
 */
class Light{
public:
	static const int	DIFFUSE_LIGHT_NUM = 4;	//���s�����̐��B
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Light()
	{
		memset(this, 0, sizeof(Light));
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Light()
	{

	}
	/*!
	 * @brief	���s�����̕������擾�B
	 */
	const D3DXVECTOR4* GetDiffuseLightDirection() const
	{
		return diffuseLightDirection;
	}
	/*!
	 * @brief	���s�����̐F���擾�B
	 */
	const D3DXVECTOR4* GetDiffuseLightColor() const
	{
		return diffuseLightColor;
	}
	/*!
	 *@brief	���s�����̕�����ݒ�B
	 *@param[in]	lightNo		���C�g�̔ԍ�
     *@param[in]	dir			�����B
	 */
	void SetDiffuseLightDirection( int lightNo, const D3DXVECTOR4& dir )
	{
		diffuseLightDirection[lightNo] = dir;
	}
	/*!
	 *@brief	���s�����̐F��ݒ�B
	 *@param[in]	lightNo		���C�g�̔ԍ��B
	 *@param[in]	color		���s�����̐F�B
	 */
	void SetDiffuseLightColor( int lightNo, const D3DXVECTOR4& color )
	{
		diffuseLightColor[lightNo] = color;
	}
	/*!
	 * @brief	������ݒ�B
	 */
	void SetAmbientLight( const D3DXVECTOR4& ambient )
	{
		ambientLight = ambient;
	}
private:
	
	D3DXVECTOR4 			diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//���s�����̕����B
	D3DXVECTOR4				diffuseLightColor[DIFFUSE_LIGHT_NUM];		//���s�����̐F�B
	D3DXVECTOR4				ambientLight;						//����
};