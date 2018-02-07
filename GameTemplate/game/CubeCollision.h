#pragma once
class CubeCollision
{
public:

	//�f�X�g���N�^
	~CubeCollision();
	//���Ƌ��̓����蔻��
	//p1	��ڂ̋��̍��W
	//p2	��ڂ̋��̍��W
	//r1	��ڂ̋��̔��a(�傫��)
	//r2	��ڂ̋��̔��a(�傫��)
	bool Cube(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float r1, float r2);

	//�C���X�^���X�̐���
	static void CubeCollision::Create()
	{
		if (!m_cube)
		{
			m_cube = new CubeCollision;
		}

	}

	//�C���X�^���X�̏���
	static  void CubeCollision::Destroy()
	{
		delete m_cube;
		m_cube = nullptr;
	}
	//�C���X�^���X�̎擾
	static CubeCollision& GetInstance()
	{
		return *m_cube;
	}
private:
	//�R���X�g���N�^
	CubeCollision();
	static CubeCollision* m_cube;
};