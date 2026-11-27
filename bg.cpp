//==========================================
// 
// 背景処理[bg.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "polygon2D.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define BG_POS	(D3DXVECTOR3(640.0f, 360.0f, 0.0f))	// 背景位置
#define BG1_POS	(D3DXVECTOR3(640.0f, 720.0f, 0.0f))	// 背景位置
#define BG_WIDTH	(static_cast<float>(SCREEN_WIDTH) * 0.5f)	// 横幅
#define BG_HEIGHT	(static_cast<float>(SCREEN_HEIGHT) * 0.5f)	// 縦幅
#define CHANGE_BG	(10000)	// 背景変更
#define CHANGE_BG1	(30000)	// 背景変更
#define ADD_HEIGHT	(20.0f)	// 背景遷移

//=============================
// 静的メンバ変数宣言
//=============================
const char* CBG::m_pFilenameType = "data\\TEXTURE\\bg\\bg000.png";	// テクスチャ000

//=============================
// コンストラクタ
//=============================
CBG::CBG(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apObject2D[0], NULL, sizeof m_apObject2D);	// ポインタのクリア
}

//=============================
// デストラクタ
//=============================
CBG::~CBG()
{

}

//=============================
// 背景生成処理
//=============================
CBG* CBG::Create(void)
{
	CBG* pBG = NULL;

	if (pBG == NULL)
	{
		pBG = new CBG;
		if (pBG != NULL)
		{ // インスタンス生成に成功
			// 背景の初期化処理
			pBG->Init();

			return pBG;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CBG::Init(void)
{
	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		// ポリゴンの用意
		if (m_apObject2D[nCntBG] == NULL)
		{ // 初期化が行われている場合
			switch (nCntBG)
			{
			case TYPE_DARKBLUE:	// 紺色
				m_apObject2D[nCntBG] = m_apObject2D[nCntBG]->Create(BG1_POS, BG_WIDTH, SCREEN_HEIGHT, COLOR_DARKBLUE, CPolygon2D::CENTER_BUTTON);
				break;

			case TYPE_BLUE:	// 青色
				m_apObject2D[nCntBG] = m_apObject2D[nCntBG]->Create(BG1_POS, BG_WIDTH, 0.0f, COLOR_BLUE, CPolygon2D::CENTER_BUTTON);
				break;

			case TYPE_LIGHTBLUE:	// 水
				m_apObject2D[nCntBG] = m_apObject2D[nCntBG]->Create(BG1_POS, BG_WIDTH, 0.0f, COLOR_LIGHTBLUE, CPolygon2D::CENTER_BUTTON);
				break;

			case TYPE_TEXTURE:	// テクスチャ
				m_apObject2D[nCntBG] = m_apObject2D[nCntBG]->Create(BG_POS, BG_WIDTH, BG_HEIGHT, COLOR_WHITE_ALPHA75);
				
				m_nIdxTexture = pTexture->Register(m_pFilenameType);
				m_apObject2D[nCntBG]->BindTexture(m_nIdxTexture);
				break;
			}
		}
		else
		{ // 初期化に失敗
			return E_FAIL;
		}
		// オブジェクトにタイプを指定
		SetType(TYPE_BG);
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CBG::Uninit(void)
{
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		// number2Dの終了処理
		if (m_apObject2D[nCntBG] != NULL)
		{ // 使用されている場合
			m_apObject2D[nCntBG]->Uninit();
			m_apObject2D[nCntBG] = NULL;
		}
	}

	// 自分自身の破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CBG::Update(void)
{
	// スコアの取得
	CScore* pScore = CManager::GetScore();
	int nScore = pScore->Get();
	
	// 背景の高度変更[紺→青]====================================
	float fBlue = m_apObject2D[TYPE_BLUE]->GetHeight();
	if (fBlue <= SCREEN_HEIGHT && nScore >= CHANGE_BG)
	{ // 一定スコア越えたら背景を変更
		fBlue += ADD_HEIGHT;
	}
	// 制限を設ける
	if (fBlue > SCREEN_HEIGHT)
	{
		fBlue = SCREEN_HEIGHT;
	}

	// 背景の高度変更[青→水]====================================
	float fLight = m_apObject2D[TYPE_LIGHTBLUE]->GetHeight();
	if (fLight <= SCREEN_HEIGHT && nScore >= CHANGE_BG1)
	{ // 一定スコア越えたら背景を変更
		fLight += ADD_HEIGHT;
	}
	// 制限を設ける
	if (fLight > SCREEN_HEIGHT)
	{
		fLight = SCREEN_HEIGHT;
	}

	// 高度設定
	m_apObject2D[TYPE_BLUE]->SetHeight(fBlue);
	m_apObject2D[TYPE_LIGHTBLUE]->SetHeight(fLight);
}

//=============================
// 描画処理
//=============================
void CBG::Draw(void)
{
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{		
		if (m_apObject2D[nCntBG] != NULL)
		{ // 初期化が行われている場合
			m_apObject2D[nCntBG]->Draw();
		}
	}
}
