#pragma once

#include "stdafx.h"
#include "Common.h"
#include "Stage.h"
#include "Bullet.h"

class CPlayer
{
private:
	int posX, posY;		// ��ǥ
	int sizeX, sizeY;	// ũ��
	int CurrentLife;	// ����
	int GameOverlife;	// ���ӿ��� ������

	int WalkMotion;				// �Ǵ� �ȱ� �̵� ���
	int JumpMotion;				// �Ǵ� ���� ���
	int RushMotion;				//���� ���
	int ShootingMotion;			//�ѽ�� ���
	int FlyMotion;				//�Ǵ� ����� ���
	int HitMotion;				//�Ǵ� �ǰ� ���


	int ApplyItemEffect;		//�Ǵ� ������ ȿ��
	int PlayerJumpState;		//����Ű ����
	

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



	//set �Լ�
	void setPlayerLife(int playerLife) { CurrentLife = playerLife; }
	void setItemEffect(int itemEffect) { ApplyItemEffect = itemEffect; }
	void setPlayerJumpState(int playerjumpstate){ PlayerJumpState = playerjumpstate; }

	//get �Լ�

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

