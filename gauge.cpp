//==========================================
// 
// ゲージ処理[gauge.cpp]
// Create : 2026/05/26~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "gauge.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define GAUGE_WIDTH		(static_cast<float>(SCREEN_WIDTH))	// ゲージ横幅
#define GAUGE_HEIGHT	(80.0f)	// ゲージ縦幅
#define GAUGEUI_WIDTH	(704.0f * 0.5f)	// ゲージテキスト幅

//=============================
// 静的メンバ変数宣言
//=============================
const char* CGauge::m_apFilenameType[TYPE_MAX]
{
	"data\\TEXTURE\\gauge\\gauge000.png",	// 背景
	"data\\TEXTURE\\gauge\\gauge001.png",	// ゲージ1
	"data\\TEXTURE\\gauge\\gauge001.png",	// ゲージ2
	"data\\TEXTURE\\gauge\\gauge002.png",	// フレーム
	"data\\TEXTURE\\gauge\\gauge003.png",	// UI
};

//=============================
// 生成処理
//=============================
CGauge* CGauge::Create(D3DXVECTOR3 pos)
{
	CGauge* pGauge = NULL;	// オブジェクトへのポインタを用意
	if (pGauge == NULL)
	{ // NULLが設定できている場合
		pGauge = new CGauge;
		if (pGauge != NULL)
		{ // インスタンス生成に成功した場合
			// 初期化処理
			pGauge->Init(pos);

			return pGauge;
		}
	}
	// インスタンス生成に失敗
	return NULL;
}

//=============================
// コンストラクタ
//=============================
CGauge::CGauge(int nPriority) : CObject(nPriority)
{
	// 頂点バッファの初期化
	m_pVtxBuff = NULL;
	m_pos = INIT_D3DVEC3;
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);
}

//=============================
// デストラクタ
//=============================
CGauge::~CGauge()
{

}

//=============================
// 初期化処理
//=============================
HRESULT CGauge::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	m_pos = pos;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 構造体の初期化
	for (int nCntGauge = 0; nCntGauge < TYPE_MAX; nCntGauge++)
	{
		switch (nCntGauge)
		{
		case TYPE_BG:	// 背景
			m_aGauge[nCntGauge].pos = m_pos;
			m_aGauge[nCntGauge].type = TYPE_BG;
			m_aGauge[nCntGauge].fWidth = GAUGE_WIDTH;
			m_aGauge[nCntGauge].fHeight = GAUGE_HEIGHT * 0.5f;
			m_aGauge[nCntGauge].fTexX = 1.0f;
			m_aGauge[nCntGauge].col = COLOR_WHITE;
			break;

		case TYPE_GAUGE1:	// ゲージ
			m_aGauge[nCntGauge].pos = m_pos;
			m_aGauge[nCntGauge].type = TYPE_GAUGE1;
			m_aGauge[nCntGauge].fWidth = GAUGE_WIDTH;
			m_aGauge[nCntGauge].fHeight = GAUGE_HEIGHT * 0.5f;
			m_aGauge[nCntGauge].fTexX = 1.0f;
			m_aGauge[nCntGauge].col = COLOR_ORANGE;
			break;

		case TYPE_GAUGE2:	// ゲージ
			m_aGauge[nCntGauge].pos = m_pos;
			m_aGauge[nCntGauge].type = TYPE_GAUGE2;
			m_aGauge[nCntGauge].fWidth = 0.0f;
			m_aGauge[nCntGauge].fHeight = GAUGE_HEIGHT * 0.5f;
			m_aGauge[nCntGauge].fTexX = 1.0f;
			m_aGauge[nCntGauge].col = COLOR_RED;
			break;

		case TYPE_FRAME:	// フレーム
			m_aGauge[nCntGauge].pos = m_pos;
			m_aGauge[nCntGauge].type = TYPE_FRAME;
			m_aGauge[nCntGauge].fWidth = GAUGE_WIDTH;
			m_aGauge[nCntGauge].fHeight = GAUGE_HEIGHT * 0.5f;
			m_aGauge[nCntGauge].fTexX = 1.0f;
			m_aGauge[nCntGauge].col = COLOR_WHITE;
			break;

		case TYPE_TEXT:	// テキスト
			m_aGauge[nCntGauge].pos = m_pos;
			m_aGauge[nCntGauge].pos.y -= GAUGE_HEIGHT * 0.5f;
			m_aGauge[nCntGauge].type = TYPE_TEXT;
			m_aGauge[nCntGauge].fWidth = GAUGEUI_WIDTH;
			m_aGauge[nCntGauge].fHeight = GAUGE_HEIGHT * 0.5f;
			m_aGauge[nCntGauge].fTexX = 1.0f;
			m_aGauge[nCntGauge].col = COLOR_WHITE;
			break;
		}

		m_aIdxTexture[nCntGauge] = pTexture->Register(m_apFilenameType[nCntGauge]);
	}

	// 頂点情報更新
	SetVtx();

	SetType(CObject::TYPE_GAUGE);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGauge::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// メモリ破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CGauge::Update(void)
{

}

//=============================
// 描画処理
//=============================
void CGauge::Draw(void)
{
	// デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntGauge = 0; nCntGauge < TYPE_MAX; nCntGauge++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_aIdxTexture[nCntGauge]));
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
	}
}

//=============================
// ゲージの長さを設定
//=============================
void CGauge::SetGauge(float fTexX)
{
	if (fTexX >= 1.0f)
	{
		// テクスチャ読み込み
		m_aGauge[TYPE_GAUGE1].fTexX = 1.0f;

		// 幅設定
		m_aGauge[TYPE_GAUGE1].fWidth = GAUGE_WIDTH;

		// テクスチャ読み込み
		m_aGauge[TYPE_GAUGE2].fTexX = fTexX - 1.0f;

		// 幅設定
		m_aGauge[TYPE_GAUGE2].fWidth = GAUGE_WIDTH * (fTexX - 1.0f);
	}
	else
	{
		// テクスチャ読み込み
		m_aGauge[TYPE_GAUGE1].fTexX = fTexX;

		// 幅設定
		m_aGauge[TYPE_GAUGE1].fWidth = GAUGE_WIDTH * fTexX;

		// テクスチャ読み込み
		m_aGauge[TYPE_GAUGE2].fTexX = 0.0f;

		// 幅設定
		m_aGauge[TYPE_GAUGE2].fWidth = 0.0f;
	}
	// 頂点情報更新
	SetVtx();
}

//=============================
// 頂点情報更新
//=============================
void CGauge::SetVtx(void)
{
	VERTEX_2D* pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGauge = 0; nCntGauge < TYPE_MAX; nCntGauge++, pVtx += 4)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_aGauge[nCntGauge].pos.x, m_aGauge[nCntGauge].pos.y - m_aGauge[nCntGauge].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_aGauge[nCntGauge].pos.x + m_aGauge[nCntGauge].fWidth, m_aGauge[nCntGauge].pos.y - m_aGauge[nCntGauge].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_aGauge[nCntGauge].pos.x, m_aGauge[nCntGauge].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_aGauge[nCntGauge].pos.x + m_aGauge[nCntGauge].fWidth, m_aGauge[nCntGauge].pos.y, 0.0f);


		// 頂点カラーの設定
		pVtx[0].col = m_aGauge[nCntGauge].col;
		pVtx[1].col = m_aGauge[nCntGauge].col;
		pVtx[2].col = m_aGauge[nCntGauge].col;
		pVtx[3].col = m_aGauge[nCntGauge].col;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_aGauge[nCntGauge].fTexX, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_aGauge[nCntGauge].fTexX, 1.0f);
	}
	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
