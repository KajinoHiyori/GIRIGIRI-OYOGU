//==========================================
// 
// 開始管理処理[end.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "end.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sound.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define END_POS	(D3DXVECTOR3(640.0f, 360.0f, 0.0f))	// 開始管理位置
#define END_WIDTH	(static_cast<float>(SCREEN_WIDTH) * 0.5f)	// 横幅
#define END_HEIGHT	(static_cast<float>(SCREEN_HEIGHT) * 0.5f)	// 縦幅
//=============================
// 静的メンバ変数宣言
//=============================
const char* CEnd::m_apFilenameType[CEnd::TYPE_MAX] =
{
	"data\\TEXTURE\\end\\end000.png",	// テクスチャ000
	"data\\TEXTURE\\end\\end001.png",	// テクスチャ000
};

//=============================
// コンストラクタ
//=============================
CEnd::CEnd(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apObject2D[0], NULL, sizeof m_apObject2D);	// ポインタのクリア
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);
}

//=============================
// デストラクタ
//=============================
CEnd::~CEnd()
{

}

//=============================
// 開始管理生成処理
//=============================
CEnd* CEnd::Create(TYPE type)
{
	CEnd* pEnd = NULL;

	if (pEnd == NULL)
	{
		pEnd = new CEnd(7);
		if (pEnd != NULL)
		{ // インスタンス生成に成功
			// 開始管理の初期化処理
			pEnd->Init(type);

			return pEnd;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CEnd::Init(TYPE type)
{
	CTexture* pTexture = CManager::GetTexture();

	m_aIdxTexture[type] = pTexture->Register(m_apFilenameType[type]);

	for (int nCntEnd = 0; nCntEnd < NUM_END; nCntEnd++)
	{
		// ポリゴンの用意
		if (m_apObject2D[nCntEnd] == NULL)
		{ // 初期化が行われている場合
			m_apObject2D[nCntEnd] = m_apObject2D[nCntEnd]->Create(END_POS, END_WIDTH, END_HEIGHT, COLOR_WHITE);
			m_apObject2D[nCntEnd]->BindTexture(m_aIdxTexture[type]);
		}
		else
		{ // 初期化に失敗
			return E_FAIL;
		}
		// オブジェクトにタイプを指定
		SetType(TYPE_END);
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CEnd::Uninit(void)
{
	for (int nCntEnd = 0; nCntEnd < NUM_END; nCntEnd++)
	{
		// number2Dの終了処理
		if (m_apObject2D[nCntEnd] != NULL)
		{ // 使用されている場合
			m_apObject2D[nCntEnd]->Uninit();
			m_apObject2D[nCntEnd] = NULL;
		}
	}

	// 自分自身の破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CEnd::Update(void)
{
	
}

//=============================
// 描画処理
//=============================
void CEnd::Draw(void)
{
	for (int nCntEnd = 0; nCntEnd < NUM_END; nCntEnd++)
	{
		// ポリゴンの描画
		if (m_apObject2D[nCntEnd] != NULL)
		{
			m_apObject2D[nCntEnd]->Draw();
		}
	}
}
