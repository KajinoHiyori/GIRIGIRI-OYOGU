//==========================================
// 
// カーソル処理[cursor.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// 前方宣言
//=============================
class CPolygon2D;

//=============================
// マクロ定義
//=============================
#define CURSOR_WIDTH		(75.0f)	// カーソルの幅
#define CURSOR_HEIGHT		(CURSOR_WIDTH)	// カーソルの高さ
#define CURSOR_SIZE			(CURSOR_WIDTH * 0.6f)	// カーソルの当たり判定サイズ

//=============================
// カーソルクラス
//=============================
class CCursor : public CObject
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_000 = 0,	// テクスチャ000
		TYPE_MAX
	}TYPE;
	static CCursor* Create(void);
	CCursor(int nPriority = 5);
	~CCursor();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos) {}
	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	bool GetDisp(void) { return m_bDisp; }

private:
	CPolygon2D* m_pObject2D;	// ポリゴンへのポインタ
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャ名
	int m_aIdxTexture[TYPE_MAX];	// テクスチャのインデックス
	bool m_bDisp;	// 表示状態
};

#endif // !_CURSOR_H_

