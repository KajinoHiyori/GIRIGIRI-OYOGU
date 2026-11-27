//==========================================
// 
// プレイヤー処理[player.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "debugproc.h"
#include "enemy.h"
#include "explosion.h"
#include "particle.h"
#include "score.h"
#include "gauge.h"
#include "timer.h"
#include "sound.h"
#include "cursor.h"
#include "effect.h"
#include "orbit2D.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define PLAYER_SPEED		(4.0f)	// 移動速度
#define SPEED_ADD			(0.075f)	// 移動速度の加算
#define PLAYER_BULLET		(30)	// プレイヤーの弾の寿命
#define ANGLE_COEFFICIENT	(0.2f)	// 角度補正係数
#define EN_PARTICLE_LIFE	(20)	// 敵死亡時のパーティクル寿命
#define LIMIT_SIZE			(1.7f)	// ギリギリを攻める際の幅
#define LIMIT_POINT			(50)	// ギリギリを攻めた際の加点数
#define RECOVERY			(5)		// 回復量
#define CONSUMPUTION		(10)	// 消費量
#define COMBO_RECOVER		(4)		// コンボ時の回復量
#define MAX_PRESS			(2000)	// 最大のプレス時間[加速可能]
#define HALF_PRESS			(1000)	// 最大のプレス時間[通常速度]
#define UI_LIMIT			(60.0f)	// UIによる行動範囲制限
#define LOW_SPEED			(1.0f)	// 最低速度
#define APPER_SPEED			(2.5f)	// 赤ゲージの加速
#define EFFECT_LIFE			(5)		// 軌跡の寿命

//=============================
// 静的メンバ変数宣言
//=============================
const char* CPlayer::m_apFilenameType[CPlayer::TYPE_MAX] =
{
	"data\\TEXTURE\\player\\Player_00.png",	// テクスチャ000
	"data\\TEXTURE\\player\\Player_01.png",	// テクスチャ001
};

//=============================
// コンストラクタ
//=============================
CPlayer::CPlayer(int nPriority): CObject2D(nPriority)
{
	m_move = INIT_D3DVEC3;			// 移動量
	m_posDest = INIT_D3DVEC3;		// 目的地
	m_rot_inertia = INIT_D3DVEC3;	// 向きの慣性
	m_fLength_inertia = 0.0f;		// 拡大縮小の慣性
	m_fSpeed = 0.0f;				// 移動速度
	m_nMousePress = 0;				// Press時間を計測
	m_bCillisionOld = false;		// 過去の衝突状態を管理
	m_bCillision = false;			// 衝突状態を管理
	m_type = TYPE_NORMAL;			// テクスチャの種類を決定
	m_pOrbit = NULL;				// オービット情報
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);	// テクスチャインデックス
	m_bHit = false;
}

//=============================
// デストラクタ
//=============================
CPlayer::~CPlayer()
{

}

//=============================
// プレイヤー生成処理
//=============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, TYPE type)
{
	CPlayer* pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{ // インスタンス生成に成功
			pPlayer->Init(type, pos);
			
			// オービット生成
			float fAngle = pPlayer->GetAngle();
			float fLength = pPlayer->GetLength();
			if (pPlayer->m_pOrbit == NULL)
			{
				pPlayer->m_pOrbit = pPlayer->m_pOrbit->Create(pos, COLOR_ORANGE_ALPHA, COLOR_ORANGE_ALPHA, INIT_D3DVEC3, fAngle, fLength);
			}
			return pPlayer;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CPlayer::Init(TYPE type, D3DXVECTOR3 pos)
{
	// 2Dオブジェクトの初期化
	CObject2D::Init(pos, PLAYER_HEIGHT, PLAYER_WIDTH);

	// テクスチャ設定
	CTexture* pTexture = CManager::GetTexture();
	for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
	{
		m_aIdxTexture[nCntType] = pTexture->Register(m_apFilenameType[nCntType]);
	}

	// 角度管理
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// マウスを押せる時間を半分に設定
	m_nMousePress = static_cast<int>(MAX_PRESS * 0.25f);

	// テクスチャの種類を設定
	m_type = TYPE_NORMAL;

	// オブジェクトにタイプを指定
	SetType(TYPE_PLAYER);

	// 移動量設定
	m_move = D3DXVECTOR3(PLAYER_SPEED, 0.0f, 0.0f);
	m_fSpeed = PLAYER_SPEED;

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CPlayer::Uninit(void)
{
	// オービット破棄
	if (m_pOrbit != NULL)
	{
		m_pOrbit->Uninit();
		delete m_pOrbit;
		m_pOrbit = NULL;
	}

	// object2Dの終了処理
	CObject2D::Uninit();

	// SEの停止
	CSound* pSound = CManager::GetSound();
	pSound->Stop(CSound::SE_PRESSEFFECT);
}

//=============================
// 更新処理
//=============================
void CPlayer::Update(void)
{
	// 餌の取得
	CCursor* pCursor = CManager::GetCursor();
	// 入力情報を取得
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse* pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad* pInputJoypad = CManager::GetInputJoypad();		// ジョイパッド
	// デバッグ表示
	CDebugProc* pDebugProc = CManager::GetDebugProc();
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	// 角度取得
	D3DXVECTOR3 rot = GetRotation();
	// 過去の衝突状態を格納
	m_bCillisionOld = m_bCillision;

	// マウスの入力時間を回復
	int nMousePressOld = m_nMousePress;	// 過去の入力時間を格納

	m_nMousePress += RECOVERY;
	if (m_nMousePress >= MAX_PRESS)
	{ // 最大値に到達
		m_nMousePress = MAX_PRESS;
	}

	// 行動範囲制限
	if (pos.x < PLAYER_SIZE * 0.5f)
	{ // 左端
		pos.x = PLAYER_SIZE * 0.5f;
		m_move.x *= -1.0f;
	}
	else if (pos.x > SCREEN_WIDTH - PLAYER_SIZE * 0.5f)
	{ // 右端
		pos.x = SCREEN_WIDTH - PLAYER_SIZE * 0.5f;
		m_move.x *= -1.0f;
	}
	if (pos.y < PLAYER_SIZE * 0.5f)
	{ // 上端
		pos.y = PLAYER_SIZE * 0.5f;
		m_move.y *= -1.0f;
	}
	else if (pos.y > SCREEN_HEIGHT - UI_LIMIT - PLAYER_SIZE * 0.5f)
	{ // 下端
		pos.y = SCREEN_HEIGHT - UI_LIMIT - PLAYER_SIZE * 0.5f;
		m_move.y *= -1.0f;
	}

	// マウスが押されている間、マウスカーソルを追尾する
	if (pInputMouse->GetPress(CInputMouse::BUTTON_LEFT) == true)
	{
		// 押すことができる時間を減少
		m_nMousePress -= CONSUMPUTION;
		if (m_nMousePress < 0)
		{ // 長時間押したことでゲージが尽きた
			m_nMousePress = 0;
			m_type = TYPE_NORMAL;
			// 餌の表示管理
			pCursor->SetDisp(false);
		}
		else
		{ // ゲージが残っている
			// 目的地取得
			m_posDest = pInputMouse->GetClientPos();
			float fRotMove = atan2f(m_move.x, m_move.y);	// 現在の移動方向
			float fRotDest = atan2f(m_posDest.x - pos.x, m_posDest.y - pos.y);	// 目的の移動方向
			float fRotDiff = AngleNormalize(fRotDest - fRotMove);	// 目的の値までの差分
			fRotMove += fRotDiff * ANGLE_COEFFICIENT;	// 角度補正
			fRotMove = AngleNormalize(fRotMove);
			m_move.x = sinf(fRotMove) * m_fSpeed;
			m_move.y = cosf(fRotMove) * m_fSpeed;

			// 餌の表示管理
			pCursor->SetDisp(true);

			// エフェクト生成
			//CParticle::Create(m_posDest, CParticle::TYPE_FIREFLOWER, COLOR_YELLOW, 2);
			m_type = TYPE_PRESS;

			// 残量に応じて移動量変更
			if (HALF_PRESS >= m_nMousePress)
			{ // 赤ゲージが溜まっていない
				//m_fSpeed = PLAYER_SPEED * (static_cast<float>(m_nMousePress) / static_cast<float>(HALF_PRESS)) + APPER_SPEED;
				m_pOrbit->SetColor(COLOR_ORANGE, COLOR_ORANGE);
			}
			else
			{
				//m_fSpeed = PLAYER_SPEED * (static_cast<float>(m_nMousePress) / static_cast<float>(HALF_PRESS)) + LOW_SPEED;
				m_pOrbit->SetColor(COLOR_RED, COLOR_RED);
			}
		}
	}
	else
	{
		// デフォルトの速度に戻す
		m_fSpeed = PLAYER_SPEED; 

		float fRotMove = AngleNormalize(atan2f(m_move.x, m_move.y));	// 現在の移動方向
		m_move.x = sinf(fRotMove) * m_fSpeed;
		m_move.y = cosf(fRotMove) * m_fSpeed;

		// 餌の表示管理
		pCursor->SetDisp(false);
		// テクスチャの設定
		m_type = TYPE_NORMAL;
		m_pOrbit->SetColor(COLOR_BLUE, COLOR_BLUE);
	}

	// SEの再生/停止
	CSound* pSound = CManager::GetSound();
	if (pInputMouse->GetTrigger(CInputMouse::BUTTON_LEFT) == true && m_nMousePress > 0)
	{ // マウスを押した&&ゲージが残っている
		pSound->Play(CSound::SE_PRESSEFFECT);
		pSound->Stop(CSound::SE_RECOVER);
	}
	else if (pInputMouse->GetRelease(CInputMouse::BUTTON_LEFT) == true || m_nMousePress <= 0)
	{ // マウスを離した||ゲージが尽きた
		pSound->Stop(CSound::SE_PRESSEFFECT);
		pSound->Play(CSound::SE_RECOVER);
	}
	else if (pInputMouse->GetTrigger(CInputMouse::BUTTON_LEFT) == true && m_nMousePress <= 0)
	{ // マウスを押した&&ゲージが残っていない
		pSound->Play(CSound::SE_BEEP);
	}

	if (nMousePressOld < MAX_PRESS && m_nMousePress >= MAX_PRESS)
	{ // 前回回復しきっていない&&今回回復しきった
		pSound->Stop(CSound::SE_RECOVER);
	}

	// ゲージ範囲の更新
	CGauge* pGauge = CManager::GetGauge();
	float fGauge = static_cast<float>(m_nMousePress) / static_cast<float>(HALF_PRESS);
	pGauge->SetGauge(fGauge);

	// 移動量の更新
	pos += m_move;

	// 回転管理
	float fRot = AngleNormalize(atan2f(m_move.x, m_move.y));
	rot.z = AngleNormalize(-fRot + D3DX_PI * 0.5f);

	// オービット更新
	m_pOrbit->Update(pos, rot);

	// 位置情報の更新
	SetPosition(pos);

	// 角度情報の更新
	SetRotation(rot);

	// テクスチャを設定
	BindTexture(m_aIdxTexture[m_type]);

	pos = GetPosition();
	pDebugProc->Print("位置 : (%f, %f)\n", pos.x, pos.y);
	pDebugProc->Print("速度 : %f\n", m_fSpeed);

	// 敵との当たり判定
	bool bEnd = CManager::GetEndState();	// 終了状態であれば処理を弾く
	if (bEnd == false)
	{
		m_bCillision = CollisionEnemy(pos);
		if (m_bHit == true)
		{
			// 自分自身の破棄
			Uninit();
		}
	}
}

//=============================
// 描画処理
//=============================
void CPlayer::Draw(void)
{
	// オービットの描画
	m_pOrbit->Draw();

	// object2Dの描画処理
	CObject2D::Draw();
}

//=============================
// 敵との当たり判定
//=============================
bool CPlayer::CollisionEnemy(D3DXVECTOR3 pos)
{
	bool bCollision = false;
	bool bSound = false;
	// SEの再生/停止
	CSound* pSound = CManager::GetSound();
	CCursor* pCursor = CManager::GetCursor();

	for (int nPriority = 0; nPriority < MAX_PRIORITY; nPriority++)
	{
		for (int nObj = 0; nObj < MAX_OBJECT; nObj++)
		{
			CObject* pObj = NULL;	// オブジェクトのポインタを取得
			pObj = GetObject(nPriority, nObj);	// オブジェクト取得

			if (pObj != NULL)
			{ // オブジェクトが使用されている
				CObject::TYPE type = pObj->GetType();	// オブジェクトの種類を取得

				if (type == TYPE_ENEMY)
				{ // 敵だった場合判定を実行
					CEnemy* pEnemy = static_cast<CEnemy*>(pObj);	// CEnemy型にキャスト
					if (pEnemy->GetState() == CEnemy::STATE_APPEAR)
					{ // 出現状態であれば判定をなくす
						continue;
					}

					D3DXVECTOR3 posEnemy = pEnemy->GetPosition();	// 敵の位置取得
					float fLength = (posEnemy.x - pos.x) * (posEnemy.x - pos.x) + (posEnemy.y - pos.y) * (posEnemy.y - pos.y);	// 2点間の距離を取得
					if (fLength <= (PLAYER_SIZE + ENEMY_SIZE) * (PLAYER_SIZE + ENEMY_SIZE))
					{ // 当たっている場合
						bCollision = true;
						// SEの再生
						pSound->Play(CSound::SE_DAMAGE);
						// リカバリー音の停止
						pSound->Stop(CSound::SE_RECOVER);
						// 衝突音の停止
						pSound->Stop(CSound::SE_COLLISION);
						
						// 餌の非表示
						pCursor->SetDisp(false);
						
						// 終了設定
						CManager::SetEndState(true, false);
						
						// タイマーの停止
						CTimer* pTimer = CManager::GetTimer();
						pTimer->SetOperate(false);
						
						// 爆発生成
						CExplosion::Create(pos, COLOR_ORANGE);
						
						// パーティクル生成
						CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_ORANGE, EN_PARTICLE_LIFE);
						m_bHit = true;
						return bCollision;
					}
					else if (fLength <= (PLAYER_SIZE * LIMIT_SIZE + ENEMY_SIZE * LIMIT_SIZE) * (PLAYER_SIZE * LIMIT_SIZE + ENEMY_SIZE * LIMIT_SIZE))
					{ // ギリギリを攻めた場合
						CScore* pScore = CManager::GetScore();
						pScore->Add(LIMIT_POINT);
						// パーティクル生成
						CParticle::Create(pos, CParticle::TYPE_RANDCOL, COLOR_ORANGE, 2);

						// 速度加算
						m_fSpeed += SPEED_ADD;

						// ゲージ加算
						m_nMousePress += COMBO_RECOVER;
						// ゲージ範囲の更新
						CGauge* pGauge = CManager::GetGauge();
						float fGauge = static_cast<float>(m_nMousePress) / static_cast<float>(HALF_PRESS);
						pGauge->SetGauge(fGauge);

						// SEの再生
						if (m_bCillisionOld == false && bSound == false)
						{
							pSound->Play(CSound::SE_COLLISION);
						}

						bSound = true;
						bCollision = true;
					}
				}
			}
		}
	}

	// SEの停止
	if (bSound == false)
	{
		pSound->Stop(CSound::SE_COLLISION);
	}

	// 敵に当たっていなければ速度減少
	if (bCollision == false)
	{
		m_fSpeed = PLAYER_SPEED;
		if (m_fSpeed <= PLAYER_SPEED)
		{ // 規定値を下回らないように制限
			m_fSpeed = PLAYER_SPEED;
		}
	}

	return bCollision;
}
