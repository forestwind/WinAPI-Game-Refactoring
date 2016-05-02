#pragma once

#include "stdafx.h"
#include "Common.h"
#include "Player.h"
#include "Stage.h"


class CGameManager : public Singleton<CGameManager>
{
private:

	HWND m_hwnd;
	HINSTANCE m_hInst;
	RECT m_rectview;
	int m_ScrollSpeed;			//화면이동스피드
	int m_TitleCheck;			//타이틀 화면인지 확인
	int m_CurrentStage;			//현재 스테이지 확인변수
	int m_GlobalX;
	int m_ScreenX, m_ScreenY;		//스크린 이동값
	int m_ObjectX, m_ObjectY;		//오브젝트 이동값
	int m_Score;					//점수
	
	
	int m_EnemyMotion;			//적 모션
	int m_Timecount;				//애니메이션 프레임설정
	int m_Itemtime;				//아이템 지속시간
	BOOM boom[10];



	CPlayer player;
	CStage stage[4];

public:
	CGameManager();
	~CGameManager();
	void Update();
	void Init(HWND& hwnd, HINSTANCE& hInst, UserHbit& userHbit);
	void isEndgame();
	void Render(HWND& hwnd, HDC& hdc, HDC& memdc1, HDC& memdc2, HBITMAP& hbit1, UserHbit& userHbit, RECT& rectview);
	void InputKeyboard();
	void InputMouse(int mx, int my);
	void LoadStage();
	void Cheat() { player.setPlayerLife(-100); };


};
