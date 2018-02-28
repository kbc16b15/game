#pragma once
#include "Sound.h"
#include "IScene.h"
class Silhouette;
/*!
 * @brief	�Q�[���N���X�B
 */
class Game:public IScene
{
public:
	//�R���X�g���N�^
	Game();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�N���֐��B
	 */
	void Init();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Draw();

	//�V���h�E�̈ʒu�ݒ�
	void SetShadow();

	//�t�F�[�h
	void SceneFade();

	//�Q�[���V�[���̊J��
	void GameRelease();
	
	//�Q�[���I���̃t���O�̎擾
	bool GetGameEnd()
	{
		return m_isEnd;
	}
	//���̃X�e�[�W��
	void StageNext()
	{
		m_isNext = true;
	}
	//�N���A
	void StageClear(bool isClear)
	{
		m_isClear = isClear;
	}
	//BGM�X�g�b�v
	void BgmStop()
	{
		if(m_bgmSound!=nullptr)
		m_bgmSound->Stop();
	}
	//�X�e�[�W�Z�b�g
	void SetStage(int No)
	{
		m_stageNo = No;
	}
private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	Silhouette*			m_silhouette = nullptr;
	EState				m_state = WaitFadeIn;		//�t�F�[�h�̏��
	Sound*				m_bgmSound=nullptr;			//�T�E���h
	const float			m_killZ = -10.0f;			//�v���C���[�����ʍ���
	bool				m_isNext = false;			//���̃X�e�[�W��
	bool				m_isNextTo = false;			//���̃X�e�[�W
	bool				m_isClear = false;			//�N���A
	bool				m_isEnd = false;			//�Q�[���I�[�o�[
	bool				m_isLoadEnd = false;
	int					m_stageNo=0;
};