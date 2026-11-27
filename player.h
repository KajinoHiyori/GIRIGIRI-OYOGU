//==========================================
// 
// プレイヤー処理[player.h]
// Create : 2026/05/18~
// 
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"
#include "object2D.h"

//=============================
// マクロ定義
//=============================
#define PLAYER_WIDTH		(75.0f)	// プレイヤーの幅
#define PLAYER_HEIGHT		(PLAYER_WIDTH)	// プレイヤーの高さ
#define PLAYER_SIZE			(PLAYER_WIDTH * 0.55f)	// プレイヤーの当たり判定サイズ
//=============================
// 前方宣言
//=============================
class COrbit2D;	// オービット2Dクラス

//=============================
// プレイヤークラス
//=============================
class CPlayer : public CObject2D
{
public:
	// テクスチャの種類
	typedef enum
	{
		TYPE_NORMAL = 0,	// テクスチャ000
		TYPE_PRESS,		// テクスチャ001
		TYPE_MAX
	}TYPE;
	static CPlayer* Create(D3DXVECTOR3 pos, TYPE type);
	CPlayer(int nPriority = 4);
	~CPlayer();
	HRESULT Init(TYPE type, D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetSpeed(void) { return m_fSpeed; }
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

private:
	bool CollisionEnemy(D3DXVECTOR3 pos);
	static const char* m_apFilenameType[TYPE_MAX];	// テクスチャ名
	int m_aIdxTexture[TYPE_MAX];			// テクスチャインデックス
	D3DXVECTOR3 m_posDest;		// 目的地
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_rot_inertia;	// 向きの慣性
	float m_fLength_inertia;	// 拡大縮小の慣性
	float m_fSpeed;				// 移動速度
	int m_nMousePress;			// マウスを押せる時間をカウント
	bool m_bCillision;			// 衝突判定を管理
	bool m_bCillisionOld;		// 過去の衝突判定を管理
	bool m_bHit;				// 衝突
	TYPE m_type;				// テクスチャの種類を管理
	COrbit2D* m_pOrbit;			// オービット
};

#endif // !_PLAYER_H_

