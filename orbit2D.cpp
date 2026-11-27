//==========================================
// 
// オービット処理[orbit2D.h]
// Create : 2026/05/19~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "orbit2D.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//=============================
// マクロ定義
//=============================
#define ALPHA_CHANGE	(0.02f)	// アルファ値変更

//=============================
// 静的メンバ変数宣言
//=============================
int COrbit2D::m_nNumAll = 0;

//=============================
// コンストラクタ
//=============================
COrbit2D::COrbit2D()
{
	// 値のクリア
	m_pVtxBuff = NULL;		// 頂点バッファのクリア
	m_pIdxBuff = NULL;		// インデックスバッファのクリア
	m_pos = INIT_D3DVEC3;	// 発生基準位置
	memset(&m_posOffset[0], 0, sizeof m_posOffset);	// 表示位置
	memset(&m_posPoint[0], 0, sizeof m_posPoint);	// オービット位置
	m_col[0] = COLOR_WHITE;	// 表示色
	m_col[1] = COLOR_WHITE;	// 表示色
}

//=============================
// デストラクタ
//=============================
COrbit2D::~COrbit2D()
{

}

//=============================
// オービット生成処理
//=============================
COrbit2D* COrbit2D::Create(D3DXVECTOR3 pos, D3DXCOLOR colTop, D3DXCOLOR colDown, D3DXVECTOR3 rot, float fAngle, float fLength)
{
	COrbit2D* pOrbit2D = NULL;	// オブジェクトへのポインタを用意
	if (pOrbit2D == NULL)
	{ // NULLが設定できている場合
		pOrbit2D = new COrbit2D;
		if (pOrbit2D != NULL)
		{ // インスタンス生成に成功した場合
			// 初期化処理
			pOrbit2D->Init(pos, colTop, colDown, rot, fAngle, fLength);

			return pOrbit2D;
		}
	}
	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理[オーバーロード]
//=============================
HRESULT COrbit2D::Init(D3DXVECTOR3 pos, D3DXCOLOR colTop, D3DXCOLOR colDown, D3DXVECTOR3 rot, float fAngle, float fLength)
{
	// レンダラーの取得
	CRenderer* pRenderer = CManager::GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 表示状態の設定
	m_pos = pos;	// 表示位置
	m_col[0] = colTop;	// 色
	m_col[1] = colDown;	// 色
	m_rot = rot;	// 角度
	m_fAngle = fAngle;	// 対角線
	m_fLength = fLength;	// 対角線の長さ
	
	for (int nOrbit = 0; nOrbit < MAX_ORBIT / 2; nOrbit += 2)
	{
		// 位置設定
		m_posPoint[nOrbit].x = pos.x;
		m_posPoint[nOrbit].y = pos.y;
		m_posPoint[nOrbit].z = 0.0f;
		m_posPoint[nOrbit + 1].x = pos.x;
		m_posPoint[nOrbit + 1].y = pos.y;
		m_posPoint[nOrbit + 1].z = 0.0f;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_ORBIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_ORBIT, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);

	// 色設定
	SetColor(COLOR_WHITE, COLOR_WHITE);

	// 表示位置更新
	SetVtx();

	// インデックスバッファ更新
	SetIdx();

	if (m_pVtxBuff != NULL)
	{
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}

//=============================
// 終了処理
//=============================
void COrbit2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{ // 頂点バッファが設定されていた場合
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{ // インデックスバッファが設定されていた場合
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	m_nNumAll--;	// 表示数を減算
}

//=============================
// 更新処理
//=============================
void COrbit2D::Update(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;

	D3DXVECTOR3 posLocal[MAX_ORBIT] = {};

	// 位置変更
	m_posPoint[0].x = m_pos.x - sinf(-m_rot.z + m_fAngle) * m_fLength;
	m_posPoint[0].y = m_pos.y - cosf(-m_rot.z + m_fAngle) * m_fLength;
	m_posPoint[0].z = 0.0f;
	m_posPoint[1].x = m_pos.x - sinf(m_rot.z + m_fAngle) * m_fLength;
	m_posPoint[1].y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	m_posPoint[1].z = 0.0f;

	// 2つ前の頂点情報を格納
	for (int nOrbit = MAX_ORBIT - 1; nOrbit >= 3; nOrbit -= 2)
	{
		// 頂点情報
		m_posPoint[nOrbit] = m_posPoint[nOrbit - 2];
		m_posPoint[nOrbit - 1] = m_posPoint[nOrbit - 3];
		m_posPoint[nOrbit] = m_posPoint[nOrbit - 2];
		m_posPoint[nOrbit - 1] = m_posPoint[nOrbit - 3];
	}

	// 頂点情報更新
	SetVtx();

	CDebugProc* pDebug = CManager::GetDebugProc();
	int nSize = sizeof(m_pVtxBuff);
	pDebug->Print("メッシュオービットのサイズ : %d\n", nSize);
}

//=============================
// 描画処理
//=============================
void COrbit2D::Draw(void)
{
	// デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_ORBIT, 0, MAX_ORBIT - 2);
}

//=============================
// 色の設定
//=============================
void COrbit2D::SetColor(D3DXCOLOR colTop, D3DXCOLOR colDown)
{
	m_col[0] = colTop;	// 色
	m_col[1] = colDown;	// 色

	// 色の変更
	m_colPoint[0] = m_col[0];
	m_colPoint[1] = m_col[1];

	for (int nOrbit = MAX_ORBIT - 1; nOrbit >= 3; nOrbit -= 2)
	{
		// 色情報
		m_colPoint[nOrbit] = m_colPoint[nOrbit - 2];
		m_colPoint[nOrbit].a = 1.0f - (float)nOrbit * ALPHA_CHANGE;
		m_colPoint[nOrbit - 1] = m_colPoint[nOrbit - 3];
		m_colPoint[nOrbit - 1].a = 1.0f - (float)nOrbit * ALPHA_CHANGE;
		if (m_colPoint[nOrbit].a <= 0.0f)
		{
			m_colPoint[nOrbit].a = 0.0f;
		}
		if (m_colPoint[nOrbit - 1].a <= 0.0f)
		{
			m_colPoint[nOrbit - 1].a = 0.0f;
		}
	}

	VERTEX_2D* pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nOrbit = 0; nOrbit < MAX_ORBIT; nOrbit++, pVtx++)
	{
		// 色の設定
		pVtx[0].col = m_colPoint[nOrbit];
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================
// 頂点バッファの更新
//=============================
void COrbit2D::SetVtx(void)
{
	VERTEX_2D* pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nOrbit = 0; nOrbit < MAX_ORBIT; nOrbit++, pVtx++)
	{
		// 位置設定
		pVtx[0].pos = m_posPoint[nOrbit];

		// rhwの設定
		pVtx[0].rhw = 1.0f;

		// 色の設定
		pVtx[0].col = m_colPoint[nOrbit];

		// テクスチャ座標の設定
		float fTexU = nOrbit % 2;
		pVtx[0].tex = D3DXVECTOR2(nOrbit, fTexU);
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================
// インデックスバッファの更新
//=============================
void COrbit2D::SetIdx(void)
{
	WORD* pIdx;
	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nIdx = MAX_ORBIT - 1; nIdx > 1; nIdx--)
	{
		pIdx[nIdx] = static_cast<WORD>(nIdx);
	}

	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();
}