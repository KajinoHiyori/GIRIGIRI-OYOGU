//===============================================
// 
// D3DXCOLOR型の色指定ヘッダー[color.h]
// Author : Kajino Hiyori
// 
//===============================================
#ifndef _COLOR_H_
#define	_COLOR_H_

//================================
// マクロ定義
//================================
#define COL_MAX				(1000)		// 色の最大数
#define RAND_COLOR			((float)(rand() % COL_MAX) / COL_MAX)	// 配色のランダム
#define COLOR_WHITE			(D3DXCOLOR(1.000f,	1.000f,	1.000f,	1.000f))	// 白
#define COLOR_WHITE_ALPHA	(D3DXCOLOR(1.000f,	1.000f,	1.000f,	0.500f))	// アルファ値半減白
#define COLOR_WHITE_ALPHA75	(D3DXCOLOR(1.000f,	1.000f,	1.000f,	0.750f))	// アルファ値75白
#define COLOR_BLACK			(D3DXCOLOR(0.000f,	0.000f,	0.000f,	1.000f))	// 黒
#define COLOR_RED			(D3DXCOLOR(1.000f,	0.000f,	0.000f,	1.000f))	// 赤
#define COLOR_GREEN			(D3DXCOLOR(0.000f,	1.000f,	0.000f,	1.000f))	// 緑
#define COLOR_BLUE			(D3DXCOLOR(0.000f,	0.000f,	1.000f,	1.000f))	// 青
#define COLOR_DARKBLUE		(D3DXCOLOR(0.000f,	0.000f,	0.450f,	1.000f))	// 紺
#define COLOR_LIGHTBLUE		(D3DXCOLOR(0.450f,	0.450f,	1.000f,	1.000f))	// 水色
#define COLOR_YELLOW		(D3DXCOLOR(1.000f,	1.000f,	0.000f,	1.000f))	// 黄
#define COLOR_CYAN			(D3DXCOLOR(0.000f,	1.000f,	1.000f,	1.000f))	// シアン
#define COLOR_CYAN_ALPHA	(D3DXCOLOR(0.000f,	1.000f,	1.000f,	0.500f))	// アルファ値半減シアン
#define COLOR_MAGENTA		(D3DXCOLOR(1.000f,	0.000f,	1.000f,	1.000f))	// マゼンタ
#define COLOR_ORANGE		(D3DXCOLOR(1.000f,	0.500f, 0.000f, 1.000f))	// オレンジ
#define COLOR_ORANGE_ALPHA	(D3DXCOLOR(1.000f,	0.500f, 0.000f, 0.500f))	// アルファ値半減オレンジ
#define COLOR_VIOLET		(D3DXCOLOR(0.478f,	0.003f,	0.831f,	1.000f))	// バイオレット
#define COLOR_LIGHTGRAY		(D3DXCOLOR(0.678f,	0.678f,	0.678f,	1.000f))	// 明るい灰色
#endif