//==========================================
// 
// パーティクル処理[particle.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "particle.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "number2D.h"
//#include "effect2D.h"
#include "effect.h"
#include "debugproc.h"

//=============================
// マクロ定義
//=============================
#define FIREFLOWER_MAX	(1)		// 1フレーム当たりの最大数[花火型]
#define FIREFLOWER_LIFE	(60)	// パーティクルの寿命[花火型]
#define FIREFLOWER_POS	(10.0f)	// 発生位置の設定[花火型]
#define EFFECT_LIFE		(30)	// エフェクトの寿命
#define MOVE_PARTICLE		(10)		// パーティクル移動量のランダム数
#define MOVE_ADJUST			(1.0f)		// 移動量の値を指定
#define MOVE_MIN			(4.0f)		// 最低限の移動量
#define ANGLE_DOUBLE		(629)		// 角度の最大数(*2)
#define MAX_ANGLE			(314)		// 角度の最大数
#define ANGLE_ADJUST		(100.0f)	// 角度の値を指定

// 独立したCEffect2Dを利用する場合
#if 0
//=============================
// コンストラクタ
//=============================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apEffect[0], NULL, sizeof m_apEffect);	// ポインタのクリア
	m_nLife = 0;	// パーティクル管理の値をクリア
	m_nMax = 0;  // 1フレーム当たりの最大数をクリア
}

//=============================
// デストラクタ
//=============================
CParticle::~CParticle()
{

}

//=============================
// パーティクル生成処理
//=============================
CParticle* CParticle::Create(D3DXVECTOR3 pos, TYPE type)
{
	CParticle* pParticle = NULL;

	if (pParticle == NULL)
	{
		pParticle = new CParticle;
		if (pParticle != NULL)
		{ // インスタンス生成に成功
			// 1フレーム当たりの最大数を設定
			switch (type)
			{
			case TYPE_FIREFLOWER:	// 花火型
				pParticle->m_nMax = FIREFLOWER_MAX;
				pParticle->m_nLife = FIREFLOWER_LIFE;	// パーティクルの寿命
				break;
			}

			// パーティクルの初期化処理
			pParticle->Init(pos, type);

			return pParticle;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CParticle::Init(D3DXVECTOR3 pos, TYPE type)
{
	int nCntEffect = 0;	// エフェクトの用意
	// 設定位置の保存
	m_pos = pos;

	D3DXVECTOR3 posLocal = INIT_D3DVEC3;	// ローカルで位置保存

	SetType(TYPE_PARTICLE);	// テクスチャの設定

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CParticle::Uninit(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		// number2Dの終了処理
		if (m_apEffect[nCntParticle] != NULL)
		{ // 使用されている場合
			m_apEffect[nCntParticle]->Uninit();
			delete m_apEffect[nCntParticle];
			m_apEffect[nCntParticle] = NULL;
		}
		// 自分自身の破棄
		Release();
	}
}

//=============================
// 更新処理
//=============================
void CParticle::Update(void)
{
	static int nCnt = 0;

	m_nLife--;	// 寿命の減少

	CDebugProc* pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\nパーティクルの寿命 : %d\n", m_nLife);

	D3DXVECTOR3 pos = INIT_D3DVEC3;	// 発生位置の設定
	// エフェクトの用意
	int nCntEffect = 0;	// エフェクト数の計算

	for (int nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		if (m_apEffect[nCntParticle] == NULL && m_nLife > 0)
		{ // 初期化が行われている&&寿命が残っている
			pos = m_pos;
			pos.x += sinf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * FIREFLOWER_POS;
			pos.y += cosf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * FIREFLOWER_POS;
			D3DXVECTOR3 move = INIT_D3DVEC3;	// 移動量の設定
			move.x = sinf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * MOVE_MIN;	// 移動量X
			move.y = cosf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * MOVE_MIN;	// 移動量Y
			move.z = 0.0f;
			m_apEffect[nCntParticle] = m_apEffect[nCntParticle]->Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move, CEffect2D::TYPE_SQUARE, EFFECT_LIFE);
			nCntEffect++;	// 1フレーム当たりの生成数をカウント

			if (nCntEffect > m_nMax)
			{ // 規定値を越えたら処理を抜ける
				break;
			}
		}
	}

	nCnt++;
	pDebugProc->Print("フレーム : %d\n", nCnt);
	nCntEffect = 0;
	// エフェクトの更新
	for (int nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		if (m_apEffect[nCntParticle] != NULL)
		{
			// 寿命が切れるなどして破棄された場合、NULLが帰ってくる
			m_apEffect[nCntParticle] = m_apEffect[nCntParticle]->Update();
			if (m_apEffect[nCntParticle] != NULL)
			{ // 継続して使用されている
				nCntEffect++;
			}
		}
	}

	if (nCntEffect == 0 && m_nLife <= 0)
	{ // 全てのエフェクトが破棄&&生成を辞めた
		Uninit();
	}
}

//=============================
// 描画処理
//=============================
void CParticle::Draw(void)
{
	// デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// エフェクトの描画
	for (int nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		if (m_apEffect[nCntParticle] != NULL)
		{
			m_apEffect[nCntParticle]->Draw();
		}
	}

	// アルファブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
#endif

// CObject2Dを継承したeffectを利用した場合
//=============================
// コンストラクタ
//=============================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apEffect[0], NULL, sizeof m_apEffect);	// ポインタのクリア
	m_nLife = 0;	// パーティクル管理の値をクリア
	m_nMax = 0;  // 1フレーム当たりの最大数をクリア
	m_col = COLOR_WHITE;	// 色指定
	m_type = TYPE_FIREFLOWER;	// 種類
}

//=============================
// デストラクタ
//=============================
CParticle::~CParticle()
{

}

//=============================
// パーティクル生成処理
//=============================
CParticle* CParticle::Create(D3DXVECTOR3 pos, TYPE type, D3DXCOLOR col, int nLife)
{
	CParticle* pParticle = NULL;

	if (pParticle == NULL)
	{
		pParticle = new CParticle;
		if (pParticle != NULL)
		{ // インスタンス生成に成功
			// 1フレーム当たりの最大数を設定
			switch (type)
			{
			case TYPE_FIREFLOWER:	// 花火型
				pParticle->m_nMax = FIREFLOWER_MAX;	// 最大数設定
				pParticle->m_nLife = nLife;	// パーティクルの寿命
				pParticle->m_col = col;	// 色指定
				break;

			case TYPE_RANDCOL:	// 色ランダム
				pParticle->m_nMax = FIREFLOWER_MAX;	// 最大数設定
				pParticle->m_nLife = nLife;	// パーティクルの寿命
				pParticle->m_col = col;	// 色指定
				break;
			}

			// パーティクルの初期化処理
			pParticle->Init(pos, type);

			return pParticle;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CParticle::Init(D3DXVECTOR3 pos, TYPE type)
{
	int nCntEffect = 0;	// エフェクトの用意
	// 設定位置の保存
	m_pos = pos;

	D3DXVECTOR3 posLocal = INIT_D3DVEC3;	// ローカルで位置保存
	m_type = type;	// 種類格納

	SetType(TYPE_PARTICLE);	// テクスチャの設定

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CParticle::Uninit(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		// number2Dの終了処理
		if (m_apEffect[nCntParticle] != NULL)
		{ // 使用されている場合
			m_apEffect[nCntParticle] = NULL;
		}
	}

	// 自分自身の破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CParticle::Update(void)
{
	m_nLife--;	// 寿命の減少

	CDebugProc* pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\nパーティクルの寿命 : %d\n", m_nLife);

	if (m_nLife <= 0)
	{ // 寿命が尽きた
		// 終了処理
		Uninit();
		return;	// 早期リターン
	}

	D3DXVECTOR3 pos = INIT_D3DVEC3;	// 発生位置の設定
	// エフェクトの用意
	int nCntEffect = 0;	// エフェクト数の計算

	for (int nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		D3DXCOLOR col = COLOR_WHITE;	// 色指定

		if (m_apEffect[nCntParticle] == NULL)
		{ // 初期化が行われている&&寿命が残っている
			// 位置、移動量設定
			pos = m_pos;
			pos.x += sinf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * FIREFLOWER_POS;
			pos.y += cosf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * FIREFLOWER_POS;
			D3DXVECTOR3 move = INIT_D3DVEC3;	// 移動量の設定
			move.x = sinf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * MOVE_MIN;	// 移動量X
			move.y = cosf((float)(rand() % ANGLE_DOUBLE - MAX_ANGLE) / ANGLE_ADJUST) * MOVE_MIN;	// 移動量Y
			move.z = 0.0f;
			
			switch (m_type)
			{
			case TYPE_RANDCOL:	// 色ランダム
				col.r = RAND_COLOR;
				col.g = RAND_COLOR;
				col.b = RAND_COLOR;
				col.a = 1.0f;
				m_apEffect[nCntParticle] = m_apEffect[nCntParticle]->Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move, col, CEffect::TYPE_001, EFFECT_LIFE);
				break;

			default:
				col = m_col;
				m_apEffect[nCntParticle] = m_apEffect[nCntParticle]->Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move, col, CEffect::TYPE_000, EFFECT_LIFE);
				break;
			}
			
			nCntEffect++;	// 1フレーム当たりの生成数をカウント

			if (nCntEffect > m_nMax)
			{ // 規定値を越えたら処理を抜ける
				break;
			}
		}
	}
}

//=============================
// 描画処理
//=============================
void CParticle::Draw(void)
{

}
