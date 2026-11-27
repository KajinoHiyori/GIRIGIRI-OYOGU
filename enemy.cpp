//==========================================
// 
// 敵処理[enemy.h]
// Create : 2026/05/19~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "enemy.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "debugproc.h"
#include "particle.h"
#include "sound.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define MOVE_RAND	((float)(rand() % 20 - 10) * 0.35f)	// 移動量ランダム
#define ANGLE_COEFFICIENT	(0.2f)	// 角度補正係数
#define GENERAT_INTERVAL	(360)	// 自動生成間隔
#define PARTICLE_LIFE		(5)		// パーティクル寿命
#define APPEAR_TIME			(120)	// 出現時の判定ナシ時間
#define UI_LIMIT			(60.0f)	// UIによる行動範囲制限

//=============================
// 静的メンバ変数宣言
//=============================
const char* CEnemy::m_apFilenameType[CEnemy::TYPE_MAX] =
{
	"data\\TEXTURE\\enemy\\Enemy_00.png",	// テクスチャ000
	"data\\TEXTURE\\enemy\\Enemy_01.png",	// テクスチャ001
	"data\\TEXTURE\\enemy\\Enemy_02.png",	// テクスチャ002
	"data\\TEXTURE\\enemy\\Enemy_03.png",	// テクスチャ002
};
int CEnemy::m_nNumAll = 0;	// 総数のクリア
int CEnemy::m_nGenerator = 0;	// 生成間隔のクリア

//=============================
// コンストラクタ
//=============================
CEnemy::CEnemy(int nPriority) : CObject2D(nPriority)
{
	m_move = INIT_D3DVEC3;			// 移動量
	m_rot_inertia = INIT_D3DVEC3;	// 向きの慣性
	m_fLength_inertia = 0.0f;		// 拡大縮小の慣性
	m_type = TYPE_000;				// 種類の初期化
	m_fSpeed = 0.0f;				// 移動量設定
	m_state = STATE_APPEAR;			// 出現状態
	m_nCounterState = 0;			// ステートカウンター初期化
	m_nIdxTexture = 0;
	m_nNumAll++;					// 総数の加算
}

//=============================
// デストラクタ
//=============================
CEnemy::~CEnemy()
{

}

//=============================
// 敵生成処理
//=============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy* pEnemy = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		if (pEnemy != NULL)
		{ // インスタンス生成に成功
			pEnemy->Init(type, pos);

			return pEnemy;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CEnemy::Init(TYPE type, D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetTexture();

	// 2Dオブジェクトの初期化
	CObject2D::Init(pos, ENEMY_HEIGHT, ENEMY_WIDTH);

	m_nIdxTexture = pTexture->Register(m_apFilenameType[type]);
	BindTexture(m_nIdxTexture);

	// 出現中は色を半透明に設定
	SetColor(COLOR_WHITE_ALPHA);
	m_state = STATE_APPEAR;

	// 移動量設定
	m_move.x = MOVE_RAND + 0.5f;
	m_move.y = MOVE_RAND + 0.5f;

	// スピード管理
	m_fSpeed = 1.0f;

	m_type = type;	// 種類を設定

	// オブジェクトにタイプを指定
	SetType(TYPE_ENEMY);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CEnemy::Uninit(void)
{
	// object2Dの終了処理
	CObject2D::Uninit();

	// 総数の減算
	m_nNumAll--;
}

//=============================
// 更新処理
//=============================
void CEnemy::Update(void)
{
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

	if (m_nCounterState < APPEAR_TIME)
	{ // 判定ナシ期間
		m_nCounterState++;
		if (m_nCounterState >= APPEAR_TIME)
		{ // 一定フレーム経過
			m_state = STATE_NORMAL;
			SetColor(COLOR_WHITE);
		}
	}

	// 移動量の更新
	pos += m_move;

	// 行動範囲制限
	if (pos.x < ENEMY_SIZE * 0.5f)
	{ // 左端
		pos.x = ENEMY_SIZE * 0.5f;
		m_move.x *= -1.0f;
	}
	else if (pos.x > SCREEN_WIDTH - ENEMY_SIZE * 0.5f)
	{ // 右端
		pos.x = SCREEN_WIDTH - ENEMY_SIZE * 0.5f;
		m_move.x *= -1.0f;
	}
	if (pos.y < ENEMY_SIZE * 0.5f)
	{ // 上端
		pos.y = ENEMY_SIZE * 0.5f;
		m_move.y *= -1.0f;
	}
	else if (pos.y > SCREEN_HEIGHT - UI_LIMIT - ENEMY_SIZE * 0.5f)
	{ // 下端
		pos.y = SCREEN_HEIGHT - UI_LIMIT - ENEMY_SIZE * 0.5f;
		m_move.y *= -1.0f;
	}

	// 回転管理
	float fRot = AngleNormalize(atan2f(m_move.x, m_move.y));
	rot.z = AngleNormalize(-fRot - D3DX_PI * 0.5f);

	// 位置情報の更新
	SetPosition(pos);

	// 角度情報の更新
	SetRotation(rot);
}

//=============================
// 描画処理
//=============================
void CEnemy::Draw(void)
{
	// object2Dの描画処理
	CObject2D::Draw();
}

//=============================
// 自動生成処理
//=============================
void CEnemy::Generator(void)
{
	m_nGenerator++;
	if (m_nGenerator > GENERAT_INTERVAL)
	{ // 規定間隔に到達
		m_nGenerator = 0;	// 生成間隔カウンターの初期化

		CEnemy::TYPE type = static_cast<CEnemy::TYPE>(rand() % static_cast<int>(CEnemy::TYPE_MAX));	// 生成するタイプを設定
		D3DXVECTOR3 pos = RAND_POS;	// 生成位置を設定
		Create(pos, type);	// エナジー生成

		// 種類ごとにパーティクル生成
		switch (type)
		{
		case TYPE_000:	// 緑
			CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_GREEN, PARTICLE_LIFE);
			break;

		case TYPE_001:	// 紫
			CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_VIOLET, PARTICLE_LIFE);
			break;

		case TYPE_002:	// 灰色
			CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_LIGHTGRAY, PARTICLE_LIFE);
			break;

		case TYPE_003:	// 黄色
			CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_YELLOW, PARTICLE_LIFE);
			break;
		}

		// SEの再生
		CSound* pSound = CManager::GetSound();
		pSound->Play(CSound::SE_ENEMYAPPEAR);
	}
}