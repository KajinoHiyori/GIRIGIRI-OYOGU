//==========================================
// 
// オブジェクト処理[object.cpp]
// Create : 2026/05/08~
// 
//==========================================
#include "object.h"
#include "debugproc.h"
#include "manager.h"

//=============================
// 静的メンバ変数宣言
//=============================
int CObject::m_nNumAll = 0;	// 最大数を初期化
CObject* CObject::m_apObject[MAX_PRIORITY][MAX_OBJECT] = {};	// ポインタにNULLを設定

//========================================================================
// コンストラクタ[オーバーロード]
//========================================================================
CObject::CObject(int nPriority)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (m_apObject[nPriority][nCntObj] == NULL)
		{ // もし配列が空だった場合
			m_apObject[nPriority][nCntObj] = this;	// 自身のポインタを格納
			m_nID = nCntObj;			// 自身のIDを設定
			m_type = TYPE_NONE;			// 種類の初期化
			m_nPriority = nPriority;			// 自身の優先順位の初期化
			m_nNumAll++;				// 総数をカウントアップ
			break;
		}
	}
}

//========================================================================
// デストラクタ
//========================================================================
CObject::~CObject()
{

}

//========================================================================
// 全てのオブジェクトを破棄
//========================================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] != NULL)
			{ // 使用されていた場合
				// 終了処理
				m_apObject[nCntPriority][nCntObj]->Uninit();
			}
		}
	}
}

//========================================================================
// 全てのオブジェクトを更新
//========================================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] == NULL) continue;
			// 使用されていた場合更新処理を行う
			m_apObject[nCntPriority][nCntObj]->Update();
		}
	}
}

//========================================================================
// 全てのオブジェクトを描画
//========================================================================
void CObject::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] != NULL)
			{ // 使用されていた場合更新処理を行う
				m_apObject[nCntPriority][nCntObj]->Draw();
			}
		}
	}
}

//========================================================================
// 自分自身を破棄
//========================================================================
void CObject::Release(void)
{
	if (m_apObject[m_nPriority][m_nID] != NULL)
	{ // 使用されていた場合
		int nID = m_nID;				// 自身のIDをローカルで格納
		int nPriority = m_nPriority;	// 自身の優先順位をローカルで格納

		// メモリ破棄
		delete m_apObject[nPriority][nID];
		m_apObject[nPriority][nID] = NULL;
		m_nNumAll--;	// 総数を減少
	}
}

//========================================================================
// オブジェクト取得
//========================================================================
CObject* CObject::GetObject(int nPriority, int nIdx)
{ 
	return m_apObject[nPriority][nIdx]; 
}
