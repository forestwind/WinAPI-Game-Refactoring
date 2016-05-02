#pragma once
#include "stdafx.h"
#include "Common.h"
#include "Bullet.h"


class CStage;

class CObjects
{
private:
	
public:
	CObjects();
	~CObjects();
	void Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX);
	void EnemyMove(RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX, int playerPosX);

	int use;  //사용중인지
	int Objecttype; //오브젝트 타입
	POINT Start;  //스타트 좌표
	POINT size;   // 사이즈
	int health;   //체력

	
	CBullet EnemyBullet;
	int Enemy_Y_Direction; // 적들 방향성
};

