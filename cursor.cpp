//==========================================
// 
// カーソル処理[cursor.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "cursor.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "polygon2D.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define CURSOR_SPEED		(3.0f)	// 移動速度
#define CURSOR_BULLET		(30)	// カーソルの弾の寿命
#define ANGLE_COEFFICIENT	(0.2f)	// 角度補正係数
#define EN_PARTICLE_LIFE	(20)	// 敵死亡時のパーティクル寿命
#define LIMIT_SIZE			(1.6f)	// ギリギリを攻める際の幅
#define LIMIT_POINT			(10)	// ギリギリを攻めた際の加点数
#define RECOVERY			(5)		// 回復量
#define CONSUMPUTION		(10)	// 消費量
#define MAX_PRESS			(2000)	// 最大のプレス時間[加速可能]
#define HALF_PRESS			(1000)	// 最大のプレス時間[通常速度]
#define UI_LIMIT			(60.0f)	// UIによる行動範囲制限
#define LOW_SPEED			(1.0f)	// 最低速度
#define APPER_SPEED			(2.0f)	// 赤ゲージの加速
#define CURSOR_SIZE			(37.0f)	// カーソルの大きさ

//=============================
// 静的メンバ変数宣言
//=============================
const char* CCursor::m_apFilenameType[CCursor::TYPE_MAX] =
{
	"data\\TEXTURE\\feed.png",	// テクスチャ000
};

//=============================
// コンストラクタ
//=============================
CCursor::CCursor(int nPriority)
{
	// 初期化
	m_bDisp = true;
	m_pObject2D = NULL;
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);
}

//=============================
// デストラクタ
//=============================
CCursor::~CCursor()
{

}

//=============================
// カーソル生成処理
//=============================
CCursor* CCursor::Create(void)
{
	CCursor* pCursor = NULL;

	if (pCursor == NULL)
	{
		pCursor = new CCursor(7);
		if (pCursor != NULL)
		{ // インスタンス生成に成功
			pCursor->Init();
			// テクスチャを設定
			return pCursor;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CCursor::Init(void)
{
	if (m_pObject2D == NULL)
	{ // 初期化が行われている場合
		CTexture* pTexture = CManager::GetTexture();

		for (int nCntTexture = 0; nCntTexture < TYPE_MAX; nCntTexture++)
		{
			m_aIdxTexture[nCntTexture] = pTexture->Register(m_apFilenameType[nCntTexture]);
		}

		m_pObject2D = m_pObject2D->Create(INIT_D3DVEC3, CURSOR_SIZE, CURSOR_SIZE, COLOR_WHITE);
		m_pObject2D->BindTexture(m_aIdxTexture[TYPE_000]);
	}
	else
	{ // 初期化に失敗
		return E_FAIL;
	}

	// オブジェクトにタイプを指定
	SetType(TYPE_CURSOR);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CCursor::Uninit(void)
{
	// number2Dの終了処理
	if (m_pObject2D != NULL)
	{ // 使用されている場合
		m_pObject2D->Uninit();
		m_pObject2D = NULL;
	}

	// 自分自身の破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CCursor::Update(void)
{
	
}

//=============================
// 描画処理
//=============================
void CCursor::Draw(void)
{
	if (m_bDisp == true)
	{ // 表示状態の場合
		// 位置更新
		CInputMouse* pMouse = CManager::GetInputMouse();
		D3DXVECTOR3 posMouse = pMouse->GetClientPos();
		
		// 位置更新
		m_pObject2D->SetPosition(posMouse);

		// object2Dの描画処理
		m_pObject2D->Draw();
	}
}