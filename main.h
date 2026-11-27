//==========================================
// 
// メイン処理[main.h]
// Create : 2026/05/08~
// 
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================
// インクルードファイル
//=============================
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"		// D3DXCOLOR型の色指定
#include "d3dx9.h"		// 描画処理に必要
#include "dinput.h"		// 入力処理に必要
#include "xaudio2.h"	// サウンド処理に必要
#include "xinput.h"		// ジョイパッド処理に必要

//=============================
// ライブラリのリンク
//=============================
#pragma comment(lib, "d3d9.lib")	// 描画処理に必要
#pragma comment(lib, "d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	// DirectXコンポーネント(部品)使用に必要
#pragma comment(lib, "winmm.lib")	// システム時刻の取得に必要
#pragma comment(lib, "dinput8.lib")	// 入力処理に必要
#pragma comment(lib, "xinput.lib")	// ジョイパッド処理に必要

//=============================
// マクロ定義
//=============================
#define DIRECTINPUT_VERSION	(0x0800)	// ビルド時の警告対処用マクロ
#define SCREEN_WIDTH	(1280)			// ウィンドウの幅
#define SCREEN_HEIGHT	(720)			// ウィンドウの高さ
					  //  頂点座標2D	   頂点カラー    テクスチャ座標
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット
#define WINDOW_NAME	"GIRIGIRI OYOGU"	// ウィンドウの名前(キャプションに表示)
#define INIT_D3DVEC3	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))	// D3DXVECTOR3型の初期値
#define RAND_POS		(D3DXVECTOR3(static_cast<float>(rand() % SCREEN_WIDTH), static_cast<float>(rand() % SCREEN_HEIGHT), 0.0f))	// ランダムな座標位置[2D]

#define SAFE_UNINIT(pointer)			if (pointer != NULL){pointer->Uninit(); delete pointer; pointer = NULL;}		// Uninit
#define SAFE_UNLOAD(pointer)			if (pointer != NULL){pointer->Unload(); delete pointer; pointer = NULL;}		// Unload
#define SAFE_RELEASE(pointer)			if (pointer != NULL){pointer->Release(); pointer = NULL;}						// Release
#define	SAFE_DELETE_SINGULAR(pointer)	if (pointer != NULL){delete pointer; pointer = NULL;}							// delete
#define	SAFE_DELETE_PLURAL(pointer)		if (pointer != NULL){delete[] pointer; pointer = NULL;}							// delete[]

//=============================
// 頂点情報[2D]の構造体を定義
//=============================
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標(x, y, z)
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー(r, g, b, a)
	D3DXVECTOR2 tex;	// テクスチャ座標(x, y)
}VERTEX_2D;

//=============================
// プロトタイプ宣言
//=============================
float AngleNormalize(float fAngle);
#endif