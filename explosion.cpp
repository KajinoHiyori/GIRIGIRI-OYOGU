//==========================================
// 
// 爆発処理[explosion.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "explosion.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "debugproc.h"
#include "enemy.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define EXPLOSION_WIDTH		(35.0f)	// プレイヤーの幅
#define EXPLOSION_HEIGHT	(35.0f)	// プレイヤーの高さ
#define EXPLOSION_FRAME		(5)	// 爆発アニメーションのフレーム
#define EXPLOSION_MAX		(8)	// コマ数
#define EXPLOSION_TEXW		(0.125f)	// 読み込み幅
#define EXPLOSION_TEXH		(1.0f)		// 読み込み高さ

//=============================
// 静的メンバ変数宣言
//=============================
const char* CExplosion::m_pFilenameType =
{
	"data\\TEXTURE\\explosion000.png",	// テクスチャ000
};

//=============================
// コンストラクタ
//=============================
CExplosion::CExplosion(int nPriority): CObject2DAnim(nPriority)
{
	m_move = INIT_D3DVEC3;			// 移動量
	m_rot_inertia = INIT_D3DVEC3;	// 向きの慣性
	m_fLength_inertia = 0.0f;		// 拡大縮小の慣性
	m_nIdxTexture = 0;
}

//=============================
// デストラクタ
//=============================
CExplosion::~CExplosion()
{

}

//=============================
// 爆発生成処理
//=============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	CExplosion* pExplosion = NULL;

	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		if (pExplosion != NULL)
		{ // インスタンス生成に成功
			// 初期化処理
			pExplosion->Init(pos, col);

			// アニメーション情報の設定
			pExplosion->SetAnimInfo(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, EXPLOSION_FRAME, EXPLOSION_MAX, EXPLOSION_TEXW, EXPLOSION_TEXH, false);

			
			return pExplosion;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	CTexture* pTexture = CManager::GetTexture();

	// 2Dオブジェクトの初期化
	CObject2DAnim::Init(pos, col);

	// テクスチャの用意
	m_nIdxTexture = pTexture->Register(m_pFilenameType);

	// テクスチャを設定
	BindTexture(m_nIdxTexture);

	// オブジェクトにタイプを指定
	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CExplosion::Uninit(void)
{
	// object2Dの終了処理
	CObject2DAnim::Uninit();
}

//=============================
// 更新処理
//=============================
void CExplosion::Update(void)
{
	// デバッグ表示
	CDebugProc* pDebugProc = CManager::GetDebugProc();

	// アニメーション更新処理
	CObject2DAnim::Update();

	// 終了フラグが立っていれば破棄
	if (GetEnd() == true)
	{ // アニメーションが終了
		Uninit();
	}
}

//=============================
// 描画処理
//=============================
void CExplosion::Draw(void)
{
	// object2Dの描画処理
	CObject2DAnim::Draw();
}
