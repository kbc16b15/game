#pragma once
/*!
* @brief	�Q�[���p�b�h�N���X�B
*/
#pragma once

#include <XInput.h> // XInput API
#include "IGameObject.h"
/*!
*@brief	�p�b�h�X�e�[�g�B
*/
struct PAD_STATE
{
	XINPUT_STATE state;
	bool bConnected;
};
/*!
* @brief	�Q�[���p�b�h�N���X�B
*/
class Pad/*:public IGameObject*/
{
public:
	/*!
	* @brief	���z�{�^����`�B
	*/
	enum EnButton {
		enButtonUp,			//!<��B
		enButtonDown,		//!<���B
		enButtonLeft,		//!<���B
		enButtonRight,		//!<�E�B
		enButtonA,			//!<A�{�^���B
		enButtonB,			//!<B�{�^���B
		enButtonX,			//!<X�{�^���B
		enButtonY,			//!<Y�{�^���B
		enButtonSelect,		//!<�Z���N�g�{�^���B
		enButtonStart,		//!<�X�^�[�g�{�^���B
		enButtonRB1,		//!<RB1�{�^���B
		enButtonRB2,		//!<RB2�{�^���B
		enButtonRB3,		//!<RB3�{�^���B
		enButtonLB1,		//!<LB1�{�^���B
		enButtonLB2,		//!<LB2�{�^���B
		enButtonLB3,		//!<LB3�{�^���B
		enButtonNum,		//!<�{�^���̐��B
	};
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Pad();
	/*!
	* @brief	�������B
	*/
	//void Init();
	void Update();
	//void Draw();
	/*!
	*@brief	�{�^���̃g���K�[����B
	*@return	true���Ԃ��Ă�����g���K�[���́B
	*/
	bool IsTrigger(EnButton button) const
	{
		return m_trigger[button] != 0;
	}
	/*!
	*@brief	�{�^����������Ă��邩����B
	*@return	true���Ԃ��Ă����牟����Ă���B
	*/
	bool IsPress(EnButton button) const
	{
		return m_press[button] != 0;
	}
	/*!
	*@brief	���X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickXF() const
	{
		return m_lStickX;
	}
	/*!
	*@brief	���X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickYF() const
	{
		return m_lStickY;
	}
	/*!
	*@brief	�E�X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickXF() const
	{
		return m_rStickX;
	}
	/*!
	*@brief	�E�X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickYF() const
	{
		return m_rStickY;
	}

	//�C���X�^���X�̐���
	static  void Pad::Create()
	{
		if (!m_pad)
		{
			m_pad = new Pad;

		}
	}

	//�C���X�^���X�̏���
	static  void Pad::Destroy()
	{
		delete m_pad;
		m_pad = nullptr;
	}
	//�C���X�^���X�̎擾
	static Pad& GetInstance()
	{
		return *m_pad;
	}
private:
	//�R���X�g���N�^�B
	Pad();

	static Pad*		m_pad;
	PAD_STATE	m_state;	//!<�p�b�h�X�e�[�g�B
	int m_padNo = 0;
	int m_trigger[enButtonNum];	//!<trigger���͂̃t���O�B
	int m_press[enButtonNum];	//!<press���͂̃t���O�B
	float m_lStickX;			//!<���X�e�B�b�N��X���̓��͗ʁB
	float m_lStickY;			//!<���X�e�B�b�N��Y���̓��͗ʁB
	float m_rStickX;			//!<�E�X�e�B�b�N��X���̓��͗ʁB
	float m_rStickY;			//!<�E�X�e�B�b�N��Y���̓��͗ʁB
};

