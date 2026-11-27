//==========================================
// 
// エフェクト処理[effect.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object2D.h"

//=============================
// マクロ定義
//=============================
#define EFFECT_SPEED (10.0f)	// エフェクト速

//=============================
// エフェクトクラス
//=============================
class CEffect : public CObject2D
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_000 = 0,	// テクスチャ000
		TYPE_001,		// テクスチャ001
		TYPE_002,		// テクスチャ001
		TYPE_MAX
	}TYPE;

	CEffect(int nPriority = 5);
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, TYPE type, int nLife, D3DXVECTOR3 rot = INIT_D3DVEC3);
	int GetLife(void) { return m_nLife; }
	static int GetNumAll(void) { return m_nNumAll; }

private:
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャ名
	int m_aIdxTexture[TYPE_MAX];	// 共有テクスチャ
	D3DXVECTOR3 m_move;	// 移動量
	int m_nLife;		// エフェクトの寿命
	static int m_nNumAll;	// エフェクトの総数
};

#endif