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
	characterController.SetGravity(m_Gravity);

	animation.SetAnimationLoopFlag(Jump, false);
	animation.SetAnimationLoopFlag(Damage, false);
	animation.SetAnimationLoopFlag(Dead, false);

	animation.PlayAnimation(Stand, 0.3f);
	animation.SetAnimationEndTime(Dash, 0.8f);
	animation.SetAnimationEndTime(Jump, 2.2f);
	animation.SetAnimationEndTime(Damage, 0.8f);
	animation.SetAnimationEndTime(Dead, 0.8f);


	scale *= 0.01f;
	
	//HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
	//	"Assets/model/utc_spec.tga",
	//	&specularMap);
	//
	//if (specularMap != NULL)
	//{
	//	skinModel.SetSpecularMap(specularMap);
	//}
}

void Player::Update()
{
	switch (m_State)
	{
	case Dead:
		pad.Update();
		Setangle();
		move();
		AnimationSet();
		break;
	default:
		pad.Update();
		BulletHit();
		Setangle();
		move();
		AnimationSet();
		//Key();

		skinModel.UpdateWorldMatrix(characterController.GetPosition(), rotation, scale);
		break;
	}
}

void Player::move()
{
	if (MoveStop)
	{
		Ismove = false;
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
	//状態遷移？
	//ループフラグを切れていないからまだ変
	//if(!animation.IsPlay()){}これが使えない
	switch (m_State)
	{
	case Stand://待機
		if (workState != Stand){animation.PlayAnimation(Stand, 0.3f);}
		workState = m_State;//連続再生させないためのステート
		if (IsDead&&game->GetHp() <= 0) { m_State = Dead; }
		else if (IsDamage) { m_State = Damage; }
		else if (Isjump) { m_State = Jump; }
		else if (Ismove) { m_State = Dash; }
		else{ m_State = Stand;}
		//アニメーションの更新
		animation.Update(1.0f / 60.0f);
		break;
	case Dash://歩行
		if (workState != Dash){animation.PlayAnimation(Dash, 0.5f);}
		workState = m_State;
		if (IsDead&&game->GetHp() <= 0) { m_State = Dead; }
		else if (IsDamage) { m_State = Damage; }
		else if (Isjump) { m_State = Jump; }
		else if (Ismove) { m_State = Dash; }
		else { m_State = Stand; }
		//アニメーションの更新
		animation.Update(1.0f / 60.0f);
		break;
	case Jump://ジャンプ
		if (workState != Jump){animation.PlayAnimation(Jump, 0.5f);}
		workState = m_State;
		if (IsDead&&game->GetHp() <= 0){ m_State = Dead; }
		else if (IsDamage) { m_State = Damage; }
		else if (Isjump) { m_State = Jump; }
		else if (Ismove) { m_State = Dash; }
		else { m_State = Stand; }
		Isjump = false;
		//アニメーションの更新
		animation.Update(1.0f / 60.0f);
		break;
	case Damage://ダメージ
		if (workState != Damage){animation.PlayAnimation(Damage, 0.5f);}
		workState = m_State;
		if (IsDead&&game->GetHp() <= 0) { m_State = Dead; }
		else if (IsDamage) { m_State = Damage; }
		else if (Isjump) { m_State = Jump; }
		else if (Ismove) { m_State = Dash; }
		else { m_State = Stand; }
		//if (!animation.IsPlay())
		//{
			IsDamage = false;
		//}
		//アニメーションの更新
		animation.Update(1.0f / 60.0f);
		break;
	case Dead://死亡
		if (workState != Dead){animation.PlayAnimation(Dead, 0.5f);}
		workState = m_State;
		if (IsDead&&game->GetHp() <= 0){ m_State = Dead; }
		else if (IsDamage) { m_State = Damage; }
		else if (Isjump) { m_State = Jump; }
		else if (Ismove) { m_State = Dash; }
		else { m_State = Stand; }
		//if (!animation.IsPlay())
		//{
			IsDead = false;
		//}
		//アニメーションの更新
		animation.Update(1.0f / 60.0f);
		break;
	default:
		break;
	}
	

}

void Player::Setangle()
{
	D3DXVECTOR3 Mpos = position;

	moveSpeed = characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	D3DXVECTOR3 LocalDir;
	LocalDir.y = 0.0f;
	LocalDir.x = pad.GetLStickXF();
	LocalDir.z = pad.GetLStickYF();
	D3DXMATRIX m_inv;
	D3DXMatrixInverse(&m_inv, NULL, &game->GetCamera()->GetViewMatrix());

	D3DXVECTOR3 cameraZ;
	cameraZ.y = 0.0f;
	cameraZ.x = m_inv.m[2][0];
	cameraZ.z = m_inv.m[2][2];
	D3DXVec3Normalize(&cameraZ, &cameraZ);
	D3DXVECTOR3 cameraX;
	cameraX.x = m_inv.m[0][0];
	cameraX.z = m_inv.m[0][2];
	cameraX.y = 0.0f;
	D3DXVec3Normalize(&cameraX, &cameraX);

	D3DXVECTOR3 moveDir;
	
	moveDir.x = cameraX.x * LocalDir.x + cameraZ.x * LocalDir.z;
	moveDir.y = 0.0f;
	moveDir.z = cameraX.z *LocalDir.x + cameraZ.z * LocalDir.z;
	if (moveDir.x > 0.0f || moveDir.x<0.0f)
	{
		Addvector.x += 1.0f;
	}

	if (moveDir.z>0.0f || moveDir.z<0.0f)
	{
		Addvector.z += 1.0f;
	}

	if (Addvector.x>100.0f)
	{
		moveSpeed.x = 2.5f;
	}

	if (Addvector.z > 100.0f)
	{
		moveSpeed.z = 2.5f;
	}
	
	moveSpeed.x = moveDir.x*(6.0f+moveSpeed.x);
	moveSpeed.z = moveDir.z*(6.0f+moveSpeed.z);

	if (moveSpeed == D3DXVECTOR3{ 0.0f,0.0f,0.0f })
	{
		Addvector = { 0.0f,0.0f,0.0f };
	}
	//if (m_isGravity)
	//{
	//	if (Grotflg)
	//	{
	//		gAngle += 3.0f;

	//		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXToRadian(gAngle));
	//	}
	//	if (gAngle >= 180)
	//	{
	//		gAngle = 180.0f;
	//		//D3DXQuaternionNormalize(&rotation, &rotation);
	//		//Grotflg = false;
	//	}



	//}
	if ((moveDir.x*moveDir.x + moveDir.y*moveDir.y + moveDir.z*moveDir.z) > 0.0001f&&!MoveStop)
	{
		//回転させる　※
		float s;
		float halfAngle = atan2f(moveDir.x, moveDir.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.x = 0.0f * s;
		rotation.y = 1.0f * s;
		rotation.z = 0.0f * s;
	}

	if (pad.IsTrigger(pad.enButtonA) && characterController.IsOnGround() /*&& animation.GetNumAnimationSet() != Jump*/) {

		//ジャンプ
		moveSpeed.y = 8.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
		Isjump = true;
	}

	if (Jumpflg)
	{
		//ジャンプ
		moveSpeed.y = 11.0f;
		//ジャンプしたことをキャラクタコントローラーに通知
		characterController.Jump();
		Jumpflg = false;
		Isjump = true;
	}


	//キャラクタが動く速度を設定。
	characterController.SetMoveSpeed(moveSpeed);

	//if (MoveStop)
	//{
	//	characterController.SetPosition(Mpos);
	//}
	if (!MoveStop)
	{
		//キャラクタコントローラーを実行。
		characterController.Execute();
	}
}

void Player::Key()
{

	//float fMoveSpeed = 8.0f;
	//D3DXQUATERNION addRot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	//if (pad.IsPress(pad.enButtonLeft)||pad.GetLStickXF()<0.0) {//左方向

	//		moveSpeed.x = fMoveSpeed;
	//	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), -5.0f);
	//	rotation = addRot;
	//}
	//else if (pad.IsPress(pad.enButtonRight)||pad.GetLStickXF()>0.0) {//右方向

	//		moveSpeed.x = -fMoveSpeed;
	//	//moveSpeed.x = fMoveSpeed;
	//	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 5.0f);
	//	rotation = addRot;

	//	
	//}
	//else if (pad.IsPress(pad.enButtonUp)||pad.GetLStickYF()>0.0) {//上方向
	//		moveSpeed.x = -fMoveSpeed;

	//	//moveSpeed.z = -fMoveSpeed;
	//	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 60.0f);
	//	rotation = addRot;

	//}
	//else if (pad.IsPress(pad.enButtonDown)|| pad.GetLStickYF()<0.0) {//下方向

	//	//if (AddCount > 5.0f)
	//	//{
	//	//	moveSpeed.x = fMoveSpeed ;
	//	//}
	//	//else
	//	//{
	//		moveSpeed.x = 20.0f;
	//	//}
	//	moveSpeed.z = fMoveSpeed;
	//	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f);
	//	rotation = addRot;

	//}

	
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
	DamageTime--;
	
}

void Player::Draw(D3DXMATRIX viewM, D3DXMATRIX projM,bool Caster,bool Recive)
{
	if (DamageTime > 0 && (DamageTime % 2) == 0){return;}
	skinModel.Draw(/*&game->GetCamera()->GetViewMatrix()*/&viewM, &projM,Caster,Recive);

}
