#pragma once
#include "IGameObject.h"
#include "Sound.h"

/*!
 * @brief	�Q�[���N���X�B
 */
class Game:public IGameObject
{
public:
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
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
	void NextStage()
	{
		m_isNext = true;
	}
	//�N���A
	void ClearStage()
	{
		m_isClear = true;
	}

	//�C���X�^���X�̐���
	static void Game::Create()
	{
		if (!m_game)
		{
			m_game = new Game;
		}

	}

	//�C���X�^���X�̎擾
	static Game& GetInstance()
	{
		return *m_game;
	}

	//�C���X�^���X�̏���
	static  void Game::Destroy()
	{
		delete m_game;
		m_game = nullptr;
	}
private:
	
	//�R���X�g���N�^
	Game();
	static Game* m_game;//�C���X�^���X
private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = Run;				//�t�F�[�h�̏��
	Sound*				m_bgmSound=nullptr;			//�T�E���h
	const float			m_killZ = -30.0f;			//�v���C���[�����ʍ���
	bool				m_isNext = false;			//���̃X�e�[�W��
	bool				m_isNextTo = false;			//���̃X�e�[�W��
	bool				m_isClear = false;			//�N���A
	bool				m_isEnd = false;			//�Q�[���I�[�o�[
};