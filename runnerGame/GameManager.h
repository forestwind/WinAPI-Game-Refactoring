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
	int m_ScrollSpeed;			//ȭ���̵����ǵ�
	int m_TitleCheck;			//Ÿ��Ʋ ȭ������ Ȯ��
	int m_CurrentStage;			//���� �������� Ȯ�κ���
	int m_GlobalX;
	int m_ScreenX, m_ScreenY;		//��ũ�� �̵���
	int m_ObjectX, m_ObjectY;		//������Ʈ �̵���
	int m_Score;					//����
	
	
	int m_EnemyMotion;			//�� ���
	int m_Timecount;				//�ִϸ��̼� �����Ӽ���
	int m_Itemtime;				//������ ���ӽð�
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
