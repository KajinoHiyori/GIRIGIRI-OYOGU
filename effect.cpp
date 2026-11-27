//==========================================
// 
// エフェクト処理[effect.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "player.h"
#include "texture.h"

//=============================
// マクロ定義
//=============================
#define EFFECT_SIZE	(20.0f)	// エフェクトのサイズ

//=============================
// 静的メンバ変数宣言
//=============================
const char* CEffect::m_apFilenameType[CEffect::TYPE_MAX] =
{
	"data\\TEXTURE\\effect\\effect000.png",	// テクスチャ000
	"data\\TEXTURE\\effect\\effect001.png",	// テクスチャ001
	"data\\TEXTURE\\effect\\effect002.png",	// テクスチャ002
};
int CEffect::m_nNumAll = 0;

//=============================
// コンストラクタ
//=============================
CEffect::CEffect(int nPriority): CObject2D(nPriority)
{
	// メンバ変数の値をクリア
	m_move = INIT_D3DVEC3;	// 移動量
	m_nLife = 0;			// エフェクトの寿命
	m_nNumAll++;			// エフェクトの総数を加算
	memset(&m_aIdxTexture[0], 0, sizeof m_aIdxTexture);
}

//=============================
// デストラクタ
//=============================
CEffect::~CEffect()
{

}

//=============================
// エフェクト生成処理
//=============================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, TYPE type, int nLife, D3DXVECTOR3 rot)
{
	CEffect* pEffect = NULL;

	if (pEffect == NULL)
	{
		switch (type)
		{
		case TYPE_002:	// 魚用
			pEffect = new CEffect(3);	// インスタンス生成
			break;

		default:
			pEffect = new CEffect;	// インスタンス生成
			break;
		}
		if (pEffect != NULL)
		{ // インスタンス生成に成功
			// エフェクトの初期化処理
			pEffect->Init(pos, type);

			col.a = 0.25f;	// 半透明に設定

			// 色の設定
			pEffect->SetColor(col);

			// 角度の設定
			pEffect->SetRotation(rot);

			// テクスチャを設定
			pEffect->BindTexture((pEffect->m_aIdxTexture[type]));

			// 移動量設定
			pEffect->m_move = move;

			// エフェクトの寿命設定
			pEffect->m_nLife = nLife;

			return pEffect;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CEffect::Init(D3DXVECTOR3 pos, TYPE type)
{
	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャの読み込み
	for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
	{
		m_aIdxTexture[nCntType] = pTexture->Register(m_apFilenameType[nCntType]);
	}

	// 2Dオブジェクトの初期化
	switch (type)
	{
	case TYPE_002:	// 魚用
		CObject2D::Init(pos, PLAYER_SIZE, PLAYER_SIZE);
		break;

	default:
		CObject2D::Init(pos, EFFECT_SIZE, EFFECT_SIZE);
		break;
	}

	// オブジェクトにタイプを指定
	SetType(TYPE_EFFECT);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CEffect::Uninit(void)
{
	m_nNumAll--;

	// object2Dの終了処理
	CObject2D::Uninit();
}

//=============================
// 更新処理
//=============================
void CEffect::Update(void)
{
	// 寿命の更新
	m_nLife--;

	// 移動量の更新
	D3DXVECTOR3 pos = GetPosition() + m_move;

	// 位置情報の更新
	SetPosition(pos);

	// 敵と当たらなかった場合
	if (pos.x < 0.0f || pos.x > SCREEN_WIDTH || pos.y < 0.0f || pos.y > SCREEN_HEIGHT || m_nLife <= 0)
	{ // 画面外処理 || 寿命処理
		// 自身の破棄
		CEffect::Uninit();
	}
}

//=============================
// 描画処理
//=============================
void CEffect::Draw(void)
{
	// デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// object2Dの描画処理
	CObject2D::Draw();
}
