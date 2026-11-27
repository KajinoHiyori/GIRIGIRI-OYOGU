//==========================================
// 
// ポリゴン処理[polygon2D.h]
// Create : 2026/05/19~
// 
//==========================================
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"

//=============================
// ポリゴンクラス
// オブジェクトを継承せず、
// 必要な場所で処理を呼び出す
//=============================
class CPolygon2D
{
public:
	// アンカーポイントの位置設定
	typedef enum
	{
		LEFT_TOP = 0,	// 左揃え上寄せ
		LEFT_MIDDLE,	// 左揃え中央寄せ
		LEFT_BUTTON,	// 左揃え下寄せ
		CENTER_TOP,		// 中央揃え上寄せ
		CENTER_MIDDLE,	// 中央揃え中央寄せ
		CENTER_BUTTON,	// 中央揃え下寄せ
		RIGHT_TOP,		// 右揃え上寄せ
		RIGHT_MIDDLE,	// 右揃え中央寄せ
		RIGHT_BUTTON,	// 右揃え下寄せ
	}TYPE;

	static CPolygon2D* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, TYPE type = CENTER_MIDDLE);
	CPolygon2D();
	~CPolygon2D();
	void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; SetVtx(); }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetColor(D3DXCOLOR col) { m_col = col; SetVtx(); }
	void SetHeight(float fHeight) { m_fHeight = fHeight;  SetVtx(); }
	void SetWidth(float fWidth) { m_fWidth = fWidth;  SetVtx(); }
	float GetHeight(void) { return m_fHeight; }
	float GetWidth(void) { return m_fWidth; }
	static int GetNumAll(void) { return m_nNumAll; }

private:
	void SetVtx(void);
	int m_nIdxTexture;						// テクスチャのインデックス格納
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	D3DXVECTOR3 m_pos;	// 表示位置
	D3DXCOLOR m_col;	// 表示色
	float m_fWidth;		// 横幅
	float m_fHeight;	// 縦幅
	TYPE m_type;		// 中心座標設定
	static int m_nNumAll;	// 数字の総数
};

#endif

