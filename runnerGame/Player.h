#pragma once

#include "stdafx.h"
#include "Common.h"
#include "Stage.h"
#include "Bullet.h"

class CPlayer
{
private:
	int posX, posY;		// 좌표
	int sizeX, sizeY;	// 크기
	int CurrentLife;	// 생명
	int GameOverlife;	// 게임오버 라이프

	int WalkMotion;				// 건담 걷기 이동 모션
	int JumpMotion;				// 건담 점프 모션
	int RushMotion;				//돌진 모션
	int ShootingMotion;			//총쏘는 모션
	int FlyMotion;				//건담 비행기 모션
	int HitMotion;				//건담 피격 모션


	int ApplyItemEffect;		//건담 아이템 효과
	int PlayerJumpState;		//점프키 상태
	

public:
	CBullet bullet[5];

	CPlayer();
	~CPlayer();
	void Init();
	void Update();
	void Reset();
	bool isPlayerDie();
	void AnimationMotion(int itemtime, int scrollSPEED);
	void GravityCheck(RECT rectview);
	void CollisionCheck(int itemtime, int scrollSPEED, CStage* stage, int NOWStage, BOOM* boom, int score, int globalX);
	void BulletCollisionCheck(int itemtime, int scrollSPEED, CStage* stage, int NOWStage, BOOM* boom, int score, int globalX);
	void InputKeyboard(CStage* stage, int NOWStage, BOOM* boom, int score, int globalX, RECT rectview);
	void Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview, int globalX);



	//set 함수
	void setPlayerLife(int playerLife) { CurrentLife = playerLife; }
	void setItemEffect(int itemEffect) { ApplyItemEffect = itemEffect; }
	void setPlayerJumpState(int playerjumpstate){ PlayerJumpState = playerjumpstate; }

	//get 함수

	int getPlayerLife() { return CurrentLife; }
	int getPlayerItemEffect() { return ApplyItemEffect; }
	int getPlayerJumpState() { return PlayerJumpState; }

	int getPositionX() { return posX; }
	int getPositionY() { return posY; }
	int getSizeX() { return sizeX; }
	int getSizeY() { return sizeY; }
	int getWalkMotion() { return WalkMotion; }
	int getJumpMotion() { return JumpMotion; }
	int getRushMotion() { return RushMotion; }
	int getShootMotion() { return ShootingMotion; }
	int getFlyMotion() { return FlyMotion; }
	int getHitMotion() { return HitMotion; }
};

