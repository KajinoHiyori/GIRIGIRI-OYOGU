//==========================================
// 
// 背景処理[bg.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _BG_H_
#define _BG_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// マクロ定義
//=============================
#define NUM_BG	(TYPE_MAX)	// 背景のレイヤー数

//=============================
// 前方宣言
//=============================
class CPolygon2D;	// ポリゴン[2D]クラス

//=============================
// 背景クラス
//=============================
class CBG : public CObject
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_DARKBLUE = 0,	// 紺
		TYPE_BLUE,			// 青
		TYPE_LIGHTBLUE,		// 水
		TYPE_TEXTURE,		// テクスチャ000
		TYPE_MAX
	}TYPE;

	CBG(int nPriority = 0);
	~CBG();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos = INIT_D3DVEC3) {}
	static CBG* Create(void);

private:
	CPolygon2D* m_apObject2D[NUM_BG];	// 2Dオブジェクトへのポインタ
	int m_nIdxTexture;	// テクスチャのインデックス
	static const char* m_pFilenameType;		// テクスチャ名
};

#endif // !_PLAYER_H_

#pragma once
