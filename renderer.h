//==========================================
// 
// レンダラー処理[renderer.h]
// Create : 2026/05/08
// 
//==========================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"

//=============================
// レンダラークラス
//=============================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(const HWND hWnd, const BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice ;}

private:
	//void Init(void);
	//void Uninit(void);
	//void Update(void);
	//void Draw(void);
	LPDIRECT3D9	 m_pD3D;			// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Direct3Dデバイスへのポインタ
};

#endif