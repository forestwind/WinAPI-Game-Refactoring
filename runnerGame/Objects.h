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

	int use;  //���������
	int Objecttype; //������Ʈ Ÿ��
	POINT Start;  //��ŸƮ ��ǥ
	POINT size;   // ������
	int health;   //ü��

	
	CBullet EnemyBullet;
	int Enemy_Y_Direction; // ���� ���⼺
};

