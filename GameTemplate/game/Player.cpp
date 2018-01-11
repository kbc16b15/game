#include "stdafx.h"
#include "Player.h"
#include "MoveCube.h"
#include "Sound.h"

Player::Player()
{
}

Player::~Player()
{
	m_characterController.RemoveRigidBoby();
	m_skinModelData.Release();
	/*if (m_JumpSound != nullptr)
	{
		delete m_JumpSound;
		m_JumpSound = nullptr;
	}*/
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}
}

void Player::Start(){

	m_scale *= 0.01f;
	//ライトのセット
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_skinModelData.LoadModelData("Assets/modelData/Unity2.X", &m_animation);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&m_light);

	//キャラクタコントローラを初期化。
	m_characterController.Init(0.3f, 0.5f, m_position);
	m_characterController.SetGravity(m_Gravity);

	//アニメーションループフラグのセット
	m_animation.SetAnimationLoopFlag(Jump, false);
	m_animation.SetAnimationLoopFlag(Damage, false);
	m_animation.SetAnimationLoopFlag(Dead, false);

	//アニメーションエンドタイムのセット
	m_animation.PlayAnimation(Stand, 0.3f);
	m_animation.SetAnimationEndTime(Dash, 0.8f);
	m_animation.SetAnimationEndTime(Jump, 1.5f);
	m_animation.SetAnimationEndTime(Damage, 0.2f);
	m_animation.SetAnimationEndTime(Dead, 3.0f);

	/*D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&specularMap);
	
	if (specularMap != NULL)
	{
		skinModel.SetSpecularMap(specularMap);
	}*/

	//m_skinModel.SetSpecularlight(true);

	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_nomal.tga",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_skinModel.SetnormalMap(m_normalMap);
	}
}

void Player::Update()
{
	if (m_deathflg)return;//死んでいたらリターン

	//if (GetAsyncKeyState('Q')) {
	//	//法線マップのオフ
	//	m_skinModel.SetnormalMap(NULL);
	//}
	//if (GetAsyncKeyState('E')) {
	//	m_skinModel.SetnormalMap(m_normalMap);
	//}

	
	AnimationSet();
	m_pad.Update();
	BulletHit();
	Setangle();
	move();

	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);

}

void Player::move()
{
	//移動しているがどうかのフラグのセット
	if (m_moveStop)
	{
		m_ismove = false;
	}
	else if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f)
	{
		m_ismove = true;
	}
	else
	{
		m_ismove = false;
	}

}

void Player::AnimationSet()
{
	//状態遷移？
	switch (m_state)
	{
	case Stand://待機
		if (m_workState != Stand){m_animation.PlayAnimation(Stand, 0.3f);}
		m_workState = m_state;//連続再生させないためのステート
		if (m_isDead&&g_game->GetHp() <= 0) { m_state = Dead; }
		else if (m_isDamage) { m_state = Damage; }
		else if (m_isjump) { m_state = Jump; }
		else if (m_ismove) { m_state = Dash; }
		else{ m_state = Stand;}
		break;
	case Dash://歩行
		if (m_workState != Dash){m_animation.PlayAnimation(Dash, 0.5f);}
		m_workState = m_state;
		if (m_isDead&&g_game->GetHp() <= 0) { m_state = Dead; }
		else if (m_isDamage) { m_state = Damage; }
		else if (m_isjump) { m_state = Jump; }
		else if (m_ismove) { m_state = Dash; }
		else { m_state = Stand; }
		break;
	case Jump://ジャンプ
		if (m_workState != Jump){m_animation.PlayAnimation(Jump, 0.5f);}
		m_workState = m_state;
		if (m_isDead&&g_game->GetHp() <= 0){ m_state = Dead; }
		else if (m_isDamage) { m_state = Damage; }
		else if (m_isjump) { m_state = Jump; }
		else if (m_ismove) { m_state = Dash; }
		else { m_state = Stand; }
		if (!m_animation.IsPlay()|| m_characterController.IsOnGround())
		{
			m_isjump = false;
			//m_state = Stand;
		}
		break;
	case Damage://ダメージ
		if (m_workState != Damage){m_animation.PlayAnimation(Damage, 0.5f);}
		m_workState = m_state;
		if (m_isDead&&g_game->GetHp() <= 0) { m_state = Dead; }
		else if (m_isDamage) { m_state = Damage; }
		else if (m_isjump) { m_state = Jump; }
		else if (m_ismove) { m_state = Dash; }
		else { m_state = Stand; }

		if (!m_animation.IsPlay()){m_isDamage = false;}
		break;
	case Dead://死亡
		if (m_workState != Dead){m_animation.PlayAnimation(Dead, 0.5f);}
		m_workState = m_state;

		if (!m_animation.IsPlay()){m_deathflg = true;}
		break;
	default:
		break;
	}
	//アニメーションの更新
	m_animation.Update(1.0f / 60.0f);

}

void Player::Setangle()
{
	if (m_isDead)return;
	//D3DXVECTOR3 Mpos = position;

	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	D3DXVECTOR3 LocalDir;
	LocalDir.y = 0.0f;
	LocalDir.x = m_pad.GetLStickXF();
	LocalDir.z = m_pad.GetLStickYF();
	D3DXMATRIX m_inv;
	D3DXMatrixInverse(&m_inv, NULL, &g_game->GetCamera()->GetViewMatrix());//逆行列を計算

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

	if (!m_maxSflg)
	{
		m_dir.x += moveDir.x;
		m_dir.z += moveDir.z;
	}
	if (m_pad.GetLStickXF() == 0.0f&&m_pad.GetLStickYF() == 0.0f)
	{
		//移動していないときに減速させる処理(摩擦？)
		
		if (m_dir.x > 0.0f)
		{
			m_dir.x += -0.2f;
		}
		if (m_dir.x < 0.0f)
		{
			m_dir.x += 0.2f;
		}
		if (m_dir.z > 0.0f)
		{
			m_dir.z += -0.2f;
		}
		if (m_dir.z < 0.0f)
		{
			m_dir.z += 0.2f;
		}

		//移動していないときに止める処理
		if (m_dir.x > -1.0f&&m_dir.x < 1.0f&&m_dir.z < 1.0f&&m_dir.z > -1.0f/*len<1.0f*/)
		{
			m_dir = { 0.0f,0.0f,0.0f };
		}
	}
	//最大移動速度の保存
	m_maxSflg = false;
	if (m_dir.x > 5.0f)
	{
		m_dir.x = 5.0f;
		m_maxSflg = true;
	}
	else if (m_dir.x < -5.0f)
	{
		m_dir.x = -5.0f;
		m_maxSflg = true;
	}
	if (m_dir.z > 5.0f)
	{
		m_dir.z = 5.0f;
		m_maxSflg = true;
	}
	else if (m_dir.z < -5.0f)
	{
		m_dir.z = -5.0f;
		m_maxSflg = true;
	}

	m_moveSpeed.x = m_dir.x;
	m_moveSpeed.z = m_dir.z;

	/*if (moveSpeed == D3DXVECTOR3{ 0.0f,0.0f,0.0f })
	{
		Addvector = { 0.0f,0.0f,0.0f };
	}*/
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
	if ((moveDir.x*moveDir.x + moveDir.y*moveDir.y + moveDir.z*moveDir.z) > 0.0001f&&!m_moveStop)
	{
		//回転させる　※
		float s;
		float halfAngle = atan2f(moveDir.x, moveDir.z) * 0.5f;
		s = sin(halfAngle);
		m_rotation.w = cos(halfAngle);
		m_rotation.x = 0.0f * s;
		m_rotation.y = 1.0f * s;
		m_rotation.z = 0.0f * s;
	}

	if (m_pad.IsTrigger(m_pad.enButtonA) && m_characterController.IsOnGround()) {

			Sound*	m_JumpSound = new Sound();
			m_JumpSound->Init("Assets/Sound/jump06.wav");
			m_JumpSound->SetVolume(0.4f);
			m_JumpSound->Play(false);
		//ジャンプ
		m_moveSpeed.y = 8.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		m_characterController.Jump();
		m_isjump = true;
	}
	/*if (!m_JumpSound->IsPlaying()&&m_JumpSound!=nullptr)
	{
		delete m_JumpSound;
		m_JumpSound = nullptr;
	}*/
	if (m_jumpflg)
	{
		//ジャンプ
		m_moveSpeed.y = 11.0f;
		//ジャンプしたことをキャラクタコントローラーに通知
		m_characterController.Jump();
		m_jumpflg = false;
		m_isjump = true;
	}
	

	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_moveSpeed);

		//キャラクタコントローラーを実行
		m_characterController.Execute();
}

void Player::BulletHit()
{
	//std::list<Bullet*> bulletstl = game->GetBullets();
	//for (auto bullet : bulletstl)
	//{

	/*std::vector<trackingEnemy*> Tenestl = game->GetTEnemy();
	for (auto Tene : Tenestl)
	{
		D3DXVECTOR3 Tvec;
		D3DXVec3Subtract(&Tvec, &Tene->Getpos(), &characterController.GetPosition());
		float Tlen=D3DXVec3Length(&Tvec);
		if (Tlen < 3.0f)
		{
			Tene->Settraking();
		}
	}*/
	//プレイヤーとバレット前方の当たり判定
	if (m_damageflg&&m_damageTime<0)
	{
		if (g_game->GetHp() <= 0 && m_characterController.IsOnGround())
		{
			m_isDead = true;
		}
		else
		{
			//m_state = Damage;
			m_damageflg = false;
			m_isDamage = true;
			g_game->Damage(1);
			m_damageTime = 200;
		}
		m_damageflg = false;
	}
	m_damageTime--;
}

void Player::Draw(D3DXMATRIX* viewM, D3DXMATRIX* projM, bool shadowCaster,bool shadowRecive)
{
	m_skinModel.SetCasterflg(shadowCaster);
	m_skinModel.SetReciveflg(shadowRecive);
	if (!shadowCaster)
	{
		if (m_damageTime > 0 && (m_damageTime % 2) == 0) { return; }
	}
	m_skinModel.Draw(viewM, projM);
	m_skinModel.SetCasterflg(false);
	m_skinModel.SetReciveflg(false);
}
