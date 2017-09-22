#include "stdafx.h"
#include "Player.h"
#include "CubeCollision.h"


Player::Player()
{
}

Player::~Player()
{
	//delete skinModelData;
	characterController.RemoveRigidBoby();
	skinModelData.Release();
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
	skinModelData.LoadModelData("Assets/modelData/Unity2.X", &animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	animation.PlayAnimation(0);
	//キャラクタコントローラを初期化。

	characterController.Init(0.3f, 0.2f, position);
	characterController.SetGravity(-15.0f);

	animation.PlayAnimation(Stand, 0.3f);
	//animation.SetAnimationLoopFlag(Jump, false);
	animation.SetAnimationEndTime(Dash,0.8f);
	//animation.SetAnimationEndTime(Jump, 0.8f);
	//animation.SetAnimationEndTime(Damage,0.8f);
	//animation.SetAnimationEndTime(Dead, 0.8f);
	scale *= 0.01f;
	
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/model/utc_spec.tga",
		&specularMap);
	
	if (specularMap != NULL)
	{
		skinModel.SetSpecularMap(specularMap);
	}
	//characterController.GetRigidBody()->GetBody()->getCollisionShape()->setUserIndex(enCollisionAttr_User);

}

void Player::Update()
{
	
	Key();
	pad.Update();
	BulletHit();

	//キャラクタが動く速度を設定。
	characterController.SetMoveSpeed(moveSpeed);
	//キャラクタコントローラーを実行。
	characterController.Execute();
	AnimationSet();
	move();
	DamageTime--;

	//アニメーションの更新
	animation.Update(1.0f / 60.0f);
	skinModel.UpdateWorldMatrix(characterController.GetPosition(), rotation, scale);

}

void Player::move()
{

	//D3DXVECTOR3 move = characterController.GetMoveSpeed();
	//move.x = -pad->GetLStickXF() * 5.0f;
	//move.z = -pad->GetLStickYF() * 5.0f;

	//D3DXVECTOR3 old_move = move;

	//D3DXVECTOR3 moveXZ = move;						//方向ベクトル
	//moveXZ.y = 0.0f;

	//if (/*GetAsyncKeyState('J')*/pad->IsTrigger(pad->enButtonA) && animation.GetNumAnimationSet() != Jump)
	//{
	//	Isjump = true;
	//}
	//else
	//{
	//	Isjump = false;
	//}
	/*if (!characterController.IsOnGround())
	{
		moveSpeed = { 0.0f,0.0f,0.0f };
	}*/
	/*if (IsDamage || IsDead)
	{
		moveSpeed = { 0.0f,0.0f,0.0f };
	}*/

	if (moveSpeed.x != 0.0f || moveSpeed.z != 0.0f)
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
	if (IsDead&&game->GetHp() <= 0)
	{
		animation.PlayAnimation(Dead, 0.5f);
		IsDead = false;
		//standflg = true;
	}
	//キャラの移動
	if (!Isrun)
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
		animation.PlayAnimation(Stand, 0.3f);
	}

	if (IsDamage)
	{

		animation.PlayAnimation(Damage, 0.5f);
		IsDamage = false;
		//Isrun = true;
		IsStand = true;
	}
	//ジャンプアニメーション再生
	else if (Isjump)
	{
		animation.PlayAnimation(Jump,0.5f);
		Isjump = false;
		//Isrun = true;
		IsStand = true;

	}
	else if (characterController.IsOnGround() &&IsStand)
	{
		Isrun = false;
		IsStand = false;
		animation.PlayAnimation(Stand, 0.3f);
	}

	/*if (JumpTime > 0)
	{
		JumpTime--;
	}
	if (JumpTime <= 0)
	{
		JumpTime = 106;
		Isrun = true;
		Isjump = false;
	}*/
	
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

}

void Player::Key()
{
	moveSpeed = characterController.GetMoveSpeed();
	float fMoveSpeed = 8.0f;
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	D3DXQUATERNION addRot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	if (pad.IsPress(pad.enButtonLeft)|| GetAsyncKeyState('A')||pad.GetLStickXF()<0.0) {//左方向
		moveSpeed.x = fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), -5.0f);
		rotation = addRot;
	}
	else if (pad.IsPress(pad.enButtonRight)||GetAsyncKeyState('D')||pad.GetLStickXF()>0.0) {//右方向
		moveSpeed.x = -fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 5.0f);
		rotation = addRot;
		
	}
	else if (pad.IsPress(pad.enButtonUp)|| GetAsyncKeyState('W') || pad.GetLStickYF()>0.0) {//上方向
		moveSpeed.z = -fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 60.0f);
		rotation = addRot;
	}
	else if (pad.IsPress(pad.enButtonDown)|| GetAsyncKeyState('S') || pad.GetLStickYF()<0.0) {//下方向

		moveSpeed.z = fMoveSpeed;
		D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f);
		rotation = addRot;
	}


	if (pad.IsTrigger(pad.enButtonA) && characterController.IsOnGround() /*&& animation.GetNumAnimationSet() != Jump*/) {
		//ジャンプ
		moveSpeed.y = 9.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
		Isjump = true;
	}
}

void Player::BulletHit()
{
	//std::list<Bullet*> bulletstl = game->GetBullets();
	//for (auto bullet : bulletstl)
	//{
	//プレイヤーとバレット前方の当たり判定
	if (Damageflg&&DamageTime<0)
	{
		if (game->GetHp() <= 0)
		{
			IsDead = true;
		}
		else
		{
			IsDamage = true;
			game->Damage(1);
			DamageTime = 200;
		}
		Damageflg = false;
	}

	if (Jumpflg)
	{
		//ジャンプ
		moveSpeed.y = 12.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
		//JumpTime = 80;
		Jumpflg = false;
		Isjump = true;
	}
}

void Player::Draw()
{

	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());

}
