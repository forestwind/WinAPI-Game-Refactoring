#pragma once
#include "stdafx.h"
#include "Common.h"

class CSound : public Singleton<CSound>
{
public:

	//	���� ���� �������� �� �Լ� 
	MCI_OPEN_PARMS      mciOpen; //������ �ε�
	MCI_PLAY_PARMS       mciPlay; //������ ���
	MCI_STATUS_PARMS   mciStatus; //������ ����
	UINT wDeviceID = 0;

	CSound();
	~CSound();
	void Init(HWND& hwnd, HINSTANCE& hInst);
	DWORD LoadWAV(HWND hwnd, LPCTSTR lpszWave);
	DWORD Sound1, Sound2, Sound3, Sound4, Sound5, Sound6, Sound7, Sound8;


	

	

};

