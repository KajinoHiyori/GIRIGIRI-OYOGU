//==========================================
// 
// ゲージ処理[gauge.h]
// Create : 2026/05/26~
// 
//==========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// ゲージクラス
//=============================
class CGauge : public CObject
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_BG = 0,	// 背景
		TYPE_GAUGE1,	// ゲージ1
		TYPE_GAUGE2,	// ゲージ2
		TYPE_FRAME,		// フレーム
		TYPE_TEXT,		// 文字表記
		TYPE_MAX
	}TYPE;

	CGauge(int nPriority = 6);
	~CGauge();
	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge* Create(D3DXVECTOR3 pos);
	void SetGauge(float fTexX);
	void SetPosition(D3DXVECTOR3) {}

private:
	void SetVtx(void);
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャファイル名
	int m_aIdxTexture[TYPE_MAX];	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファ
	// 各ポリゴンごとの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		TYPE type;			// 種類
		float fWidth;		// 幅
		float fHeight;		// 高さ
		float fTexX;		// テクスチャ読み込み幅
		D3DXCOLOR col;		// 色
	}GAUGE;
	GAUGE m_aGauge[TYPE_MAX];	// ポリゴン管理
	D3DXVECTOR3 m_pos;			// 位置
};

#endif // !_GAUGE_H_
