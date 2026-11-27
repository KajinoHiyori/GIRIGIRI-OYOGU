//==========================================
// 
// マネージャー処理[manager.h]
// Create : 2026/05/12
// 
//==========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"

//=============================
// クラスの前方宣言
//=============================
class CRenderer;		// レンダラークラス
class CInputKeyboard;	// キーボード入力クラス
class CInputMouse;		// マウス入力クラス
class CInputJoypad;		// ジョイパッド入力クラス
class CDebugProc;		// デバッグ表示クラス
class CTexture;			// テクスチャクラス
class CPlayer;			// プレイヤークラス
class CScore;			// スコアクラス
class CTimer;			// タイマークラス
class CGauge;			// ゲージクラス
class CBG;				// 背景クラス
class CStart;			// 開始クラス
class CEnd;				// 終了クラス
class CUI;				// UIクラス
class CCursor;			// カーソルクラス
class CSound;			// サウンドクラス

//=============================
// マネージャークラス定義
//=============================
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Generator(void);
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	static CInputJoypad* GetInputJoypad(void) { return m_pInputJoypad; }
	static CDebugProc* GetDebugProc(void) { return m_pDebugProc; }
	static CTexture* GetTexture(void) { return m_pTexture; }
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CScore* GetScore(void) { return m_pScore; }
	static CBG* GetBG(void) { return m_pBG; }
	static CTimer* GetTimer(void) { return m_pTimer; }
	static CGauge* GetGauge(void) { return m_pGauge; }
	static CSound* GetSound(void) { return m_pSound; }
	static CStart* GetStart(void) { return m_pStart; }
	static CEnd* GetEnd(void) { return m_pEnd; }
	static CCursor* GetCursor(void) { return m_pCursor; }
	static CUI* GetUI(void) { return m_pUI; }
	static bool GetPause(void) { return m_bPause; }
	static bool GetStartState(void) { return m_bStart; }
	static bool GetEndState(void) { return m_bEnd; }
	static void SetEndState(bool bEnd, bool bWin);

private:
	void Load(void);
	void Unload(void);
	void Reload(void);
	static CRenderer* m_pRenderer;				// レンダラーへのポインタ
	static CInputKeyboard* m_pInputKeyboard;	// キーボード入力へのポインタ
	static CInputMouse* m_pInputMouse;			// マウス入力へのポインタ
	static CInputJoypad* m_pInputJoypad;		// ジョイパッド入力へのポインタ
	static CDebugProc* m_pDebugProc;			// デバッグ表示へのポインタ
	static CTexture* m_pTexture;				// テクスチャへのポインタ
	static CPlayer* m_pPlayer;	// プレイヤーへのポインタ
	static CScore* m_pScore;	// スコアへのポインタ
	static CBG* m_pBG;			// 背景へのポインタ
	static CTimer* m_pTimer;	// タイマーへのポインタ
	static CGauge* m_pGauge;	// ゲージへのポインタ
	static CSound* m_pSound;	// サウンドへのポインタ
	static CStart* m_pStart;	// スタートへのポインタ
	static CEnd* m_pEnd;		// 終了へのポインタ
	static CCursor* m_pCursor;	// カーソルへのポインタ
	static CUI* m_pUI;			// UIへのポインタ
	static bool m_bPause;		// ポーズ状態の管理
	static bool m_bStart;		// 開始状態の管理
	static bool m_bEnd;			// 終了状態の管理
	static bool m_bEndOld;		// 過去の終了状態の管理
};

#endif // !_MANAGER_H_

