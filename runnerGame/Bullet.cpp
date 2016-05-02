#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview,int globalX)
{

	if (m_isUse == 1 && (m_isEnemy == 0)){
		(HBITMAP)SelectObject(memdc2, userHbit.b_gundam);
		TransparentBlt(memdc1, m_PosX, m_PosY, 60, 50, memdc2, 1027, 3461, 1066 - 1027, 3506 - 3461, RGB(8, 16, 40));
		m_PosX += 20;
		m_TotalDistanse += 20;
		if (m_TotalDistanse >= rectview.right){
			m_isUse = 0;
			m_TotalDistanse = 0;
		}
	}

	else if (m_isUse == 1 && (m_isEnemy == 1)){
		(HBITMAP)SelectObject(memdc2, userHbit.b_Enemy);
		TransparentBlt(memdc1, m_PosX - 20 - globalX, m_PosY - 20, 60, 40, memdc2, 22, 7, 43 - 22, 20 - 7, RGB(255, 255, 255));
	}
}

void CBullet::Init()
{
	m_isUse = 0;
}

bool CBullet::isUse()
{
	if (m_isUse)
		return true;
	else return false;
}

void CBullet::Fire(int posX,int posY)
{
	m_isUse = 1;
	m_PosX = posX;
	m_PosY = posY;
}