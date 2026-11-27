//==========================================
// 
// スコア処理[score.h]
// Create : 2026/05/18~
// 
//==========================================
//=============================
// インクルードファイル
//=============================
#include "score.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "number2D.h"

//=============================
// マクロ定義
//=============================
#define SCORE_SIZE	(20.0f)	// スコアのサイズ

//=============================
// コンストラクタ
//=============================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	memset(&m_apNumber[0], NULL, sizeof m_apNumber);	// ポインタのクリア
	m_nScore = 0;	// スコア管理の値をクリア
	memset(&m_aTecU[0], 0, sizeof m_aTecU);	// スコアのUV座標を管理
}

//=============================
// デストラクタ
//=============================
CScore::~CScore()
{

}

//=============================
// スコア生成処理
//=============================
CScore* CScore::Create(D3DXVECTOR3 pos, int nScore)
{
	CScore* pScore = NULL;

	if (pScore == NULL)
	{
		pScore = new CScore;
		if (pScore != NULL)
		{ // インスタンス生成に成功
			// 弾の初期化処理
			pScore->Init(pos, nScore);

			return pScore;
		}
	}

	// インスタンス生成に失敗
	return NULL;
}

//=============================
// 初期化処理
//=============================
HRESULT CScore::Init(D3DXVECTOR3 pos, int nScore)
{
	// 表示桁を管理
	SetTexU();

	for (int nCntScore = 0; nCntScore < SCORE_DIGIT; nCntScore++)
	{
		// 数字の用意
		if (m_apNumber[nCntScore] == NULL)
		{ // 初期化が行われている場合
			m_apNumber[nCntScore] = m_apNumber[nCntScore]->Create(D3DXVECTOR3(pos.x + nCntScore * NUMBER_WIDTH, pos.y, pos.z), 0);
		}
		else
		{ // 初期化に失敗
			return E_FAIL;
		}
		// オブジェクトにタイプを指定
		SetType(TYPE_SCORE);
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < SCORE_DIGIT; nCntScore++)
	{
		// number2Dの終了処理
		if (m_apNumber[nCntScore] != NULL)
		{ // 使用されている場合
			m_apNumber[nCntScore]->Uninit();
			delete m_apNumber[nCntScore];
			m_apNumber[nCntScore] = NULL;
		}
	}

	// 自分自身の破棄
	Release();
}

//=============================
// 更新処理
//=============================
void CScore::Update(void)
{
	// 入力情報を取得
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		Add(20);
	}
}

//=============================
// 描画処理
//=============================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < SCORE_DIGIT; nCntScore++)
	{
		// number2Dの描画処理
		m_apNumber[nCntScore]->Draw();
	}
}

//=============================
// 加算処理
//=============================
void CScore::Add(int nAdd)
{
	// スコアを加算
	m_nScore += nAdd;

	// 表示桁を管理
	SetTexU();

	for (int nCntScore = 0; nCntScore < SCORE_DIGIT; nCntScore++)
	{ // 表示状態を変更
		m_apNumber[nCntScore]->SetNum(m_aTecU[nCntScore]);
	}
}

//=============================
// 表示桁を管理
//=============================
void CScore::SetTexU(void)
{
	for (int nCntScore = 0; nCntScore < SCORE_DIGIT; nCntScore++)
	{
		if (nCntScore == SCORE_DIGIT - 1)
		{
			m_aTecU[nCntScore] = m_nScore % 10 / 1;
		}
		else
		{
			float fNumX = powf(static_cast <float>(10), static_cast <float>(SCORE_DIGIT - nCntScore));		// 剰余算
			float fNumY = powf(static_cast <float>(10), static_cast <float>(SCORE_DIGIT - nCntScore - 1));	// 除算
			m_aTecU[nCntScore] = m_nScore % static_cast<int>(fNumX) / static_cast<int>(fNumY);
		}
	}
}
