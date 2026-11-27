//==========================================
// 
// UI処理[ui.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "ui.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define TIME_POS	(D3DXVECTOR3(110.0f, 45.0f, 0.0f))	// UI位置
#define SCORE_POS	(D3DXVECTOR3(750.0f, 45.0f, 0.0f))	// UI位置
#define UI_HEIGHT	(80.0f * 0.325f)	// UIの縦幅
#define UI_WIDTH	(320.0f * 0.325f)	// UIの縦幅

//=============================
// 静的メンバ変数宣言
//=============================
const char* CUI::m_apFilenameType[CUI::TYPE_MAX] =
{
	"data\\TEXTURE\\ui\\time.png",	// テクスチャ000
	"data\\TEXTURE\\ui\\score.png",	// テクスチャ000
};

//=============================
// コンストラクタ
//=============================
CUI::CUI(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apObject2D[0], NULL, sizeof m_apObject2D);	// ポインタのクリア
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);		// テクスチャのクリア
}

//=============================
// デストラクタ
//=============================
CUI::~CUI()
{

}

//=============================
// UI生成処理
//=============================
CUI* CUI::Create(void)
{
	CUI* pUI = NULL;

	if (pUI == NULL)
	{
		pUI = new CUI;
		if (pUI != NULL)
		{ // インスタンス生成に成功
			// UIの初期化処理
			pUI->Init();

			return pUI;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CUI::Init(void)
{
	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	for (int nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		// ポリゴンの用意
		if (m_apObject2D[nCntUI] == NULL)
		{ // 初期化が行われている場合
			switch (nCntUI)
			{
			case TYPE_TIME:	// 時間
				m_apObject2D[nCntUI] = m_apObject2D[nCntUI]->Create(TIME_POS, UI_WIDTH, UI_HEIGHT, COLOR_WHITE);
				break;

			case TYPE_SCORE:	// スコア
				m_apObject2D[nCntUI] = m_apObject2D[nCntUI]->Create(SCORE_POS, UI_WIDTH, UI_HEIGHT, COLOR_WHITE);
				break;
			}
			m_aIdxTexture[nCntUI] = pTexture->Register(m_apFilenameType[nCntUI]);
			m_apObject2D[nCntUI]->BindTexture(m_aIdxTexture[nCntUI]);
		}
		else
		{ // 初期化に失敗
			return E_FAIL;
		}
		// オブジェクトにタイプを指定
		SetType(TYPE_UI);
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CUI::Uninit(void)
{
	for (int nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		// 2Dポリゴンの終了処理
		if (m_apObject2D[nCntUI] != NULL)
		{ // 使用されている場合
			m_apObject2D[nCntUI]->Uninit();
			m_apObject2D[nCntUI] = NULL;
		}
	}

	// 自分自身の破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CUI::Update(void)
{
}

//=============================
// 描画処理
//=============================
void CUI::Draw(void)
{
	for (int nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		// 2Dポリゴンの描画処理
		if (m_apObject2D[nCntUI] != NULL)
		{ // 使用されている場合
			m_apObject2D[nCntUI]->Draw();
		}
	}
}
