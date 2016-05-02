#include "stdafx.h"
#include "GameManager.h"
#include "Sound.h"

//////////////////전역변수 선언구간 ////////////////////////////////////////
HINSTANCE g_hInst;


///////////////////////함수선언구간/////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)

{
	HWND hwnd;
	MSG	msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	WndClass.lpszClassName = "Window Class Name";
	RegisterClass(&WndClass);
	hwnd = CreateWindow("Window Class Name",
		"Window Title Name",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1200,
		800,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc,memdc1,memdc2;
	PAINTSTRUCT ps;
	static HBITMAP hbit1;
	static RECT rectview;
	static int mx, my;					//마우스 좌표
	static UserHbit userHbit;

	
	switch (iMsg)
	{
	case WM_CREATE:
	
		CGameManager::GetInstance()->Init(hwnd, g_hInst, userHbit);
		CSound::GetInstance()->Init(hwnd, g_hInst);
		SetTimer(hwnd, 1, 10, NULL);
		break;

	case WM_TIMER:

		//  게임 로직 구간 (더블 버퍼링 포함)
		CGameManager::GetInstance()->isEndgame();
		CGameManager::GetInstance()->Render(hwnd, hdc, memdc1, memdc2, hbit1,userHbit, rectview);
		CGameManager::GetInstance()->Update();
		CGameManager::GetInstance()->InputKeyboard();
	
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rectview);
		hdc = BeginPaint(hwnd, &ps);
		memdc1 = CreateCompatibleDC(hdc);
		(HBITMAP)SelectObject(memdc1, hbit1);
		BitBlt(hdc, 0, 0, rectview.right, rectview.bottom, memdc1, 0, 0, SRCCOPY);
		DeleteDC(memdc1);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LOAD:
			CGameManager::GetInstance()->LoadStage();
			break;
		case ID_cheat:
			CGameManager::GetInstance()->Cheat();
			break;
		case ID_startgame:		
			CGameManager::GetInstance()->Init(hwnd, g_hInst, userHbit);
			break;
		case ID_gameexit:
			if (hbit1) DeleteObject(hbit1);
			mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
			mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
			CGameManager::GetInstance()->DestroyInstance();
			CSound::GetInstance()->DestroyInstance();
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		CGameManager::GetInstance()->InputMouse(mx, my);
		
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		break;
	case WM_DESTROY:
		if (hbit1) DeleteObject(hbit1);
		mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		CGameManager::GetInstance()->DestroyInstance();
		CSound::GetInstance()->DestroyInstance();
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
