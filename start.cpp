//==========================================
// 
// 開始管理処理[start.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "start.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sound.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define START_POS	(D3DXVECTOR3(640.0f, 360.0f, 0.0f))	// 開始管理位置
#define START_WIDTH	(static_cast<float>(SCREEN_WIDTH) * 0.5f)	// 横幅
#define START_HEIGHT	(static_cast<float>(SCREEN_HEIGHT) * 0.5f)	// 縦幅

//=============================
// 静的メンバ変数宣言
//=============================
const char* CStart::m_apFilenameType[CStart::TYPE_MAX] =
{
	"data\\TEXTURE\\start.png",	// テクスチャ000
};


//=============================
// コンストラクタ
//=============================
CStart::CStart(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apObject2D[0], NULL, sizeof m_apObject2D);	// ポインタのクリア
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);		// インデックスのクリア
}

//=============================
// デストラクタ
//=============================
CStart::~CStart()
{

}

//=============================
// 開始管理生成処理
//=============================
CStart* CStart::Create(void)
{
	CStart* pStart = NULL;

	if (pStart == NULL)
	{
		pStart = new CStart(7);
		if (pStart != NULL)
		{ // インスタンス生成に成功
			// 開始管理の初期化処理
			pStart->Init();

			return pStart;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CStart::Init(void)
{
	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	for (int nCntStart = 0; nCntStart < NUM_START; nCntStart++)
	{
		// ポリゴンの用意
		if (m_apObject2D[nCntStart] == NULL)
		{ // 初期化が行われている場合
			m_apObject2D[nCntStart] = m_apObject2D[nCntStart]->Create(START_POS, START_WIDTH, START_HEIGHT, COLOR_WHITE);
			m_aIdxTexture[nCntStart] = pTexture->Register(m_apFilenameType[nCntStart]);
			m_apObject2D[nCntStart]->BindTexture(m_aIdxTexture[nCntStart]);
		}
		else
		{ // 初期化に失敗
			return E_FAIL;
		}
		// オブジェクトにタイプを指定
		SetType(TYPE_START);
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CStart::Uninit(void)
{
	for (int nCntStart = 0; nCntStart < NUM_START; nCntStart++)
	{
		// number2Dの終了処理
		if (m_apObject2D[nCntStart] != NULL)
		{ // 使用されている場合
			m_apObject2D[nCntStart]->Uninit();
			m_apObject2D[nCntStart] = NULL;
		}
	}

	// 自分自身の破棄
	Release();

	// リカバリー音の再生
	CSound* pSound = CManager::GetSound();
	pSound->Play(CSound::SE_RECOVER);
}

//=============================
// 更新処理
//=============================
void CStart::Update(void)
{
	
}

//=============================
// 描画処理
//=============================
void CStart::Draw(void)
{
	for (int nCntStart = 0; nCntStart < NUM_START; nCntStart++)
	{
		// 描画処理
		if (m_apObject2D[nCntStart] != NULL)
		{
			m_apObject2D[nCntStart]->Draw();
		}
	}
}
