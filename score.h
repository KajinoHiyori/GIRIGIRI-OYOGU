//==========================================
// 
// スコア処理[score.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// マクロ定義
//=============================
#define SCORE_DIGIT	(8)	// スコアの桁数

//=============================
// 前方宣言
//=============================
class CNumber2D;	// 数字[2D]クラス

//=============================
// スコアクラス
//=============================
class CScore : public CObject
{
public:
	CScore(int nPriority = 6);
	~CScore();
	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, int nScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos = INIT_D3DVEC3) {}
	void Add(int nAdd);
	int Get(void) { return m_nScore; }
	static CScore* Create(D3DXVECTOR3 pos, int nScore);

private:
	void SetTexU(void);
	CNumber2D* m_apNumber[SCORE_DIGIT];	// 数字表示へのポインタ
	int m_nScore;	// スコアの値を管理
	int m_aTecU[SCORE_DIGIT];	// スコアのUV座標を設定
};

#endif // !_PLAYER_H_

#pragma once
