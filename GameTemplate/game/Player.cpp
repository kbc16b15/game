#include "stdafx.h"
#include "game.h"
#include "Player.h"


Player::Player()
{
	pad = new Pad();
}


Player::~Player()
{
	delete pad;
}

void Player::Start(){
	
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	animation.PlayAnimation(0);
	//キャラクタコントローラを初期化。

	characterController.Init(0.3f, 0.2f, position);
	characterController.SetGravity(-20.0f);	//重力強め。

	animation.PlayAnimation(Stand, 0.3f);
	//animation.SetAnimationLoopFlag(Jump, false);
	animation.SetAnimationEndTime(Dash,0.8f);
	//animation.SetAnimationEndTime(Jump, 1.0f);
}
void Player::Update()
{
	pad->Update();
	Key();

	BulletHit();

	//キャラクタが動く速度を設定。
	characterController.SetMoveSpeed(moveSpeed);

	//キャラクタコントローラーを実行。
	characterController.Execute();
	move();
	AnimationSet();

	skinModel.UpdateWorldMatrix(characterController.GetPosition(), rotation, scale);

	
}

void Player::move()
{

	//D3DXVECTOR3 move = characterController.GetMoveSpeed();
	//move.x = -Pad(0).GetLStickXF() * 5.0f;
	//move.z = -Pad(0).GetLStickYF() * 5.0f;

	//D3DXVECTOR3 old_move = move;

	//D3DXVECTOR3 moveXZ = move;						//方向ベクトル
	//moveXZ.y = 0.0f;


	if (GetAsyncKeyState('J') && animation.GetNumAnimationSet() != Jump)
	{
		Isjump = true;
	}
	else if (moveSpeed.x != 0.0f || moveSpeed.z != 0.0f)
	{
		Ismove = true;

	}
	else
	{
		Ismove = false;
	}

}

void Player::AnimationSet()
{

	//キャラの移動
	//ジャンプアニメーション再生
	if (Isjump)
	{
		animation.PlayAnimation(Jump,0.5f);
		
		Isjump = false;
		Testflg = true;

	}
	if (JumpTime > 0)
	{
		JumpTime--;
	}
	if (JumpTime <= 0)
	{
		JumpTime = 75;
		Isrun = true;
		Isjump = false;
	}

	if(!Isrun)
	{
		if (Ismove) {

			animation.PlayAnimation(Dash, 0.5f);
			Isrun = true;
		}
	}
	else if (!Ismove&&animation.GetNumAnimationSet() != Jump)
	{
		Isrun = false;
		animation.PlayAnimation(Stand, 0.3f);
	}

	if (!animation.IsPlay())
	{
		Isrun = false;
		animation.PlayAnimation(Stand,0.3f);
	}


	if (characterController.IsOnGround() && Testflg)
	{
		//animation.PlayAnimation(Stand, 0.3f);
		Isrun = false;
		Testflg = false;
	}

	//if (!IsStand) {

	//	//ジャンプ時
	//	if (Isjump) {
	//		IsAnimend = false;
	//		animation.PlayAnimation(Jump, 0.3f);
	//		IsStand = true;
	//	}
	//	if (!Isrun) {
	//		if (Ismove) {
	//			IsAnimend = false;
	//			animation.PlayAnimation(Dash, 0.5f);
	//			//Isrun = true;

	//			IsStand = true;
	//		}
	//	}
	//}
	//else if (!Isjump&&!Ismove)
	//{
	//	IsStand = false;
	//}
	//if (!animation.IsPlay()|| characterController.IsOnGround() && Isjump)
	//{
	//	animation.PlayAnimation(Stand, 0.3f);

	//	//animation.SetAnimationLoopFlag(Stand_anim, true);
	//	//animation.SetAnimationSpeedRate(0.3);
	//	//IsAttack = false;
	//	Isjump = false;
	//	Ismove = false;
	//	IsAnimend = true;
	//	
	//}


	//アニメーションの更新
	animation.Update(1.0f / 60.0f);
}

void Player::Key()
{
	//パッドの入力で動かす。
	moveSpeed = characterController.GetMoveSpeed();
	float fMoveSpeed = 8.0f;
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	D3DXQUATERNION addRot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_RIGHT) || pad->GetLStickXF()>0.0f&&pad->GetLStickYF()<0.0f) {
		fMoveSpeed = 4.0f;
		moveSpeed.x = -fMoveSpeed;
		moveSpeed.z = fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), -1.0f);
		rotation = addRot;
	}
	else if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_LEFT) || pad->GetLStickXF()<0.0f&&pad->GetLStickYF()<0.0f) {
		fMoveSpeed = 4.0f;
		moveSpeed.x = fMoveSpeed;
		moveSpeed.z = fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f);
		rotation = addRot;
	}
	else if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_LEFT)|| pad->GetLStickXF()<0.0f&&pad->GetLStickYF()>0.0f) {
		fMoveSpeed = 4.0f;
		moveSpeed.x = fMoveSpeed;
		moveSpeed.z = -fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), -10.0f);
		rotation = addRot;
	}
	else if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_RIGHT)|| pad->GetLStickXF()>0.0f&&pad->GetLStickYF()>0.0f) {
		fMoveSpeed = 4.0f;
		moveSpeed.x = -fMoveSpeed;
		moveSpeed.z = -fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 10.0f);
		rotation = addRot;
	}
	else if (pad->GetLStickXF()<0.0f) {//左方向
		moveSpeed.x = fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), -5.0f);
		rotation = addRot;

	}
	else if (pad->GetLStickXF()>0.0f) {//右方向
		moveSpeed.x = -fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 5.0f);
		rotation = addRot;
	}
	else if (pad->GetLStickYF()>0.0f) {//上方向
		moveSpeed.z = -fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 60.0f);
		rotation = addRot;
	}
	else if (pad->GetLStickYF()<0.0f) {//下方向

		moveSpeed.z = fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f);
		rotation = addRot;
	}


	if (GetAsyncKeyState('J') &&!characterController.IsJump()) {
		//ジャンプ
		moveSpeed.y = 9.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
		//Isjump = true;

	}

	if (GetAsyncKeyState('I') && !characterController.IsJump()) {

		game->GetBullet()->Setpos({ 0.0f,0.0f,0.0f });
	}
}

void Player::BulletHit()
{
	std::vector<Bullet*> bulletstl = game->GetBullets();
	for (auto bullet : bulletstl)
	{
		//プレイヤーとバレット前方の当たり判定
		D3DXVECTOR3 toPos;
		D3DXVECTOR3 Bulletpos = bullet->Getpos();
		Bulletpos.x += 1.0f;
		D3DXVec3Subtract(&toPos, &Bulletpos, &characterController.GetPosition());

		float Attacklen = D3DXVec3Length(&toPos);
		if (Attacklen < 1.0f)
		{
			characterController.SetPosition({ 0.0f, 0.0f, 0.0f });
		}

		//プレイヤーとバレットの上の当たり判定
		Bulletpos = bullet->Getpos();
		Bulletpos.y += 1.0f;
		D3DXVec3Subtract(&toPos, &Bulletpos, &characterController.GetPosition());
		float Uplen = D3DXVec3Length(&toPos);

		if (Uplen < 1.0f)//エネミーを踏んでジャンプする
		{
			//ジャンプ
			moveSpeed.y = 12.0f;
			//ジャンプしたことをキャラクタコントローラーに通知。
			characterController.Jump();
			JumpTime = 80;
			D3DXVECTOR3 Addpos = { -10.0f,2.0f,0.0 };
			D3DXVec3Add(&Addpos, &Addpos, &bullet->Getpos());
			game->GetBullet()->Setpos(Addpos);
			Isjump = true;
		}

	}

	if (Jumpflg)
	{
		//ジャンプ
		moveSpeed.y = 12.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
		JumpTime = 80;
		Jumpflg = false;
		Isjump = true;
	}
}

void Player::Render()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());

}
