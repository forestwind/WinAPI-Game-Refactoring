#pragma once
#include "stdafx.h"
#include "Common.h"

class CBullet
{
private:
	int m_isEnemy;
	int m_isUse;
	int m_PosX,m_PosY;
	int m_SizeX, m_SizeY;
	int m_TotalDistanse;
public:

	CBullet();
	~CBullet();
	void Init();
	bool isUse();
	void Fire(int posX, int posY);
	void Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview, int globalX);

	//get ÇÔ¼ö
	long getPosX() { return m_PosX; }
	long getPosY() { return m_PosY; }

	void setPosX(long posX) { m_PosX = posX; }
	void setPosY(long posY)	{ m_PosY = posY; }
	
	void setisUse(int use)	{ m_isUse = use; }

	void setisEnemy(int isEnemy) { m_isEnemy = isEnemy; }
};

