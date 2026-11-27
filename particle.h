//==========================================
// 
// パーティクル処理[particle.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// マクロ定義
//=============================
#define MAX_EFFECT	(512)	// パーティクルの桁数

//=============================
// 前方宣言
//=============================
//class CEffect2D;	// エフェクト[2D]クラス
class CEffect;

//=============================
// パーティクルクラス
//=============================
class CParticle : public CObject
{
public:
	typedef enum
	{
		TYPE_FIREFLOWER = 0,	// 花火型
		TYPE_RANDCOL,			// 色ランダム[花火型]
		TYPE_MAX
	}TYPE;

	// レンダーステート
	typedef enum
	{
		RENDERSTATE_NORMAL = 0,	// 通常
		RENDERSTATE_ALPHA,		// 加算合成
		RENDERSTATE_MAX
	}RENDERSTATE;

	CParticle(int nPriority = 5);
	~CParticle();
	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos) {}
	static CParticle* Create(D3DXVECTOR3 pos, TYPE type, D3DXCOLOR col, int nLife);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	//CEffect2D* m_apEffect[MAX_EFFECT];	// エフェクトへのポインタ
	CEffect* m_apEffect[MAX_EFFECT];
	D3DXVECTOR3 m_pos;	// 位置
	D3DXCOLOR m_col;	// 色
	TYPE m_type;		// 種類
	int m_nLife;	// 寿命
	int m_nMax;		// 1フレーム当たりの最大数
};

#endif // !_PLAYER_H_

#pragma once
