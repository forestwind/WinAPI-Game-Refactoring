#include "Objects.h"

class CStage;

CObjects::CObjects()
{
}


CObjects::~CObjects()
{
}

void CObjects::Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion,int globalX)
{
		if (use == 1){
			if (Objecttype == 1){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 8, 220, 41 - 8, 252 - 220, RGB(0, 140, 189));
			}
			else if (Objecttype == 2){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 250, 706, 305 - 250, 802 - 706, RGB(0, 140, 189));
			}
			else if (Objecttype == 3){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 251, 902, 314 - 251, 964 - 902, RGB(0, 140, 189));
			}
			else if (Objecttype == 4){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 293, 429, 320 - 293, 453 - 429, RGB(0, 140, 189));
			}
			else if (Objecttype == 5){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 335, 1648, 363 - 335, 1680 - 1648, RGB(0, 140, 189));
			}
			else if (Objecttype == 6){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 374, 1648, 401 - 374, 1680 - 1648, RGB(0, 140, 189));
			}
			else if (Objecttype == 7){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 275, 57, 342 - 275, 125 - 57, RGB(0, 140, 189));
			}
			else if (Objecttype == 8){
				(HBITMAP)SelectObject(memdc2, userHbit.b_object);
				TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 374, 1688, 400 - 374, 1721 - 1688, RGB(0, 140, 189));
			}
			else if (Objecttype == 9){
				(HBITMAP)SelectObject(memdc2, userHbit.b_Enemy);
				if (Enemymotion == 0){
					TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 669, 0, 767 - 669, 103 - 0, RGB(255, 255, 255));
				}
				else if (Enemymotion == 1){
					TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 574, 5, 670 - 574, 111 - 5, RGB(255, 255, 255));
				}
				else if (Enemymotion == 2){
					TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 292, 7, 398 - 292, 98 - 7, RGB(255, 255, 255));
				}
				else if (Enemymotion == 3){
					TransparentBlt(memdc1, Start.x + objectX, Start.y, size.x, size.y,memdc2, 66, 4, 173 - 66, 111 - 4, RGB(255, 255, 255));
				}
			}
		}

		EnemyBullet.Render(memdc1, memdc2, userHbit, rectview, globalX);
	
}


void CObjects::EnemyMove(RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX, int playerPosX)
{
	if (use == 1 && Objecttype == 9) {			//적이 캐릭터를 따라서 같이 움직이게 설정
		if (playerPosX + globalX + rectview.right / 2 >= (Start.x)) {
			Start.x += 5;
			if (EnemyBullet.isUse() == false){
				EnemyBullet.Fire(Start.x, Start.y + 40);
				EnemyBullet.setisEnemy(1);
			}
		}

		if (EnemyBullet.isUse() == true){
			EnemyBullet.setPosX(EnemyBullet.getPosX() - 10);
			if (EnemyBullet.getPosX() <= globalX){
				EnemyBullet.setisUse(0);
			}
		}


	}


	
		if (Objecttype == 9 && use == 1) {
			Start.y += Enemy_Y_Direction;
			if ((Start.y + size.y >(rectview.bottom / 10) * 9 - 20) || (Start.y < 0)) {
				Enemy_Y_Direction *= -1;
			}
		}

}