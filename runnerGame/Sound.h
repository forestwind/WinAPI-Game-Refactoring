#pragma once
#include "stdafx.h"
#include "Common.h"

class CSound : public Singleton<CSound>
{
public:

	//	사운드 관련 전역변수 및 함수 
	MCI_OPEN_PARMS      mciOpen; //파일을 로드
	MCI_PLAY_PARMS       mciPlay; //파일을 재생
	MCI_STATUS_PARMS   mciStatus; //파일의 상태
	UINT wDeviceID = 0;

	CSound();
	~CSound();
	void Init(HWND& hwnd, HINSTANCE& hInst);
	DWORD LoadWAV(HWND hwnd, LPCTSTR lpszWave);
	DWORD Sound1, Sound2, Sound3, Sound4, Sound5, Sound6, Sound7, Sound8;


	

	

};

