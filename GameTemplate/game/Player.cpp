#include "stdafx.h"
#include "Player.h"
#include "PlayerHp.h"
#include "SceneManager.h"
#include "game.h"
#include "Bullet.h"
//#include "BulletWeapon.h"
#include "BulletManager.h"
//#include "GameObjectManager.h"
//#include "gameCamera.h"
//#include "BulletHud.h"
//#include "SpringCamera.h"
#include "EnemyManager.h"
#include "BossEnemy.h"

//Player *Player::player = NULL;
Player::Player()
{
	//m_JumpSound = new Sound();
	m_position = { 0.0f,0.0f,0.0f };		//座標
	m_scale = { 1.0f,1.0f,1.0f };			//拡大
	m_rotation = { 0.0f,0.0f,0.0f,1.0f };	//回転
	m_moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度
	m_dir = { 0.0f,0.0f,0.0f };				//かんせー
	//m_Addvector = { 0.0f,0.0f,0.0f };		//加算速度

}

Player::~Player()
{

	m_skinModelData.Release();
	m_characterController.RemoveRigidBoby();
	//法線マップ開放
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}

	//スペキュラマップ開放
	if (m_specularMap != NULL)
	{
		m_specularMap->Release();
	}
	if (m_beamSound != nullptr)
	{
		m_beamSound->Release();
		m_beamSound = nullptr;
	}
	if (m_jumpSound != nullptr)
	{
		m_jumpSound->Release();
		m_jumpSound = nullptr;
	}
}

void Player::Init(){

	//m_scale *= 0.01f;//unity
	//m_scale *= 0.2f;//spacestand
	m_scale *= 0.8f;//spacerun
	//Sound*	m_JumpSound = new Sound();//登録しておく？
	//m_JumpSound->Init("Assets/Sound/jump.wav");
	//m_JumpSound->SetVolume(0);
	//m_JumpSound->Play(false);
	m_beamSound = new Sound();
	m_jumpSound = new Sound();
	//ライトのセット
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, 0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));
	//ライトカラーのセット
	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	//スキンモデルのロード
	m_skinModelData.LoadModelData("Assets/modelData/Spaceanim.X",&m_animation);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&m_light);

	//キャラクタコントローラを初期化。
	m_characterController.Init(m_charaRadius,m_charaHeight,m_position);
	m_characterController.SetGravity(m_gravity);

	const float StandInterTime= 0.3f;
	m_animation.PlayAnimation(Stand, StandInterTime);
	//アニメーションループフラグのセット
	m_animation.SetAnimationLoopFlag(Jump, false);
	m_animation.SetAnimationLoopFlag(Damage, false);
	m_animation.SetAnimationLoopFlag(Dead, false);
	//アニメーションエンドタイムのセット

	//const float DashEndTime= 1.5f;
	//const float JumpEndTime= 5.5f;
	//const float DamageEndTime= 0.2f;
	//const float DeadEndTime= 3.0f;

	//m_animation.SetAnimationEndTime(Dash, DashEndTime);
	//m_animation.SetAnimationEndTime(Jump, JumpEndTime);
	//m_animation.SetAnimationEndTime(Damage, DamageEndTime);
	//m_animation.SetAnimationEndTime(Dead, DeadEndTime);

	m_skinModel.SetSpecularlight(true);

	//スペキュラマップ
	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/SpaceSpecularMap.png",
		&m_specularMap);
	if (m_specularMap != NULL)
	{
		m_skinModel.SetSpecularMap(m_specularMap);
	}
	//法線マップ
	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/SpaceNormalMap.png",
		&m_normalMap);
	

	if (m_normalMap != NULL)
	{
		m_skinModel.SetnormalMap(m_normalMap);
	}

}

void Player::Update()
{
	if (m_isDeathflg)return;//死んでいたらリターン
	//サウンド
	PlayerSound();
	//アニメーション
	AnimationSet();
	//ダメージ関係
	Hit();
	//移動
	this->move();
	Setangle();

	//バレット
	PlayerBullet();
	m_characterController.SetPosition(m_characterController.GetPosition());
	m_middlePosition = m_characterController.GetPosition();
	m_middlePosition.y += m_charaRadius;

	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);

}

void Player::move()
{
	//移動しているがどうかのフラグのセット
	/*if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f)
	{
		m_ismove = true;
	}
	else
	{
		m_ismove = false;
	}*/
	m_ismove = false;
	if (Pad::GetInstance().GetLStickXF()<0.0)
	{
		m_ismove = true;
	}
	if (Pad::GetInstance().GetLStickXF()>0.0)
	{
		m_ismove = true;
	}

	if (Pad::GetInstance().GetLStickYF()<0.0)
	{
		m_ismove = true;
	}
	if (Pad::GetInstance().GetLStickYF()>0.0)
	{
		m_ismove = true;
	}

	if (m_ismove)
	{
		m_isBulletflg = false;
		m_isPlayerBulletCamera = false;
		SetMove(false);
	}

}

void Player::AnimationSet()
{
	const float StandInterTime = 0.3f;
	const float DashInterTime = 0.5f;
	const float JumpInterTime = 0.5f;
	const float DamageInterTime = 0.5f;
	const float DeadInterTime = 0.5f;
	const float BulletInterTime = 0.5f;
	//状態遷移？
	switch (m_state)
	{
	case PlayerState::Stand://待機
		
		if (m_workState != Stand) { m_animation.PlayAnimation(Stand, StandInterTime);}
		m_workState = m_state;//連続再生させないためのステート
		/*if (m_isDead&&SceneManager::GetGame().GetPlayerHp().GetPlayerHpNum() <= 0) { m_state = Dead; }
		else if (m_isDamage) { m_state = Damage; }
		else if (m_isjump) { m_state = Jump; }
		else if (m_ismove) { m_state = Dash; }
		else if (m_isBulletflg) { m_state = Bullets; }
		else{ m_state = Stand;}*/
		AnimaionState();
		break;
	case PlayerState::Dash://歩行
		if (m_workState != Dash) { m_animation.PlayAnimation(Dash, DashInterTime); }
		m_workState = m_state;
		AnimaionState();
		break;
	case PlayerState::Jump://ジャンプ
		if (m_workState != Jump){m_animation.PlayAnimation(Jump, JumpInterTime);}
		m_workState = m_state;
		AnimaionState();
		if (!m_animation.IsPlay()|| m_characterController.IsOnGround())
		{
			m_isjump = false;
		}
		break;
	case PlayerState::Damage://ダメージ
		if (m_workState != Damage){m_animation.PlayAnimation(Damage, DamageInterTime);}
		m_workState = m_state;
		AnimaionState();

		if (!m_animation.IsPlay()){m_isDamage = false;}
		break;
	case PlayerState::Dead://死亡
		if (m_workState != Dead){m_animation.PlayAnimation(Dead, DeadInterTime);}
		m_workState = m_state;

		if (!m_animation.IsPlay()){m_isDeathflg = true;}
		break;
	case PlayerState::Bullets://銃構え
		if (m_workState != Bullets) { m_animation.PlayAnimation(Bullets, BulletInterTime); }
		m_workState = m_state;
		AnimaionState();
		break;
	default:
		break;
	}
	//アニメーションの更新
	m_animation.Update(1.0f / 60.0f);

}

void Player::AnimaionState()
{
	if (m_isDead&&SceneManager::GetGame().GetPlayerHp().GetPlayerHpNum() <= 0) { m_state = Dead; }
	else if (m_isDamage) { m_state = Damage; }
	else if (m_isjump) { m_state = Jump; }
	else if (m_ismove) { m_state = Dash; }
	else if (m_isBulletflg) { m_state = Bullets; }
	else { m_state = Stand; }
}

void Player::Setangle()
{
	//if (m_isDeathflg)return;

	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	D3DXVECTOR3 LocalDir;
	LocalDir.y = 0.0f;
	LocalDir.x = Pad::GetInstance().GetLStickXF();
	LocalDir.z = Pad::GetInstance().GetLStickYF();
	D3DXMATRIX m_inv;
	D3DXMatrixInverse(&m_inv, NULL, &Camera::GetInstance().GetViewMatrix());//逆行列を計算

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

	/*if (!m_isMax)
	{
		m_dir.x += moveDir.x;
		m_dir.z += moveDir.z;
	}*/
	
	//SetSubmove();//慣性
	

	m_moveSpeed.x = moveDir.x*6.0f;
	m_moveSpeed.z = moveDir.z*6.0f;
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

	//if (m_isGaraviey)//X軸キャラ反転
	//{
	//	float s;
	//	float halfAngle = /*atan2f(moveDir.x, moveDir.z)*/atan(10.0f);
	//	s = sin(halfAngle);
	//	m_rotation.w = cos(halfAngle);
	//	m_rotation.x = 1.0f * s;
	//	m_rotation.y = 0.0f * s;
	//	m_rotation.z = 0.0f * s;
	//}


	if ((moveDir.x*moveDir.x + moveDir.y*moveDir.y + moveDir.z*moveDir.z) > 0.0001f&&!m_isMoveStop&&!m_isDead)
	{
		//回転させる　※Y軸回り?
		float s;
		float halfAngle = atan2f(moveDir.x, moveDir.z) * 0.5f;
		s = sin(halfAngle);
		m_rotation.w = cos(halfAngle);
		m_rotation.x = 0.0f * s;
		m_rotation.y = 1.0f * s;
		m_rotation.z = 0.0f * s;
	}
	
	Setjump();//ジャンプ
	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_moveSpeed);
	if (!m_isDead&&!m_isMoveStop)//死んだときに移動を停止させる
	{
		//キャラクタコントローラーを実行
		m_characterController.Execute();
	}
	else if (!m_characterController.IsOnGround())//地面で死ぬようにする
	{
		m_characterController.Execute();
	}
}

void Player::Setjump()
{
	const float			jumpHeight = 7.5f;	//ジャンプの高さ
	if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonA) && m_characterController.IsOnGround()&&!m_isMoveStop) {
		//ジャンプ
		m_moveSpeed.y = jumpHeight;
		//ジャンプしたことをキャラクタコントローラーに通知。
		m_characterController.Jump();
		m_isjump = true;

		///*Sound**/	m_jumpSound = new Sound();
		m_jumpSound->Init("Assets/Sound/jump.wav");
		m_jumpSound->SetVolume(0.4f);
		m_jumpSound->Play(false);
	}
}

void Player::SetSubmove()
{
	const float			m_maxSpeed = 5.0f;		//最大移動速度の保存
	const float			m_downSpeed = 0.3f;		//移動していないときに減速させる処理(摩擦？)
	//if (Game::GetInstance().GetPad()->GetLStickXF() == 0.0f&&Game::GetInstance().GetPad()->GetLStickYF() == 0.0f){
		//移動していないときに減速させる処理(摩擦？)

		if (m_dir.x > 0.0f)
		{
			m_dir.x += -m_downSpeed;
		}
		if (m_dir.x < 0.0f)
		{
			m_dir.x += m_downSpeed;
		}
		if (m_dir.z > 0.0f)
		{
			m_dir.z += -m_downSpeed;
		}
		if (m_dir.z < 0.0f)
		{
			m_dir.z += m_downSpeed;
		}

		//移動していないときに止める処理
		if (m_dir.x > -1.0f&&m_dir.x < 1.0f&&m_dir.z < 1.0f&&m_dir.z > -1.0f/*len<1.0f*/)
		{
			m_dir = { 0.0f,0.0f,0.0f };
		}
	//}
	//最大移動速度の保存
	m_isMax = false;
	if (m_dir.x >m_maxSpeed)
	{
		m_dir.x = m_maxSpeed;
		m_isMax = true;
	}
	else if (m_dir.x < -m_maxSpeed)
	{
		m_dir.x = -m_maxSpeed;
		m_isMax = true;
	}
	if (m_dir.z >m_maxSpeed)
	{
		m_dir.z = m_maxSpeed;
		m_isMax = true;
	}
	else if (m_dir.z < -m_maxSpeed)
	{
		m_dir.z = -m_maxSpeed;
		m_isMax = true;
	}

	m_moveSpeed.x = m_dir.x;
	m_moveSpeed.z = m_dir.z;

}

void Player::Hit()
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

	//HPがなくなったら死亡
	if (SceneManager::GetGame().GetPlayerHp().GetPlayerHpNum() <= 0)
	{
		m_isDead = true;
	}

	//ダメージ判定
	if (m_isDamageflg&&m_damageTime<0)
	{
		if(m_isDead == false)
		{

			m_isDamageflg = false;
			m_isDamage = true;
			SceneManager::GetGame().GetPlayerHp().PlayerDamage(1);
			m_damageTime = m_damageMaxTime;
			//構え解除
			m_isBulletflg = false;
			m_isPlayerBulletCamera = false;
			SetMove(false);
		}
		m_isDamageflg = false;
	}
	m_damageTime--;
}

void Player::PlayerBullet()
{
	D3DXVECTOR3 BossPos = {0.0f,0.0f,0.0f};
	D3DXVECTOR3 EnemyPos = { 0.0f,0.0f,0.0f };
	const float Bulletlenge = 15.0f;
	bool isBossExist = false;
	float Bosslen;
	std::list<trackingEnemy*> enestl;
	

	if (&SceneManager::GetGame().GetBoss() != NULL){
		isBossExist = true;
	}

	m_bulletIntervalTime--;
	const float bulletSpeed = 0.2f;
	if (m_bulletIntervalTime < 0 && Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonRB1)  &&m_isBulletflg){
		if (!isBossExist) {
			std::list<trackingEnemy*> enestl = SceneManager::GetGame().GetEnemyManager().GetEnemy();

			for (auto ene : enestl)
			{
				if (ene == NULL || !ene->GetActive()) { continue; }
				EnemyPos = ene->GetPos() - m_middlePosition;
				float Enemylen = D3DXVec3Length(&EnemyPos);
				if (Enemylen < Bulletlenge) {

					//Bullet* bullet = BulletManager::GetInstance().CreateBullet(bullet->PLAYER);
					Bullet* bullet = new Bullet;
					SceneManager::GetGame().GetBulletManager().AddBullets(bullet);
					bullet->Start(ene->GetPos()/*SpringCamera::GetInstance().GetTarTarget()*/, m_middlePosition, bulletSpeed, bullet->PLAYER);
					m_bulletIntervalTime = m_maxBulletTime;

					//*Sound**/ m_beamSound = new Sound();
					m_beamSound->Init("Assets/Sound/beamgun.wav");
					m_beamSound->SetVolume(m_beamVolume);
					m_beamSound->Play(false);
					break;
				}
			}
			
		}
		else
		{
			BossPos = SceneManager::GetGame().GetBoss().Getpos();
			BossPos = m_middlePosition - BossPos;
			Bosslen = D3DXVec3Length(&BossPos);

			if (Bosslen < Bulletlenge) {

				Bullet* bullet = new Bullet;
				SceneManager::GetGame().GetBulletManager().AddBullets(bullet);
				bullet->Start(SceneManager::GetGame().GetBoss().Getpos()/*SpringCamera::GetInstance().GetTarTarget()*/, m_middlePosition, bulletSpeed, bullet->PLAYER);
				m_bulletIntervalTime = m_maxBulletTime;

				//*Sound**/ m_beamSound = new Sound();
				m_beamSound->Init("Assets/Sound/beamgun.wav");
				m_beamSound->SetVolume(m_beamVolume);
				m_beamSound->Play(false);
			}
		}
	}

	if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonLB1))
	{
		if (!m_isBulletflg)
		{
		
			SetMove(true);
			//BulletHud::GetInstance().SetBullet(true);
			//m_cameraPos = Camera::GetInstance().GetEyePt();
			//m_cameraTar = Camera::GetInstance().GetLookatPt();
			m_isBulletflg = true;
		}
		else {
			m_isBulletflg = false;
			SetMove(false);
			//SpringCamera::GetInstance().SetTarPosition(m_cameraPos);
			//SpringCamera::GetInstance().SetTarTarget(m_cameraTar);
		}

	}
}

void Player::ShadowDraw(D3DXMATRIX* viewM, D3DXMATRIX* projM, bool shadowCaster,bool shadowRecive)
{
	if (m_isDeathflg)return;//死んでいたらリターン
	//シャドウをセット
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

void Player::Draw()
{
	ShadowDraw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix(),false,false);
}

void Player::PlayerSound()
{
	if (m_jumpSound != nullptr) {
		if (m_jumpSound->IsPlaying())
			m_jumpSound->Update();
	}
	if (m_beamSound != nullptr) {
		if (m_beamSound->IsPlaying())
			m_beamSound->Update();
	}
}
