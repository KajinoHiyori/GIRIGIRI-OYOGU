//==========================================
// 
// 爆発処理[explosion.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object2DAnim.h"

//=============================
// 爆発クラス
//=============================
class CExplosion : public CObject2DAnim
{
public:
	CExplosion(int nPriority = 2);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXCOLOR col);

private:
	// テクスチャの読み込み
	static const char* m_pFilenameType;	// テクスチャ名
	int m_nIdxTexture;
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_rot_inertia;	// 向きの慣性
	float m_fLength_inertia;	// 拡大縮小の慣性
};

#endif // !_EXPLOSION_H_

