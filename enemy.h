//==========================================
// 
// 敵処理[enemy.h]
// Create : 2026/05/19~
// 
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object2D.h"

//=============================
// マクロ定義
//=============================
#define ENEMY_WIDTH		(75.0f)	// 敵の幅
#define ENEMY_HEIGHT	(ENEMY_WIDTH)	// 敵の高さ
#define ENEMY_SIZE		(ENEMY_WIDTH * 0.55f)	// 敵の当たり判定サイズ

//=============================
// 敵クラス
//=============================
class CEnemy : public CObject2D
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_000 = 0,	// テクスチャ000
		TYPE_001,		// テクスチャ001
		TYPE_002,		// テクスチャ002
		TYPE_003,		// テクスチャ002
		TYPE_MAX
	}TYPE;

	// 敵の状態
	typedef enum
	{
		STATE_APPEAR = 0,	// 出現
		STATE_NORMAL,		// 通常
		STATE_MAX
	}STATE;

	CEnemy(int nPriority = 3);
	~CEnemy();
	HRESULT Init(TYPE type, D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	TYPE GetType(void) { return m_type; }
	STATE GetState(void) { return m_state; }
	static CEnemy* Create(D3DXVECTOR3 pos, TYPE type);
	static int GetNumAll(void) { return m_nNumAll; }
	static void Generator(void);
	static void ResetGenerator(void) { m_nGenerator = 0; }

private:
	// テクスチャの読み込み
	static const char* m_apFilenameType[TYPE_MAX];	// テクスチャ名
	int m_nIdxTexture;	// 共有テクスチャ
	static int m_nNumAll;		// 総数
	static int m_nGenerator;	// 自動生成
	D3DXVECTOR3 m_move;			// 移動量
	float m_fSpeed;				// 移動量
	D3DXVECTOR3 m_rot_inertia;	// 向きの慣性
	float m_fLength_inertia;	// 拡大縮小の慣性
	TYPE m_type;	// 敵の種類
	STATE m_state;	// 敵の状態
	int m_nCounterState;	// ステートカウンター
};

#endif // !_ENEMY_H_

