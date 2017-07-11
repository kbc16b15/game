#include "stdafx.h"
#include "myEngine/HID/Pad.h"


#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

namespace {
	/*!
	*@brief	���z�{�^����XBox�R���g���[���̃{�^���Ƃ̊֘A�t����\���\���́B
	*/
	struct VirtualPadToXPad {
		Pad::EnButton vButton;		//!<���z�{�^���B
		DWORD		  xButton;		//!<XBox�R���g���[���̃{�^���B
	};

	//���z�{�^����XBox�R���g���[���Ƃ̃{�^���̕ϊ��e�[�u���B
	const VirtualPadToXPad vPadToXPadTable[Pad::enButtonNum] = {
		{ Pad::enButtonUp		, XINPUT_GAMEPAD_DPAD_UP },
		{ Pad::enButtonDown		, XINPUT_GAMEPAD_DPAD_DOWN },
		{ Pad::enButtonLeft		, XINPUT_GAMEPAD_DPAD_LEFT },
		{ Pad::enButtonRight	, XINPUT_GAMEPAD_DPAD_RIGHT },
		{ Pad::enButtonA		, XINPUT_GAMEPAD_A },
		{ Pad::enButtonB		, XINPUT_GAMEPAD_B },
		{ Pad::enButtonY		, XINPUT_GAMEPAD_Y },
		{ Pad::enButtonX		, XINPUT_GAMEPAD_X },
		{ Pad::enButtonSelect	, XINPUT_GAMEPAD_BACK },
		{ Pad::enButtonStart	, XINPUT_GAMEPAD_START },
		{ Pad::enButtonRB1		, XINPUT_GAMEPAD_RIGHT_SHOULDER },
		{ Pad::enButtonRB2		, 0 },
		{ Pad::enButtonRB3		, XINPUT_GAMEPAD_RIGHT_THUMB },
		{ Pad::enButtonLB1		, XINPUT_GAMEPAD_LEFT_SHOULDER },
		{ Pad::enButtonLB2		, 0 },
		{ Pad::enButtonLB3		, XINPUT_GAMEPAD_LEFT_THUMB },
	};
	/*!
	*@brief	���z�{�^���ƃL�[�{�[�h�Ƃ̊֘A�t����\���\���́B
	*/
	struct VirtualPadToKeyboard {
		Pad::EnButton vButton;		//!<���z�{�^��
		DWORD keyCoord;			//!<�L�[�{�[�h�̃L�[�R�[�h�B
	};
	const VirtualPadToKeyboard vPadToKeyboardTable[Pad::enButtonNum] = {
		{ Pad::enButtonUp		, '8' },
		{ Pad::enButtonDown		, '2' },
		{ Pad::enButtonLeft		, '4' },
		{ Pad::enButtonRight		, '6' },
		{ Pad::enButtonA			, 'J' },
		{ Pad::enButtonB			, 'K' },
		{ Pad::enButtonY			, 'I' },
		{ Pad::enButtonX			, 'O' },
		{ Pad::enButtonSelect	, VK_SPACE },
		{ Pad::enButtonStart		, VK_RETURN },
		{ Pad::enButtonRB1		, '7' },
		{ Pad::enButtonRB2		, '8' },
		{ Pad::enButtonRB3		, '9' },
		{ Pad::enButtonLB1		, 'B' },
		{ Pad::enButtonLB2		, 'N' },
		{ Pad::enButtonLB3		, 'M' },
	};
}
Pad::Pad() :
	m_padNo(0)
{
	memset(&m_state, 0, sizeof(m_state));
	memset(m_trigger, 0, sizeof(m_trigger));
	memset(m_press, 0, sizeof(m_press));
	m_lStickX = 0.0f;
	m_lStickY = 0.0f;
	m_rStickX = 0.0f;
	m_rStickY = 0.0f;
}
Pad::~Pad()
{
}
void Pad::Update()
{
	DWORD result = XInputGetState(m_padNo, &m_state.state);
	if (result == ERROR_SUCCESS) {
		//�ڑ�����Ă���B

		for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable) {
			if (m_state.state.Gamepad.wButtons & vPadToXPad.xButton) {
				m_trigger[vPadToXPad.vButton] = 1 ^ m_press[vPadToXPad.vButton];
				m_press[vPadToXPad.vButton] = 1;
			}
			else {
				m_trigger[vPadToXPad.vButton] = 0;
				m_press[vPadToXPad.vButton] = 0;
			}
		}
		//���g���K�[�B
		if (m_state.state.Gamepad.bLeftTrigger != 0) {
			m_trigger[enButtonLB2] = 1 ^ m_press[enButtonLB2];
			m_press[enButtonLB2] = 1;
		}
		else {
			m_trigger[enButtonLB2] = 0;
			m_press[enButtonLB2] = 0;
		}
		//�E�g���K�[
		if (m_state.state.Gamepad.bRightTrigger != 0) {
			m_trigger[enButtonRB2] = 1 ^ m_press[enButtonRB2];
			m_press[enButtonRB2] = 1;
		}
		else {
			m_trigger[enButtonRB2] = 0;
			m_press[enButtonRB2] = 0;
		}
		if ((m_state.state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
			(m_state.state.Gamepad.sThumbLY < INPUT_DEADZONE &&
				m_state.state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			m_state.state.Gamepad.sThumbLX = 0;
			m_state.state.Gamepad.sThumbLX = 0;
			m_state.state.Gamepad.sThumbLY = 0;
			m_lStickX = 0.0f;
			m_lStickY = 0.0f;
		}
		else {
			//���X�e�B�b�N�̓��͗ʁB
			if (m_state.state.Gamepad.sThumbLX > 0) {
				m_lStickX = (float)(m_state.state.Gamepad.sThumbLX) / SHRT_MAX;
			}
			else {
				m_lStickX = (float)(m_state.state.Gamepad.sThumbLX) / -SHRT_MIN;
			}
			if (m_state.state.Gamepad.sThumbLY > 0) {
				m_lStickY = (float)(m_state.state.Gamepad.sThumbLY) / SHRT_MAX;
			}
			else {
				m_lStickY = (float)(m_state.state.Gamepad.sThumbLY) / -SHRT_MIN;
			}
		}

		if ((m_state.state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
			(m_state.state.Gamepad.sThumbRY < INPUT_DEADZONE &&
				m_state.state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			m_state.state.Gamepad.sThumbRX = 0;
			m_state.state.Gamepad.sThumbRY = 0;
			m_rStickX = 0.0f;
			m_rStickY = 0.0f;
		}
		else {
			//�E�X�e�B�b�N�̓��͗ʁB
			if (m_state.state.Gamepad.sThumbRX > 0) {
				m_rStickX = (float)(m_state.state.Gamepad.sThumbRX) / SHRT_MAX;
			}
			else {
				m_rStickX = (float)(m_state.state.Gamepad.sThumbRX) / -SHRT_MIN;
			}
			if (m_state.state.Gamepad.sThumbRY > 0) {
				m_rStickY = (float)(m_state.state.Gamepad.sThumbRY) / SHRT_MAX;
			}
			else {
				m_rStickY = (float)(m_state.state.Gamepad.sThumbRY) / -SHRT_MIN;
			}
		}
	}
	else {
		//�p�b�h���ڑ�����Ă��Ȃ��ꍇ�̓L�[�{�[�h�Ńp�b�h�̓��͂��G�~�����[�g����B
		//�ڑ�����Ă��Ȃ��ꍇ�̓L�[�{�[�h�̓��͂ŃG�~�����[�g����B
		if (m_state.bConnected) {
			//���ڑ��ɂȂ����B
			memset(&m_state, 0, sizeof(m_state));
			memset(m_trigger, 0, sizeof(m_trigger));
			memset(m_press, 0, sizeof(m_press));
		}
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;

		if (GetAsyncKeyState(VK_LEFT)) {
			m_rStickX = -1.0f;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			m_rStickX = 1.0f;
		}
		if (GetAsyncKeyState(VK_UP)) {
			m_rStickY = 1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_rStickY = -1.0f;
		}
		//�X�e�B�b�N�̓��͗ʂ𐳋K���B
		float t = fabsf(m_rStickX) + fabsf(m_rStickY);
		if (t > 0.0f) {
			m_rStickX /= t;
			m_rStickY /= t;
		}

		if (GetAsyncKeyState('A')) {
			m_lStickX = -1.0f;
		}
		else if (GetAsyncKeyState('D')) {
			m_lStickX = 1.0f;
		}
		if (GetAsyncKeyState('W')) {
			m_lStickY = 1.0f;
		}
		else if (GetAsyncKeyState('S')) {
			m_lStickY = -1.0f;
		}
		//�X�e�B�b�N�̓��͗ʂ𐳋K���B
		t = fabsf(m_lStickX) + fabsf(m_lStickY);
		if (t > 0.0f) {
			m_lStickX /= t;
			m_lStickY /= t;
		}

		for (const VirtualPadToKeyboard& vPadToKeyboard : vPadToKeyboardTable) {
			if (GetAsyncKeyState(vPadToKeyboard.keyCoord)) {
				m_trigger[vPadToKeyboard.vButton] = 1 ^ m_press[vPadToKeyboard.vButton];
				m_press[vPadToKeyboard.vButton] = 1;
			}
			else {
				m_trigger[vPadToKeyboard.vButton] = 0;
				m_press[vPadToKeyboard.vButton] = 0;
			}
		}
	}
}