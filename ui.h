//==========================================
// 
// UI処理[bg.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _UI_H_
#define _UI_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// マクロ定義
//=============================
#define NUM_UI	(2)	// UIのレイヤー数

//=============================
// 前方宣言
//=============================
class CPolygon2D;	// ポリゴン[2D]クラス

//=============================
// UIクラス
//=============================
class CUI : public CObject
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_TIME = 0,	// テクスチャ000
		TYPE_SCORE,	// テクスチャ000
		TYPE_MAX
	}TYPE;

	CUI(int nPriority = 6);
	~CUI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos = INIT_D3DVEC3) {}
	static CUI* Create(void);

private:
	CPolygon2D* m_apObject2D[NUM_UI];	// 2Dオブジェクトへのポインタ
	int m_aIdxTexture[TYPE_MAX];	// テクスチャ
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャ名
};

#endif // !_PLAYER_H_

#pragma once
