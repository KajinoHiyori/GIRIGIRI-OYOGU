//==========================================
// 
// オブジェクト処理[object.h]
// Create : 2026/05/08
// 
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"

//=============================
// マクロ定義
//=============================
#define MAX_OBJECT		(1024)	// オブジェクト最大数
#define MAX_PRIORITY	(8)		// 優先順位最大数

//=============================
// オブジェクトクラス
//=============================
class CObject 
{
public:
	// オブジェクトの種類
	typedef enum
	{
		TYPE_NONE = 0,	// 初期化
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,		// 敵
		TYPE_BULLET,	// 弾
		TYPE_EXPLOSION,	// 爆発
		TYPE_EFFECT,	// エフェクト
		TYPE_BG,		// 背景
		TYPE_PARTICLE,	// パーティクル
		TYPE_ENERGY,	// エナジー
		TYPE_SCORE,		// スコア
		TYPE_TIMER,		// タイマー
		TYPE_GAUGE,		// ゲージ
		TYPE_START,		// 開始処理
		TYPE_END,		// 終了処理
		TYPE_UI,		// UI
		TYPE_CURSOR,	// カーソル
		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNumAll(void) { return m_nNumAll; }
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }
	static CObject* GetObject(int nPriority, int nIdx);

protected:
	void Release(void);

private:
	static CObject* m_apObject[MAX_PRIORITY][MAX_OBJECT];	// オブジェクトへのポインタ
	static int m_nNumAll;	// 総数を格納
	int m_nID;			// 自身のIDを格納
	int m_nPriority;	// 自身の優先順位を格納
	TYPE m_type;		// オブジェクトの種類を格納
};

#endif