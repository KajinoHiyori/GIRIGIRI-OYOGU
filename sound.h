//===========================================================================================
//
// サウンド処理 [sound.h]
// Author : Kajino Hiyori
//
//===========================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================
// インクルードファイル
//=============================
#include "main.h"

//=============================
// サウンドクラス
//=============================
class CSound
{
public:
	// サウンドの種類
	typedef enum
	{
		BGM,			// BGM
		SE_ENTER,		// Enter
		SE_ENEMYAPPEAR,	// 敵出現
		SE_PRESSEFFECT,	// キラキラ 
		SE_DAMAGE,		// ダメージ
		SE_BEEP,		// ビープ音 
		SE_RECOVER,		// ゲージ回復
		SE_COLLISION,	// 衝突
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// サウンド構造体
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	} SOUNDINFO;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
	static SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];					// サウンド構造体
};
#endif
