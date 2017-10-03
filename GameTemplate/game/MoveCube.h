#pragma once
class MoveCube
{
public:
	//�R���X�g���N�^
	MoveCube(int Dir,D3DXVECTOR3 limitpos);
	//�f�X�g���N�^
	~MoveCube();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�i�s����
	enum MOVEDIR
	{
		FORWARD,
		LEFT,
		RIGHT,
		BACK,
		DOWN,
		UP
	};
private:
	bool				Downflg = false;		//���������n�߂�t���O
	int					MoveDir = FORWARD;		//�i�ޕ���
	D3DXVECTOR3			Limitpos;				//�ړ�����l
	D3DXVECTOR3			Spos;					//�������W
	SkinModel			model;					//�X�L�����f��
	SkinModelData		modelData;				//�X�L�����f���f�[�^
	D3DXVECTOR3			position;				//���W
	D3DXQUATERNION		Rotation;				//��]
	Light				light;					//���C�g
	MeshCollider		meshCollider;			//���b�V���R���C�_�[
	RigidBody			rigidBody;				//���́B
	RigidBodyInfo		rbInfo;					//���̏��
	CharacterController	characterController;	//�L�����N�^�[�R���g���[���[
};

