//==========================================
// 
// マネージャー処理[manager.cpp]
// Create : 2026/05/12
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "number2D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "explosion.h"
#include "score.h"
//#include "effect2D.h"
#include "effect.h"
#include "bg.h"
#include "particle.h"
#include "timer.h"
#include "gauge.h"
#include "sound.h"
#include "start.h"
#include "end.h"
#include "cursor.h"
#include "ui.h"

//=============================
// 静的メンバ変数宣言
//=============================
CRenderer* CManager::m_pRenderer = NULL;			// レンダラーへのポインタ
CInputKeyboard* CManager::m_pInputKeyboard = NULL;	// キーボード入力へのポインタ
CInputMouse* CManager::m_pInputMouse = NULL;		// マウス入力へのポインタ
CInputJoypad* CManager::m_pInputJoypad = NULL;		// ジョイパッド入力へのポインタ
CDebugProc* CManager::m_pDebugProc = NULL;			// デバッグ表示へのポインタ
CTexture* CManager::m_pTexture = NULL;				// テクスチャへのポインタ
CPlayer* CManager::m_pPlayer = NULL;				// プレイヤーへのポインタ
CScore* CManager::m_pScore = NULL;					// スコアへのポインタ
CTimer* CManager::m_pTimer = NULL;					// タイマーへのポインタ
CGauge* CManager::m_pGauge = NULL;					// ゲージへのポインタ
CBG* CManager::m_pBG = NULL;						// 背景へのポインタ
CSound* CManager::m_pSound = NULL;					// サウンドへのポインタ
CStart* CManager::m_pStart = NULL;					// スタートへのポインタ
CEnd* CManager::m_pEnd = NULL;						// 終了へのポインタ
CCursor* CManager::m_pCursor = NULL;				// カーソルへのポインタ
CUI* CManager::m_pUI = NULL;						// UIへのポインタ
bool CManager::m_bPause = false;					// ポーズ状態管理[true : ポーズ中 / false : 通常]
bool CManager::m_bStart = false;					// 開始状態管理[true : ポーズ中 / false : 通常]
bool CManager::m_bEnd = false;						// 終了状態管理[true : 終了 / false : 通常]
bool CManager::m_bEndOld = false;					// 終了状態管理[true : 終了 / false : 通常]

//=============================
// マクロ定義
//=============================
#define GAME_TIME	(60)	// ゲームの制限時間
#define PARTICLE_LIFE		(5)		// パーティクル寿命

//=============================
// コンストラクタ
//=============================
CManager::CManager()
{
}

//=============================
// デストラクタ
//=============================
CManager::~CManager()
{
}

//=============================
// 初期化処理
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	int nID = 0;	// メッセージボックス管理

	// レンダラー生成処理
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;		// レンダラー生成
		if (m_pRenderer == NULL)
		{ // レンダラー生成に失敗
			nID = MessageBox(hWnd, "レンダラー生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	else
	{ // レンダラーのクリアに失敗
		nID = MessageBox(hWnd, "レンダラー生成に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// レンダラー初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{ // 初期化処理に失敗した場合
		nID = MessageBox(hWnd, "レンダラーの初期化に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// キーボード入力の初期化
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;		// キーボード入力生成
		if (m_pInputKeyboard == NULL)
		{ // キーボード入力生成に失敗
			nID = MessageBox(hWnd, "キーボード入力生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	else
	{ // キーボード入力のクリアに失敗
		nID = MessageBox(hWnd, "キーボード入力生成に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// キーボード入力初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{ // 初期化処理に失敗した場合
		nID = MessageBox(hWnd, "キーボード入力の初期化に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// マウス入力の初期化
	if (m_pInputMouse == NULL)
	{
		m_pInputMouse = new CInputMouse;		// マウス入力生成
		if (m_pInputMouse == NULL)
		{ // マウス入力生成に失敗
			nID = MessageBox(hWnd, "マウス入力生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	else
	{ // マウス入力のクリアに失敗
		nID = MessageBox(hWnd, "マウス入力生成に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// マウス入力初期化処理
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{ // 初期化処理に失敗した場合
		nID = MessageBox(hWnd, "マウス入力の初期化に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// ジョイパッド入力の初期化
	if (m_pInputJoypad == NULL)
	{
		m_pInputJoypad = new CInputJoypad;		// ジョイパッド入力生成
		if (m_pInputJoypad == NULL)
		{ // ジョイパッド生成に失敗
			nID = MessageBox(hWnd, "ジョイパッド入力生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	else
	{ // ジョイパッド入力のクリアに失敗
		nID = MessageBox(hWnd, "ジョイパッド入力生成に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// ジョイパッド入力初期化処理
	if (FAILED(m_pInputJoypad->Init(hInstance, hWnd)))
	{ // 初期化処理に失敗した場合
		nID = MessageBox(hWnd, "ジョイパッド入力の初期化に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// デバッグ表示入力の初期化
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = new CDebugProc;		// デバッグ表示入力生成
		if (m_pDebugProc == NULL)
		{ // デバッグ表示生成に失敗
			nID = MessageBox(hWnd, "デバッグ表示入力生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	else
	{ // デバッグ表示入力のクリアに失敗
		nID = MessageBox(hWnd, "デバッグ表示入力生成に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// デバッグ表示入力初期化処理
	m_pDebugProc->Init();

	// テクスチャの生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;	// テクスチャ生成
		if (m_pTexture == NULL)
		{ // テクスチャ生成に失敗
			nID = MessageBox(hWnd, "テクスチャ生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	else
	{ // テクスチャのクリアに失敗
		nID = MessageBox(hWnd, "テクスチャ生成に失敗", WINDOW_NAME, MB_OK);
		return E_FAIL;
	}

	// テクスチャ読み込み処理
	m_pTexture->Load();

	// サウンドの初期化
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;	// サウンド生成
		if (m_pSound == NULL)
		{ // サウンド生成に失敗
			nID = MessageBox(hWnd, "サウンド生成に失敗", WINDOW_NAME, MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(m_pSound->Init(hWnd)))
	{ // 初期化に失敗
		return E_FAIL;
	}

	//// テクスチャ読み込み処理
	//Load();

	// 各種オブジェクト生成
	Reload();

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CManager::Uninit(void)
{
	// オブジェクトの終了処理
	CObject::ReleaseAll();

	// 背景の初期化
	m_pBG = NULL;

	// プレイヤーの初期化
	m_pPlayer = NULL;
	
	// スコアの初期化
	m_pScore = NULL;

	//// テクスチャ破棄
	//Unload();

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		// テクスチャの破棄処理
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// デバッグ表示の破棄
	if (m_pDebugProc != NULL)
	{
		// デバッグ表示の終了処理
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	// キーボード入力の破棄
	if (m_pInputKeyboard != NULL)
	{
		// キーボード入力の終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// マウス入力の破棄
	if (m_pInputMouse != NULL)
	{
		// マウス入力の終了処理
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	// ジョイパッド入力の破棄
	if (m_pInputJoypad != NULL)
	{
		// キーボード入力の終了処理
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	// 音声の停止
	m_pSound->Stop();

	// サウンドの終了処理
	if (m_pSound != NULL)
	{
		// キーボード入力の終了処理
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================
// 更新処理
//=============================
void CManager::Update(void)
{
	// キーボード入力の更新処理
	m_pInputKeyboard->Update();

	// マウス入力の更新処理
	m_pInputMouse->Update();

	// ジョイパッド入力の更新処理
	m_pInputJoypad->Update();

	// 右クリックで開始
	if (m_pInputMouse->GetTrigger(CInputMouse::BUTTON_RIGHT) == true && m_bStart == false)
	{
		m_bStart = true;
		m_pStart->Uninit();
		m_pStart = NULL;
		m_pSound->Play(CSound::SE_ENTER);	// Enterの再生
	}

	if (m_pInputKeyboard->GetTrigger(DIK_P) == true && m_bStart == true)
	{ // ポーズ切り替え
		m_bPause = m_bPause ^ 1 ? true : false;
		m_pSound->Play(CSound::SE_ENTER);	// Enterの再生
		m_pSound->Stop(CSound::SE_PRESSEFFECT);	// Enterの再生
		m_pSound->Stop(CSound::SE_RECOVER);	// Enterの再生
		m_pSound->Stop(CSound::SE_COLLISION);	// Enterの再生
	}

	if (m_pInputKeyboard->GetTrigger(DIK_R) == true && m_bStart == true)
	{ // リトライ
		Reload();
		m_pSound->Play(CSound::SE_ENTER);	// Enterの再生
	}
	else if (m_pInputMouse->GetTrigger(CInputMouse::BUTTON_RIGHT) == true && m_bEnd == true)
	{// リトライ
		Reload();
		m_pSound->Play(CSound::SE_ENTER);	// Enterの再生
	}

	if (m_bPause == false && m_bStart == true)
	{ // ポーズ中ではない
		// 自動生成処理
		Generator();

		// レンダラー更新処理
		m_pRenderer->Update();
	}
	
	m_pDebugProc->Print("オブジェクト数 : %d\n", CObject::GetNumAll());
	m_pDebugProc->Print("敵の総数 : %d\n", CEnemy::GetNumAll());
	m_pDebugProc->Print("数字の総数 : %d\n", CNumber2D::GetNumAll());
	m_pDebugProc->Print("テクスチャの総数 : %d\n", m_pTexture->GetNumAll());

	// デバッグ表示の更新処理
	m_pDebugProc->Update();
}

//=============================
// 描画処理
//=============================
void CManager::Draw(void)
{
	// レンダラー描画処理
	m_pRenderer->Draw();
}

//=============================
// 自動生成処理
//=============================
void CManager::Generator(void)
{
	// エナジー生成処理
	//CEnergy::Generator();

	if (m_pTimer->GetOperate() == true)
	{ // タイマーが稼働中は敵を自動生成
		// 敵生成処理
		CEnemy::Generator();
	}
}

//=============================
// 終了管理処理
//=============================
void CManager::SetEndState(bool bEnd, bool bWin)
{
	if (m_pEnd == NULL)
	{ // 使用されていない
		switch (bWin)
		{
		case true:	// 勝利
			m_pEnd = CEnd::Create(CEnd::TYPE_WIN);
			break;

		case false:	// 敗北
			m_pEnd = CEnd::Create(CEnd::TYPE_LOSE);
			break;
		}
	}

	m_bEnd = bEnd;
}

#if 0
//=============================
// テクスチャ読み込み処理
//=============================
void CManager::Load(void)
{
	// 2Dオブジェクトの初期化
	CObject::ReleaseAll();

	// プレイヤーテクスチャの読み込み
	CPlayer::Load();

	// 弾のテクスチャの読み込み
	CBullet::Load();

	// 敵のテクスチャの読み込み
	CEnemy::Load();

	// 数字テクスチャの読み込み
	CNumber2D::Load();

	// 爆発テクスチャの読み込み
	CExplosion::Load();

	// エフェクトテクスチャの読み込み
	//CEffect2D::Load();
	CEffect::Load();

	// 背景テクスチャの読み込み
	CBG::Load();

	// エナジーテクスチャの読み込み
	CEnergy::Load();

	// ゲージテクスチャの読み込み
	CGauge::Load();

	// スタートテクスチャの読み込み
	CStart::Load();

	// 終了テクスチャ読み込み
	CEnd::Load();

	// カーソルテクスチャの読み込み
	CCursor::Load();

	// UIテクスチャの読み込み
	CUI::Load();
}

//=============================
// テクスチャ破棄処理
//=============================
void CManager::Unload(void)
{
	// プレイヤーのテクスチャの破棄
	CPlayer::Unload();

	// 弾のテクスチャ破棄
	CBullet::Unload();

	// 敵のテクスチャ破棄
	CEnemy::Unload();

	// 数字のテクスチャ破棄
	CNumber2D::Unload();

	// 爆発テクスチャ破棄
	CExplosion::Unload();

	// エフェクトテクスチャ破棄
	//CEffect2D::Unload();

	CEffect::Unload();

	// 背景テクスチャの破棄
	CBG::Unload();

	// エナジーテクスチャの破棄
	CEnergy::Unload();

	// ゲージテクスチャの破棄
	CGauge::Unload();

	// スタートテクスチャの破棄
	CStart::Unload();

	// 終了テクスチャの破棄
	CEnd::Unload();

	// カーソルテクスチャの破棄
	CCursor::Unload();

	// UIテクスチャの破棄
	CUI::Unload();
}
#endif

//=============================
// 再読み込み時に再生成
//=============================
void CManager::Reload(void)
{
	// 全てのオブジェクト破棄
	CObject::ReleaseAll();

	m_pPlayer = NULL;	// プレイヤーへのポインタ
	m_pScore = NULL;	// スコアへのポインタ
	m_pTimer = NULL;	// タイマーへのポインタ
	m_pBG = NULL;		// 背景へのポインタ
	m_pGauge = NULL;	// ゲージへのポインタ
	m_pStart = NULL;	// スタートへのポインタ
	m_pEnd = NULL;		// 終了へのポインタ
	m_pUI = NULL;		// UIへのポインタ
	m_pCursor = NULL;	// カーソルへのポインタ

	CEnemy::ResetGenerator();	// 自動生成間隔の初期化

	m_pSound->Stop();

	m_pSound->Play(CSound::BGM);	// BGMの再生

	// 背景の用意
	if (m_pBG == NULL)
	{
		m_pBG = CBG::Create();
	}

	// プレイヤーの用意
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), CPlayer::TYPE_NORMAL);
	}

	// UIの用意
	if (m_pUI == NULL)
	{
		m_pUI = CUI::Create();
	}

	// スコアの用意
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(870.0f, 20.0f, 0.0f), 0);
	}

	// タイマーの用意
	if (m_pTimer == NULL)
	{
		m_pTimer = CTimer::Create(D3DXVECTOR3(200.0f, 20.0f, 0.0f), GAME_TIME);
	}

	// ゲージの用意
	if (m_pGauge == NULL)
	{
		m_pGauge = CGauge::Create(D3DXVECTOR3(0.0f, 720.0f, 0.0f));
	}

	// スタートの用意
	if (m_pStart == NULL)
	{
		m_pStart = CStart::Create();
	}

	// カーソルの用意
	if (m_pCursor == NULL)
	{
		m_pCursor = CCursor::Create();
	}

	// 敵の生成
	CEnemy::TYPE type = static_cast<CEnemy::TYPE>(rand() % static_cast<int>(CEnemy::TYPE_MAX));	// 生成するタイプを設定
	D3DXVECTOR3 pos = RAND_POS;	// 生成位置を設定
	CEnemy::Create(pos, type);	// エナジー生成

	// 種類ごとにパーティクル生成
	switch (type)
	{
	case CEnemy::TYPE_000:	// 緑
		CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_GREEN, PARTICLE_LIFE);
		break;

	case CEnemy::TYPE_001:	// 紫
		CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_VIOLET, PARTICLE_LIFE);
		break;

	case CEnemy::TYPE_002:	// 灰色
		CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_LIGHTGRAY, PARTICLE_LIFE);
		break;

	case CEnemy::TYPE_003:	// 黄色
		CParticle::Create(pos, CParticle::TYPE_FIREFLOWER, COLOR_YELLOW, PARTICLE_LIFE);
		break;
	}
	// ポーズ状態の初期化
	m_bPause = false;
	// 開始状態の初期化
	m_bStart = false;
	// 終了状態の初期化
	m_bEnd = false;
}