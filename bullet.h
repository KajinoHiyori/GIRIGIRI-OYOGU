//==========================================
// 
// 弾処理[bullet.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object2D.h"

//=============================
// マクロ定義
//=============================
#define BULLET_SPEED (10.0f)	// 弾速

//=============================
// プレイヤークラス
//=============================
class CBullet : public CObject2D
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_000 = 0,	// テクスチャ000
		TYPE_001,		// テクスチャ001
		TYPE_002,		// テクスチャ002
		TYPE_003,		// テクスチャ003
		TYPE_MAX
	}TYPE;

	CBullet(int nPriority = 2);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, int nLife);
	static int GetNumAll(void) { return m_nNumAll; }

private:
	bool CollisionEnemy(D3DXVECTOR3 pos);
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャ名
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	// 共有テクスチャ
	D3DXVECTOR3 m_move;	// 移動量
	int m_nLife;		// 弾の寿命
	static int m_nNumAll;	// 弾の総数
};

#endif