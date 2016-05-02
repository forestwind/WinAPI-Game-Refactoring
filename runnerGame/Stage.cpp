#include "Stage.h"


CStage::CStage()
{
}


CStage::~CStage()
{
}

void CStage::Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX)
{

	if (stage[NOWStage].m_BackGroundType == 0){
		(HBITMAP)SelectObject(memdc2, userHbit.b_background[0]);       //배경 그리기
		StretchBlt(memdc1, screenX, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 253, 263, SRCCOPY);
		StretchBlt(memdc1, screenX - rectview.right, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 253, 263, SRCCOPY);
		for (int i = 0; i < 20; ++i){
			TransparentBlt(memdc1, objectX + (rectview.right*i), rectview.bottom / 2, rectview.right, rectview.bottom / 2,
				memdc2, 0, 266, 384, 407 - 266, RGB(255, 128, 255));
		}
	}
	else if (stage[NOWStage].m_BackGroundType == 1) {
		(HBITMAP)SelectObject(memdc2, userHbit.b_background[1]);       //배경 그리기
		StretchBlt(memdc1, screenX, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 253, 263, SRCCOPY);
		StretchBlt(memdc1, screenX - rectview.right, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 253, 263, SRCCOPY);
		for (int i = 0; i < 20; ++i){
			TransparentBlt(memdc1, objectX + (rectview.right*i), rectview.bottom / 2, rectview.right, rectview.bottom / 2,
				memdc2, 0, 266, 384, 407 - 266, RGB(255, 128, 255));
		}
	}
	else if (stage[NOWStage].m_BackGroundType == 2){
		(HBITMAP)SelectObject(memdc2, userHbit.b_background[2]);
		StretchBlt(memdc1, screenX, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 256, 303, SRCCOPY);
		StretchBlt(memdc1, screenX - rectview.right, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 256, 303, SRCCOPY);
		for (int i = 0; i < 20; ++i){
			TransparentBlt(memdc1, objectX + (rectview.right*i), rectview.bottom / 2, rectview.right, rectview.bottom / 2,
				memdc2, 0, 308, 384, 143, RGB(255, 128, 255));
		}
	}

	if (stage[NOWStage].m_TileType == 0){    //타일 그리기
		(HBITMAP)SelectObject(memdc2, userHbit.b_object);
		for (int i = 0; i < 20; ++i) {
			TransparentBlt(memdc1, objectX + (rectview.right*i), (rectview.bottom / 10) * 9 - 20, rectview.right, (rectview.bottom / 10) + 20,
				memdc2, 9, 527, 169 - 9, 559 - 527, RGB(255, 128, 255));
		}
	}
	else if (stage[NOWStage].m_TileType == 1) {
		(HBITMAP)SelectObject(memdc2, userHbit.b_object);

		for (int i = 0; i < 20; ++i){
			TransparentBlt(memdc1, objectX + (rectview.right*i), (rectview.bottom / 10) * 9, rectview.right, rectview.bottom / 10,
				memdc2, 297, 629, 423 - 297, 657 - 629, RGB(0, 140, 189));
		}
	}
	else if (stage[NOWStage].m_TileType == 2) {
		(HBITMAP)SelectObject(memdc2, userHbit.b_object);
		for (int i = 0; i < 20; ++i) {
			TransparentBlt(memdc1, objectX + (rectview.right*i), (rectview.bottom / 10) * 9, rectview.right, rectview.bottom / 10,
				memdc2, 16, 1325, 144 - 16, 1355 - 1325, RGB(0, 140, 189));
		}
	}

	for (int i = 0; i < 100; ++i){
		object[i].Render(memdc1, memdc2, userHbit, rectview, NOWStage, stage, screenX, objectX, Enemymotion,globalX);
	}
	
}

void CStage::Update(RECT& rectview, int NOWStage, CStage* stage, int& screenX, int& objectX, int& Enemymotion, int globalX,int playerPosX)
{
	for (int i = 0; i < 100; ++i){
		object[i].EnemyMove(rectview, NOWStage, stage, screenX, objectX, Enemymotion, globalX,playerPosX);
	}
}