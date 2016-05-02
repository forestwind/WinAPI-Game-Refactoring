#include "Sound.h"

CSound::CSound()
{
}

CSound::~CSound()
{
}

void CSound::Init(HWND& hwnd, HINSTANCE& hInst)
{
	Sound1 = LoadWAV(hwnd, "배경음.mp3");
	Sound2 = LoadWAV(hwnd, "게임화면.mp3");
	Sound3 = LoadWAV(hwnd, "Gun Shot 01.mp3");
	Sound4 = LoadWAV(hwnd, "Mobile Suit Destroyed.mp3");
	Sound5 = LoadWAV(hwnd, "Mech Movement 10.mp3");
	Sound6 = LoadWAV(hwnd, "Mech Transformation 03.mp3");
	Sound7 = LoadWAV(hwnd, "Intro Taunt.wav");
	Sound8 = LoadWAV(hwnd, "아이템.mp3");

	Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
}

DWORD CSound::LoadWAV(HWND hwnd, LPCTSTR lpszWave)
{
	DWORD Result;
	mciOpen.lpstrDeviceType = "MPEGVideo";
	mciOpen.lpstrElementName = lpszWave;
	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);
	if (Result)
		return Result;
	wDeviceID = mciOpen.wDeviceID;
	mciPlay.dwCallback = (DWORD)hwnd;
	if (Result)
		return Result;
	return 0;
}