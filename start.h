//==========================================
// 
// 開始管理処理[start.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _START_H_
#define _START_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object.h"

//=============================
// マクロ定義
//=============================
#define NUM_START	(1)	// 開始管理のレイヤー数

//=============================
// 前方宣言
//=============================
class CPolygon2D;	// オブジェクト[2D]クラス

//=============================
// 開始管理クラス
//=============================
class CStart : public CObject
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_000 = 0,	// テクスチャ000
		TYPE_MAX
	}TYPE;

	CStart(int nPriority = 0);
	~CStart();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos = INIT_D3DVEC3) {}
	static CStart* Create(void);

private:
	CPolygon2D* m_apObject2D[NUM_START];		// 2Dポリゴンへのポインタ
	int m_aIdxTexture[TYPE_MAX];				// テクスチャインデックス
	static const char* m_apFilenameType[TYPE_MAX];		// テクスチャ名
};

#endif // !_PLAYER_H_
