#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	CurrentLife = 5;
	GameOverlife = 0;
	posX = 120;
	posY = 500;
	sizeX = 135;
	sizeY = 165;

	WalkMotion = 0;
	JumpMotion = 0;
	RushMotion = 0;
	ShootingMotion = 0;
	FlyMotion = 0;
	RushMotion = 0;
	HitMotion = 0;

	PlayerJumpState = 0;
	ApplyItemEffect = 0;

	for (int i = 0; i < 5; ++i){
		bullet[i].Init();
		bullet[i].setisEnemy(0);
	}

}

void CPlayer::Reset()
{
	for (int i = 0; i < 5; ++i){
		bullet[i].Init();
	}
	posX = 120;
	posY = 500;
}

bool CPlayer::isPlayerDie()
{
	if (CurrentLife == GameOverlife)
		return true;
	else return false;
}

void CPlayer::AnimationMotion(int itemtime, int scrollSPEED)
{
	

		if (PlayerJumpState == 0) {  //점프하지 않았을때
			++WalkMotion;
			WalkMotion = WalkMotion % 8;
		}

		else if (PlayerJumpState == 1){
			if (JumpMotion != 4){
				posY -= 80;
				++JumpMotion;
				if (posY <= -10){
					JumpMotion = 0;
					PlayerJumpState = 0;
				}
			}
			else PlayerJumpState = 0;
		}
		else {}




		if (PlayerJumpState == 2){  //총쏘는 모션
			ShootingMotion++;
			if (ShootingMotion == 6){
				PlayerJumpState = 0;
				ShootingMotion = 0;

				CSound::GetInstance()->Sound3 = mciSendCommand(3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				CSound::GetInstance()->Sound3 = mciSendCommand(3, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

				for (int i = 0; i < 5; ++i){
					if (!bullet[i].isUse()) {
						bullet[i].Fire(posX+50, posY+30);
						break;
					}
				}


			}
		}

		if (PlayerJumpState == 3) {		//히트 모션
			++HitMotion;

			if (HitMotion == 6){
				PlayerJumpState = 0;
				HitMotion = 0;
			}
		}



		




		





		if (ApplyItemEffect != 0){   //아이템 먹엇을때 지속시간 타이머 설정
			++itemtime;
		}


		if (ApplyItemEffect == 1){         //가속아이템 먹었을시 체크
			++RushMotion;
			RushMotion = RushMotion % 6;
			scrollSPEED = 7;

			if (itemtime == 20){
				itemtime = 0;
				ApplyItemEffect = 0;
				scrollSPEED = 5;
			}
			for (int i = 0; i < 5; ++i){
				bullet[i].Init();
			}
		}
		else if (ApplyItemEffect == 2) {  //비행아이템 먹었을시 체크
			if (FlyMotion < 4)
				++FlyMotion;


			if (itemtime == 50){
				itemtime = 0;
				ApplyItemEffect = 0;
			}

		}
		else {}
	
}

void CPlayer::GravityCheck(RECT rectview)
{
	if (ApplyItemEffect != 2) {
		if (PlayerJumpState == 0 && posY + 150 < ((rectview.bottom / 10) * 9) - 20)  //중력받아 아래로 떨어지게 비행기때는 안떨어짐
			posY += 15;
		else if (posY + 150 >= ((rectview.bottom / 10) * 9) - 20)
			posY = ((rectview.bottom / 10) * 9) - 20 - 150;
	}
}

void CPlayer::CollisionCheck(int itemtime, int scrollSPEED, CStage* stage, int NOWStage, BOOM* boom, int score, int globalX)
{

	for (int i = 0; i < 100; ++i) {    	///장애물과 충돌체크 과정///
		if (stage[NOWStage].object[i].use == 1) {



			if ((posX + 135 + globalX)  > stage[NOWStage].object[i].Start.x && (posX + 135 + globalX) <  stage[NOWStage].object[i].Start.x + stage[NOWStage].object[i].size.x){
				if ((posY + 150) > stage[NOWStage].object[i].Start.y && (posY + 150) < stage[NOWStage].object[i].Start.y + stage[NOWStage].object[i].size.y){



					if ((stage[NOWStage].object[i].Objecttype == 1) || (stage[NOWStage].object[i].Objecttype == 2) || (stage[NOWStage].object[i].Objecttype == 3) || (stage[NOWStage].object[i].Objecttype == 4)) {

						for (int j = 0; j < 10; ++j){
							if (boom[j].use == 0){
								boom[j].Start.x = stage[NOWStage].object[i].Start.x - globalX - 50;
								boom[j].Start.y = stage[NOWStage].object[i].Start.y;
								boom[j].use = 1;
								break;
							}
						}

						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						if ((ApplyItemEffect != 1) && (PlayerJumpState != 3)) {
							CurrentLife -= 1;
							PlayerJumpState = 3;
						}
						if (ApplyItemEffect == 2){
							ApplyItemEffect = 0;
						}
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

					}
					else if (stage[NOWStage].object[i].Objecttype == 5) { //아이템1과 충돌체크(생명추가)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						++CurrentLife;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

					}
					else if (stage[NOWStage].object[i].Objecttype == 6) {   //아이템2과 충돌체크 (무적)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 1;
						itemtime = 0;
						scrollSPEED = 10;
						for (i = 0; i < 5; ++i){
							bullet[i].Init();
						}


						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

					}
					else if (stage[NOWStage].object[i].Objecttype == 7) {   //아이템3과 충돌체크 (변신)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 2;
						sizeX = 200;
						sizeY = 100;
						itemtime = 0;
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 8) {  //점수 아이템
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						score += 10000;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 9) {
						if (ApplyItemEffect == 1) {
							for (int j = 0; j < 10; ++j){
								if (boom[j].use == 0){
									boom[j].Start.x = stage[NOWStage].object[i].Start.x - 50;
									boom[j].Start.y = stage[NOWStage].object[i].Start.y;
									boom[j].use = 1;
									break;
								}
							}
							stage[NOWStage].object[i].use = 0;
							stage[NOWStage].object[i].Start.x = 0;
							stage[NOWStage].object[i].Start.y = 0;
							stage[NOWStage].object[i].size.x = 0;
							stage[NOWStage].object[i].size.y = 0;
							stage[NOWStage].object[i].Objecttype = 0;
						}
					}
				}
			}



			//장애물 처리 2번째 경우
			if ((posX + globalX)  > stage[NOWStage].object[i].Start.x && (posX + globalX) <  stage[NOWStage].object[i].Start.x + stage[NOWStage].object[i].size.x){
				if ((posY) > stage[NOWStage].object[i].Start.y && (posY) < stage[NOWStage].object[i].Start.y + stage[NOWStage].object[i].size.y){



					if ((stage[NOWStage].object[i].Objecttype == 1) || (stage[NOWStage].object[i].Objecttype == 2) || (stage[NOWStage].object[i].Objecttype == 3) || (stage[NOWStage].object[i].Objecttype == 4)) {

						for (int j = 0; j < 10; ++j){
							if (boom[j].use == 0){
								boom[j].Start.x = stage[NOWStage].object[i].Start.x;
								boom[j].Start.y = stage[NOWStage].object[i].Start.y;
								boom[j].use = 1;
								break;
							}
						}


						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						if ((ApplyItemEffect != 1) && (PlayerJumpState != 3)) {
							CurrentLife -= 1;
							PlayerJumpState = 3;
						}
						if (ApplyItemEffect == 2){
							ApplyItemEffect = 0;
						}
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 5) { //아이템1과 충돌체크(생명추가)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						++CurrentLife;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 6) {   //아이템2과 충돌체크 (무적)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 1;
						itemtime = 0;
						scrollSPEED = 10;
						for (i = 0; i < 5; ++i){
							bullet[i].Init();
						}


						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

					}
					else if (stage[NOWStage].object[i].Objecttype == 7) {   //아이템3과 충돌체크 (변신)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 2;
						sizeX = 200;
						sizeY = 100;
						itemtime = 0;
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 8) {  //점수 아이템
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						score += 10000;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 9) {
						if (ApplyItemEffect == 1) {
							for (int j = 0; j < 10; ++j){
								if (boom[j].use == 0){
									boom[j].Start.x = stage[NOWStage].object[i].Start.x;
									boom[j].Start.y = stage[NOWStage].object[i].Start.y;
									boom[j].use = 1;
									break;
								}
							}
							stage[NOWStage].object[i].use = 0;
							stage[NOWStage].object[i].Start.x = 0;
							stage[NOWStage].object[i].Start.y = 0;
							stage[NOWStage].object[i].size.x = 0;
							stage[NOWStage].object[i].size.y = 0;
							stage[NOWStage].object[i].Objecttype = 0;
						}
					}
				}
			}


			//3번째경우
			if ((posX + 135 + globalX)  > stage[NOWStage].object[i].Start.x && (posX + 135 + globalX) <  stage[NOWStage].object[i].Start.x + stage[NOWStage].object[i].size.x){
				if ((posY) > stage[NOWStage].object[i].Start.y && (posY) < stage[NOWStage].object[i].Start.y + stage[NOWStage].object[i].size.y){



					if ((stage[NOWStage].object[i].Objecttype == 1) || (stage[NOWStage].object[i].Objecttype == 2) || (stage[NOWStage].object[i].Objecttype == 3) || (stage[NOWStage].object[i].Objecttype == 4)) {

						for (int j = 0; j < 10; ++j){
							if (boom[j].use == 0){
								boom[j].Start.x = stage[NOWStage].object[i].Start.x;
								boom[j].Start.y = stage[NOWStage].object[i].Start.y;
								boom[j].use = 1;
								break;
							}
						}


						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						if ((ApplyItemEffect != 1) && (PlayerJumpState != 3)) {
							CurrentLife -= 1;
							PlayerJumpState = 3;
						}
						if (ApplyItemEffect == 2){
							ApplyItemEffect = 0;
						}
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 5) { //아이템1과 충돌체크(생명추가)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						++CurrentLife;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 6) {   //아이템2과 충돌체크 (무적)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 1;
						itemtime = 0;
						scrollSPEED = 10;
						for (i = 0; i < 5; ++i){
							bullet[i].Init();
						}


						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

					}
					else if (stage[NOWStage].object[i].Objecttype == 7) {   //아이템3과 충돌체크 (변신)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 2;
						sizeX = 200;
						sizeY = 100;
						itemtime = 0;
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 8) {  //점수 아이템
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						score += 10000;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 9) {
						if (ApplyItemEffect == 1) {
							for (int j = 0; j < 10; ++j){
								if (boom[j].use == 0){
									boom[j].Start.x = stage[NOWStage].object[i].Start.x;
									boom[j].Start.y = stage[NOWStage].object[i].Start.y;
									boom[j].use = 1;
									break;
								}
							}
							stage[NOWStage].object[i].use = 0;
							stage[NOWStage].object[i].Start.x = 0;
							stage[NOWStage].object[i].Start.y = 0;
							stage[NOWStage].object[i].size.x = 0;
							stage[NOWStage].object[i].size.y = 0;
							stage[NOWStage].object[i].Objecttype = 0;
						}
					}
				}
			}


			if ((posX + globalX) > stage[NOWStage].object[i].Start.x && (posX + globalX) <  stage[NOWStage].object[i].Start.x + stage[NOWStage].object[i].size.x){
				if ((posY + 165) > stage[NOWStage].object[i].Start.y && (posY + 165) < stage[NOWStage].object[i].Start.y + stage[NOWStage].object[i].size.y){



					if ((stage[NOWStage].object[i].Objecttype == 1) || (stage[NOWStage].object[i].Objecttype == 2) || (stage[NOWStage].object[i].Objecttype == 3) || (stage[NOWStage].object[i].Objecttype == 4)) {

						for (int j = 0; j < 10; ++j){
							if (boom[j].use == 0){
								boom[j].Start.x = stage[NOWStage].object[i].Start.x;
								boom[j].Start.y = stage[NOWStage].object[i].Start.y;
								boom[j].use = 1;
								break;
							}
						}


						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						if ((ApplyItemEffect != 1) && (PlayerJumpState != 3)) {
							CurrentLife -= 1;
							PlayerJumpState = 3;
						}
						if (ApplyItemEffect == 2){
							ApplyItemEffect = 0;
						}
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 5) { //아이템1과 충돌체크(생명추가)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						++CurrentLife;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 6) {   //아이템2과 충돌체크 (무적)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 1;
						itemtime = 0;
						scrollSPEED = 10;
						for (i = 0; i < 5; ++i){
							bullet[i].Init();
						}


						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound7 = mciSendCommand(7, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

					}
					else if (stage[NOWStage].object[i].Objecttype == 7) {   //아이템3과 충돌체크 (변신)
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						ApplyItemEffect = 2;
						sizeX = 200;
						sizeY = 100;
						itemtime = 0;
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound6 = mciSendCommand(6, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 8) {  //점수 아이템
						stage[NOWStage].object[i].use = 0;
						stage[NOWStage].object[i].Start.x = 0;
						stage[NOWStage].object[i].Start.y = 0;
						stage[NOWStage].object[i].size.x = 0;
						stage[NOWStage].object[i].size.y = 0;
						stage[NOWStage].object[i].Objecttype = 0;
						score += 10000;
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						CSound::GetInstance()->Sound8 = mciSendCommand(8, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
					}
					else if (stage[NOWStage].object[i].Objecttype == 9) {
						if (ApplyItemEffect == 1) {
							for (int j = 0; j < 10; ++j){
								if (boom[j].use == 0){
									boom[j].Start.x = stage[NOWStage].object[i].Start.x;
									boom[j].Start.y = stage[NOWStage].object[i].Start.y;
									boom[j].use = 1;
									break;
								}
							}
							stage[NOWStage].object[i].use = 0;
							stage[NOWStage].object[i].Start.x = 0;
							stage[NOWStage].object[i].Start.y = 0;
							stage[NOWStage].object[i].size.x = 0;
							stage[NOWStage].object[i].size.y = 0;
							stage[NOWStage].object[i].Objecttype = 0;
						}
					}
				}
			}









		}
	}//오브젝트 충돌처리 끝
}


void CPlayer::BulletCollisionCheck(int itemtime, int scrollSPEED, CStage* stage, int NOWStage, BOOM* boom, int score, int globalX)
{
	for (int i = 0; i < 100; ++i) {  //건담총알과  적과의 충돌처리
		for (int j = 0; j < 5; ++j){
			if (stage[NOWStage].object[i].Objecttype == 9 && stage[NOWStage].object[i].use == 1) {
				if (bullet[j].isUse() == true) {
					if ((bullet[j].getPosX() + globalX - 30 >  stage[NOWStage].object[i].Start.x) && (bullet[j].getPosX() + globalX - 30 <  stage[NOWStage].object[i].Start.x + stage[NOWStage].object[i].size.x)) {
						if ((bullet[j].getPosY() > stage[NOWStage].object[i].Start.y) && (bullet[j].getPosY() < stage[NOWStage].object[i].Start.y + stage[NOWStage].object[i].size.y)) {
							for (j = 0; j < 10; ++j){
								if (boom[j].use == 0){
									boom[j].Start.x = stage[NOWStage].object[i].Start.x - globalX;
									boom[j].Start.y = stage[NOWStage].object[i].Start.y;
									boom[j].use = 1;
									break;
								}
							}
							stage[NOWStage].object[i].use = 0;
							bullet[j].Init();
							CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
							CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
						}
					}
				}
			}
		}
	}
}


void CPlayer::InputKeyboard(CStage* stage, int NOWStage, BOOM* boom, int score, int globalX, RECT rectview)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (ApplyItemEffect == 0 || ApplyItemEffect == 1){
			if (PlayerJumpState == 0){
				posY -= 50;
				PlayerJumpState = 1;
				JumpMotion = 0;
				CSound::GetInstance()->Sound5 = mciSendCommand(5, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				CSound::GetInstance()->Sound5 = mciSendCommand(5, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
			}

		}
	}

	if (ApplyItemEffect == 2){
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			posY -= 5;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			posY += 5;
		}
	}
	if (PlayerJumpState != 3) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			posX -= 5;
			if (posX + globalX < globalX){
				posX += 5;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			posX += 5;
			if (posX + sizeX > rectview.right){
				posX -= 5;
			}
			for (int i = 0; i < 100; ++i){
				if (stage[NOWStage].object[i].Objecttype == 9 && stage[NOWStage].object[i].use == 1){
					stage[NOWStage].object[i].Start.x += 4;
					if (stage[NOWStage].object[i].Start.x + stage[NOWStage].object[i].size.x > globalX + rectview.right)
						stage[NOWStage].object[i].Start.x -= 4;
				}
			}
		}
	}


	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		PlayerJumpState = 2;
	}
}

void CPlayer::Render(HDC& memdc1, HDC& memdc2, UserHbit& userHbit, RECT& rectview,int globalX)
{

	//////////////////////////////////////캐릭터///////////////////////////////
	(HBITMAP)SelectObject(memdc2, userHbit.b_gundam);
	if (ApplyItemEffect == 0){
		if (PlayerJumpState == 0){
			if (WalkMotion == 0){  //걷기모션
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 18, 1415, 90, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 1){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 105, 1415, 90, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 2){
				TransparentBlt(memdc1, posX, posY, 165, 165, memdc2, 200, 1415, 110, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 3){
				TransparentBlt(memdc1, posX, posY, 150, 165, memdc2, 320, 1415, 100, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 4){
				TransparentBlt(memdc1, posX, posY, 150, 165, memdc2, 430, 1415, 100, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 5){
				TransparentBlt(memdc1, posX, posY, 180, 165, memdc2, 530, 1415, 120, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 6){
				TransparentBlt(memdc1, posX, posY, 165, 165, memdc2, 650, 1415, 110, 110, RGB(8, 16, 40));
			}
			else if (WalkMotion == 7){
				TransparentBlt(memdc1, posX, posY, 150, 165, memdc2, 760, 1415, 100, 110, RGB(8, 16, 40));
			}
		}
		else if (PlayerJumpState == 1) {  //점프모션
			if (JumpMotion == 0){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 11, 361, 90, 110, RGB(8, 16, 40));
			}
			else if (JumpMotion == 1){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 103, 361, 90, 110, RGB(8, 16, 40));
			}
			else if (JumpMotion == 2){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 186, 361, 90, 110, RGB(8, 16, 40));
			}

			else if (JumpMotion == 3){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 275, 358, 90, 110, RGB(8, 16, 40));
			}
			else if (JumpMotion == 4){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 377, 357, 90, 110, RGB(8, 16, 40));
			}
		}

		else if (PlayerJumpState == 2) {   //총쏘는 모션
			if (ShootingMotion == 0){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 18, 3438, 102 - 18, 3548 - 3438, RGB(8, 16, 40));
			}
			else if (ShootingMotion == 1){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 101, 3438, 193 - 101, 3548 - 3438, RGB(8, 16, 40));
			}
			else if (ShootingMotion == 2){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 194, 3438, 287 - 194, 3548 - 3438, RGB(8, 16, 40));
			}
			else if (ShootingMotion == 3){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 287, 3438, 380 - 287, 3548 - 3438, RGB(8, 16, 40));
			}
			else if (ShootingMotion == 4){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 381, 3438, 471 - 381, 3548 - 3438, RGB(8, 16, 40));
			}
			else if (ShootingMotion == 5){
				TransparentBlt(memdc1, posX, posY - 50, 135, 165 + 50, memdc2, 472, 3396, 548 - 472, 3548 - 3396, RGB(8, 16, 40));
			}
		}

		else if (PlayerJumpState == 3) { //히트모션
			if (HitMotion == 0){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 16, 679, 114 - 16, 786 - 679, RGB(8, 16, 40));

			}
			else if (HitMotion == 1){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 114, 679, 221 - 114, 786 - 679, RGB(8, 16, 40));

			}
			else if (HitMotion == 2){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 221, 679, 327 - 221, 786 - 679, RGB(8, 16, 40));

			}
			else if (HitMotion == 3){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 327, 679, 435 - 327, 786 - 679, RGB(8, 16, 40));

			}
			else if (HitMotion == 4){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 435, 679, 518 - 435, 786 - 679, RGB(8, 16, 40));

			}
			else if (HitMotion == 5){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 518, 679, 608 - 518, 786 - 679, RGB(8, 16, 40));

			}
		}


		else {}
	}//이펙트 0일때 끝
	else if ( ApplyItemEffect != 0) {

		if ( ApplyItemEffect == 1) {  //돌진 모션
			if (RushMotion == 0){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 695, 2027, 100, 110, RGB(8, 16, 40));
			}
			else if (RushMotion == 1){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 796, 2027, 78, 110, RGB(8, 16, 40));
			}
			else if (RushMotion == 2){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 865, 2027, 110, 110, RGB(8, 16, 40));
			}

			else if (RushMotion == 3){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 980, 2027, 120, 110, RGB(8, 16, 40));
			}
			else if (RushMotion == 4){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 1105, 2027, 90, 110, RGB(8, 16, 40));
			}
			else if (RushMotion == 5){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 1196, 2027, 100, 110, RGB(8, 16, 40));
			}
		}

		else if ( ApplyItemEffect == 2){ //비행모션
			if (FlyMotion == 0) {
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 14, 4358, 80, 110, RGB(8, 16, 40));
			}
			else if (FlyMotion == 1){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 100, 4358, 80, 110, RGB(8, 16, 40));
			}
			else if (FlyMotion == 2){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 182, 4358, 80, 110, RGB(8, 16, 40));
			}

			else if (FlyMotion == 3){
				TransparentBlt(memdc1, posX, posY, 135, 165, memdc2, 268, 4358, 85, 110, RGB(8, 16, 40));
			}
			else if (FlyMotion == 4){
				TransparentBlt(memdc1, posX, posY, 200, 180, memdc2, 372, 4358, 140, 528 - 372, RGB(8, 16, 40));
			}
		}
		else {}


	}//이펙트 있을때 끝
	else {}


	for (int i = 0; i < 5; ++i){
		bullet[i].Render(memdc1, memdc2, userHbit, rectview,globalX);
	}
}