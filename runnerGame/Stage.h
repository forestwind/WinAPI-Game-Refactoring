#pragma once
#include "stdafx.h"
#include "Objects.h"
#include "Common.h"

class CStage
{
private:
	
public:
	CStage();
	~CStage();
	void Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX);
	void Update(RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX,int playerPosX);
	
	CObjects object[100];  //Àå¾Ö¹°

	int m_BackGroundType;
	int m_TileType;

};

