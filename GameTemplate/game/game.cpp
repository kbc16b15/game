/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include "Scene.h"

/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
	//srand((unsigned int)time(NULL));
	m_player = new Player;
	m_map = new Map;
	//m_renderTarget = new CRenderTarget;
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{

	delete m_player;
	delete m_map;
	//delete g_physicsWorld;
	//delete m_renderTarget;

	/*if (m_bgmSound != nullptr)
	{
		m_bgmSound->Release();
		m_bgmSound = nullptr;
	}*/

	//bulletの消去
	for (auto bullet : m_bullets) {
		delete bullet;
	}
	auto bulletIt = m_bullets.begin();
	while (bulletIt != m_bullets.end())
	{
		bulletIt = m_bullets.erase(bulletIt);
	}
	//enemの消去
	for (auto Enemynum : m_enem) {
		delete Enemynum;
	}
	auto enemyIt = m_enem.begin();
	while (enemyIt != m_enem.end())
	{
		enemyIt = m_enem.erase(enemyIt);
	}
	//Tenemの消去
	
	auto TenemyIt = m_tenem.begin();
	while (TenemyIt != m_tenem.end()) {

		TenemyIt = m_tenem.erase(TenemyIt);

	}
	for (auto TEnemynum : m_tenem)
	{
		if(TEnemynum!=nullptr)
		{
			delete TEnemynum;
			TEnemynum = nullptr;
		}
		
	}
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Init()
{
	g_fade->StartFadeIn();
	//カメラ初期化。
	m_gameCamera.Init();
	//プレイヤー初期化
	m_player->Start();
	//マップを初期化。
	m_map->Init();

	//m_bossEnemy->Init();
	//パーティクルの初期化
	/*SParticleEmitParameter param;
	param.texturePath = "star.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_particleEmitter.Init(param);*/
	//画像表示
	for (int i = 0;i <= m_hpMaxNum;i++)
	{
		m_hud[i].Initialize("Assets/Sprite/HP.png", m_hppos);
		m_hppos.x += m_hpMovePos;
	}
	//m_key.Initialize("Assets/Sprite/key.png", m_keypos);
	//m_rock.Setalfa(0.5f);
	//m_rock.Initialize("Assets/Sprite/Rock.jpg", m_rockpos);
	//スプライトの生成
	CreateSprite();

	
	/*Sound* m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/bgm.wav",false);
	m_bgmSound->SetVolume(0.5f);
	m_bgmSound->Play(true);*/


	/*m_renderTarget->Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A8R8G8B8,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0
	);*/
	//Player* pl = new Player();
	//GoMgr.AddGameObject(pl);
	//Enemy* en = new Enemy();
	//GoMgr.AddGameObject(en);
	//Map* map = new Map();
	//GoMgr.AddGameObject(map);
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	//m_bgmSound->Update();
	m_pad.Update();
	//かげ用のライトの位置の設定
	D3DXVECTOR3 toPos = m_player->Getpos();
	toPos.y += 7.0f;
	g_shadowmap->SetviewPosition(toPos);
	g_shadowmap->SetviewTarget(m_player->Getpos());

	D3DXVECTOR3 Ppos = m_player->Getpos();

	switch (GAME){
	case START:
		switch(m_state){
		case WaitFadeIn:
			if (!g_fade->isExecute())
			{
				m_state = Run;
			}
			break;
		case Run:
			if (m_player->PlayerDeath()|| Ppos.y < -9.0f|| m_nextflg) {
				g_fade->StartFadeOut();
				m_state = WaitFadeOut;
			}
			break;
		case WaitFadeOut:
			if (m_nextflg&& !g_fade->isExecute())
			{
				if (m_map->GetStage() == m_map->STAGE1)
				{
					g_scene->SceneChange(g_scene->CHANGEGAME2);

				}
				else if (m_map->GetStage() == m_map->STAGE2)
				{
					g_scene->SceneChange(g_scene->CHANGETITLE);
				}
			}
			else if (!g_fade->isExecute())
			{
				GameEnd();
			}
			break;
		}
		break;
	}
	

	//if (GetAsyncKeyState('L') || m_pad.IsTrigger(m_pad.enButtonLB1))
	//{
	//	Gunflg = true;
	//	camera.SetRockCamera(true);
	//	player.PlayerMoveSet(true);
	//}

	//if (GetAsyncKeyState('R') || m_pad.IsTrigger(m_pad.enButtonLB2))
	//{
	//	camera.SetRockCamera(false);
	//	Gunflg = false;
	//	player.PlayerMoveSet(false);
	//	rockpos = { 700.0f,250.0f };
	//}
	//rock.Initialize("Assets/Sprite/Rock.jpg", rockpos);

	//if (GetAsyncKeyState('Z') || m_pad.IsTrigger(m_pad.enButtonRB1)&&Gunflg)
	//{
	//	D3DXVECTOR3 Ppos = player.Getpos();
	//	D3DXVECTOR3 Cpos = camera.Getcamera().GetLookatPt();
	//	Bullet* bullet = new Bullet();
	//	bullet->Start(Ppos, { Cpos.x ,Cpos.y ,Cpos.z },0);
	//	game->AddBullets(bullet);
	//}

	for (auto enemy : m_enem)
	{
		enemy->Update();
	}
	for (auto Tenemy : m_tenem)
	{
		Tenemy->Update();
	}
	for (auto bullet : m_bullets)
	{
		bullet->Update();
	}
	//画像のアップデート
	for (int i = 0;i < m_hpNum;i++)
	{
		m_hud[i].Update();
	}

	auto enemyIt = m_enem.begin();
	while (enemyIt != m_enem.end()) {
		if ((*enemyIt)->GetDeathflg()){
			enemyIt = m_enem.erase(enemyIt);
		}
		else {
			enemyIt++;
		}
	}

	
	auto TenemyIt = m_tenem.begin();
	while (TenemyIt != m_tenem.end()) {
		if ((*TenemyIt)->GetDeathflg()) {
			
			TenemyIt = m_tenem.erase(TenemyIt);
		}
		else {
			TenemyIt++;
		}
	}

	for (auto TEnemynum : m_tenem)
	{
		if (TEnemynum->GetDeathflg())
		{
			delete TEnemynum;
			TEnemynum = nullptr;
		}
	}

	auto bulletIt = m_bullets.begin();
	while (bulletIt != m_bullets.end()) {
		if (!(*bulletIt)->GetBulletflg()) {
			bulletIt = m_bullets.erase(bulletIt);
		}
		else {
			bulletIt++;
		}
	}

	//m_key.Update();
	//m_rock.Update();
	//GoMgr.Update();
	m_gameCamera.Update();
	m_player->Update();
	m_map->Update();
	//m_bossEnemy->Update();
	//m_particleEmitter.Update();
	
	//if (GetAsyncKeyState('G'))
	//{
	//	//次のステージへ
	//	NextStage();
	//}

}
/*!
 * @brief	描画。
 */
void Game::Render()
{

	//GoMgr.Draw();
	m_map->Draw();
	//物体に遮蔽されているときにだけ描画する
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z値を書き込まないようにする
	m_player->Draw(&m_gameCamera.Getcamera().GetViewMatrix(), &m_gameCamera.Getcamera().GetProjectionMatrix(),true, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	m_player->Draw(&m_gameCamera.Getcamera().GetViewMatrix(), &m_gameCamera.Getcamera().GetProjectionMatrix(), false, false);

	//パーティクルの描画
	/*g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_particleEmitter.Render(m_gameCamera.Getcamera().GetViewMatrix(), m_gameCamera.Getcamera().GetProjectionMatrix());
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);*/


	for (auto enemy : m_enem)
	{
		enemy->Draw();
	}

	for (auto Tenemy : m_tenem)
	{
		Tenemy->Draw();
	}
	
	for (auto bullet : m_bullets)
	{
		bullet->Draw();
	}
	
	for (int i = 0;i < m_hpNum;i++)
	{
		m_hud[i].Draw(m_sprite);
	}
	
	//m_key.Draw(m_sprite);
	/*if (m_gunflg)
	{
		m_rock.Draw(m_sprite);
	}*/
	m_bloom.Draw();//ブルームが重い、たまにバグるので修正するー
	//m_bossEnemy->Draw();
}

void Game::GameEnd()
{
	g_scene->SceneChange(g_scene->CHANGEEND);
}

HRESULT Game::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}