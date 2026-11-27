//==========================================
// 
// 終了管理処理[end.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _END_H_
#define _END_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// マクロ定義
//=============================
#define NUM_END	(1)	// 終了管理のレイヤー数

//=============================
// 前方宣言
//=============================
class CPolygon2D;	// ポリゴン[2D]クラス

//=============================
// 終了管理クラス
//=============================
class CEnd : public CObject
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_WIN = 0,	// 勝利
		TYPE_LOSE,		// 敗北
		TYPE_MAX
	}TYPE;

	CEnd(int nPriority = 0);
	~CEnd();
	HRESULT Init(void) { return S_OK; }
	HRESULT Init(TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos = INIT_D3DVEC3) {}
	static CEnd* Create(TYPE type);

private:
	CPolygon2D* m_apObject2D[NUM_END];	// 2Dオブジェクトへのポインタ
	int m_aIdxTexture[TYPE_MAX];	// 共有テクスチャ
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャ名
};

#endif // !_PLAYER_H_
