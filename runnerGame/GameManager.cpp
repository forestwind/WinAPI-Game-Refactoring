#include "GameManager.h"


CGameManager::CGameManager()
{
	m_hwnd=0;
	m_hInst = 0;
	m_rectview = {};



	m_ScrollSpeed = 0;		
	m_CurrentStage=0;			
	m_GlobalX=0;
	m_ScreenX=0, m_ScreenY=0;		//스크린 이동값
	m_ObjectX=0, m_ObjectY=0;		//오브젝트 이동값
	m_Score=0;						//점수

	memset(&stage, 0, sizeof(CStage)*4);

	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 100; ++j){
			stage[i].object[j].Enemy_Y_Direction = 5;
		}
	}

	m_EnemyMotion=0;			//적 모션
	m_Timecount=0;				//애니메이션 프레임설정
	

	m_Itemtime=0;				//아이템 지속시간
	memset(&boom, 0, sizeof(BOOM) * 10);
	

}


CGameManager::~CGameManager()
{
}

void CGameManager::Init(HWND& hwnd, HINSTANCE& hInst, UserHbit& userHbit)
{
	
	//////////////////////비트맵불러오기

	userHbit.b_background[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	userHbit.b_background[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	userHbit.b_background[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	userHbit.b_object = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	userHbit.b_Enemy = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	userHbit.b_gundam = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	userHbit.b_title = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	userHbit.b_interface = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	userHbit.b_ending = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	userHbit.b_boom = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));


	


	m_ScrollSpeed = 5;
	m_TitleCheck = 1; //타이틀화면을 실행한다.




	m_hwnd = hwnd;
	m_hInst = hInst;

	player.Init();
}

void CGameManager::isEndgame()
{

	GetClientRect(m_hwnd, &m_rectview);

	if (m_GlobalX >= m_rectview.right * 19) {  //게임 종료 조건

		KillTimer(m_hwnd, 1);
		MessageBox(m_hwnd, "STAGE CLEAR", "CLEAR", MB_OK);

		++m_CurrentStage;
		m_GlobalX = 0;
		m_ObjectX = 0;
	

		player.Reset();

		SetTimer(m_hwnd, 1, 10, NULL);
		if (m_CurrentStage == 3){
			KillTimer(m_hwnd, 1);
			MessageBox(m_hwnd, "게임을 즐겨주셔서 감사합니다", "땡큐!", MB_OK);
		}
		else if (m_CurrentStage == 4){
			KillTimer(m_hwnd, 1);
			MessageBox(m_hwnd, "특별스테이지를 즐기셨습니다", "땡큐!", MB_OK);
			m_CurrentStage = 0;
		}
	}
	else if ( player.isPlayerDie() ){
		KillTimer(m_hwnd, 1);
		MessageBox(m_hwnd, "죽음~!ㅎ.ㅎ", "죽음~!ㅎ.ㅎ", MB_OK);
	}
}

void CGameManager::Render(HWND& hwnd, HDC& hdc, HDC& memdc1, HDC& memdc2, HBITMAP& hbit1, UserHbit& userHbit, RECT& rectview)
{
	char test[100], m_ScoreText[100];

	
	GetClientRect(hwnd, &rectview);
	hdc = GetDC(hwnd);
	if (hbit1 == NULL)
		hbit1 = CreateCompatibleBitmap(hdc, rectview.right, rectview.bottom);
	memdc1 = CreateCompatibleDC(hdc);
	memdc2 = CreateCompatibleDC(memdc1);
	(HBITMAP)SelectObject(memdc1, hbit1);

	


	
	

	if (m_TitleCheck == 1) {             //타이틀 화면
		(HBITMAP)SelectObject(memdc2, userHbit.b_title);
		StretchBlt(memdc1, 0, 0, rectview.right, rectview.bottom, memdc2, 0, 0, 255, 223, SRCCOPY);
		
	}//타이틀 끝


	else if (m_TitleCheck == 0) {        //게임 화면

		stage[m_CurrentStage].Render(memdc1, memdc2, userHbit, rectview, m_CurrentStage, stage, m_ScreenX, m_ObjectX, m_EnemyMotion,m_GlobalX);

		player.Render(memdc1, memdc2, userHbit, rectview,m_GlobalX);



		for (int i = 0; i < 10; ++i) {  //폭발 화면
			if (boom[i].use == 1){
				(HBITMAP)SelectObject(memdc2, userHbit.b_boom);
				if (boom[i].boomcount == 0) {
					TransparentBlt(memdc1, boom[i].Start.x, boom[i].Start.y, 100, 100, memdc2, 0, 0, 50, 50, RGB(120, 120, 120));

				}
				else if (boom[i].boomcount == 1) {
					TransparentBlt(memdc1, boom[i].Start.x, boom[i].Start.y, 100, 100, memdc2, 0, 50, 50, 50, RGB(120, 120, 120));

				}
				else if (boom[i].boomcount == 2) {
					TransparentBlt(memdc1, boom[i].Start.x, boom[i].Start.y, 100, 100, memdc2, 0, 100, 50, 50, RGB(120, 120, 120));

				}
				else if (boom[i].boomcount == 3) {
					TransparentBlt(memdc1, boom[i].Start.x, boom[i].Start.y, 100, 100, memdc2, 0, 150, 50, 50, RGB(120, 120, 120));
				}
			}

		}



		for (int i = 0; i < player.getPlayerLife(); ++i){     //건담 라이프 표기
			(HBITMAP)SelectObject(memdc2, userHbit.b_interface);
			TransparentBlt(memdc1, i * 50, 0, 50, 80, memdc2, 293, 28, 325 - 293, 77 - 28, RGB(0, 255, 255));
		}



		sprintf(m_ScoreText, "점수 : %d", m_Score);  //점수 화면
		TextOut(memdc1, (m_rectview.right / 10) * 4, 0, m_ScoreText, strlen(m_ScoreText));


		
	}
	//게임화면 끝







	DeleteDC(memdc2);
	DeleteDC(memdc1);
	ReleaseDC(hwnd, hdc);
	InvalidateRect(hwnd, NULL, FALSE);


}

void CGameManager::Update()
{
	if (m_TitleCheck == 0) {    //메인화면

		m_ScreenX -= 1;                 ///화면 스크롤 이동
		if (0 >= m_ScreenX)
			m_ScreenX = m_rectview.right;

		m_ObjectX -= m_ScrollSpeed;	///오브젝트 스크롤 이동
		m_GlobalX += m_ScrollSpeed;  //전체 화면 이동
		m_Score += 1;


		if (m_Timecount == 8) {		// 캐릭터 모션찍기



		player.AnimationMotion(m_Itemtime,m_ScrollSpeed);


			++m_EnemyMotion;  //적모션
			m_EnemyMotion = m_EnemyMotion % 4;


			for (int i = 0; i < 10; ++i) {  //폭발 화면
				if (boom[i].use == 1){
					++boom[i].boomcount;
					if (boom[i].boomcount == 4){
						boom[i].use = 0;
						boom[i].boomcount = 0;
					}
				}
			}

		}


		
		player.GravityCheck(m_rectview);
		player.CollisionCheck(m_Itemtime, m_ScrollSpeed, stage, m_CurrentStage,boom,m_Score,m_GlobalX);
		player.BulletCollisionCheck(m_Itemtime, m_ScrollSpeed, stage, m_CurrentStage, boom, m_Score, m_GlobalX);




		


		stage[m_CurrentStage].Update(m_rectview, m_CurrentStage, stage, m_ScreenX, m_ObjectX, m_EnemyMotion, m_GlobalX, player.getPositionX());

		


		for (int i = 0; i < 100; ++i) {  //적 총알 과 건담과의 충돌처리
			if (stage[m_CurrentStage].object[i].EnemyBullet.isUse() == 1) {
				
				 if (player.getPositionX() + player.getSizeX() > stage[m_CurrentStage].object[i].EnemyBullet.getPosX() - 20 - m_GlobalX && player.getPositionX() + player.getSizeX() < stage[m_CurrentStage].object[i].EnemyBullet.getPosX() - 20 - m_GlobalX + 60) {
					if (player.getPositionY() + player.getSizeY() > stage[m_CurrentStage].object[i].EnemyBullet.getPosY() - 20 && player.getPositionY() < stage[m_CurrentStage].object[i].EnemyBullet.getPosY() - 20 + 40) {

						for (int j = 0; j < 10; ++j){
							if (boom[j].use == 0){
								boom[j].Start.x = stage[m_CurrentStage].object[i].EnemyBullet.getPosX() - m_GlobalX - 100;
								boom[j].Start.y = stage[m_CurrentStage].object[i].EnemyBullet.getPosY() - 20;
								boom[j].use = 1;
								break;
							}
						}

						if (player.getPlayerItemEffect() == 2){
							player.setItemEffect(0);
						}

						if (player.getPlayerJumpState() != 3){
							stage[m_CurrentStage].object[i].EnemyBullet.setisUse(0);

							player.setPlayerLife(player.getPlayerLife() - 1);
							CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
							CSound::GetInstance()->Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
							player.setPlayerJumpState(3);
						}
					}
				}
			}
		}

	} //게임 로직 끝


	

	++m_Timecount;
	m_Timecount = m_Timecount % 9; //모션 카운트
}


void  CGameManager::InputKeyboard()
{
	//키입력

	player.InputKeyboard(stage, m_CurrentStage, boom, m_Score, m_GlobalX, m_rectview);

	
}

void  CGameManager::InputMouse(int mx, int my)
{
	FILE *fp;

	if (m_TitleCheck == 1) {          //타이틀 화면에서 시작 누르기
		if (mx > 370 && mx < 830){
			if (my > 465 && my < 505) {
				m_TitleCheck = 0;
				m_CurrentStage = 0;
				player.setPlayerLife(5);
				m_Score = 0;
				player.setItemEffect(0);
				m_GlobalX = 0;
				m_ObjectX = 0;
				m_ScreenX = 0;
				CSound::GetInstance()->Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				CSound::GetInstance()->Sound2 = mciSendCommand(2, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);

				/////////////////////////스테이지 불러오기 
				fp = fopen("1.txt", "r");
				fscanf(fp, "%d %d \n", &stage[0].m_BackGroundType, &stage[0].m_TileType);
				for (int i = 0; i < 100; ++i){
					fscanf(fp, "%d %d %d %d %d %d %d \n", &stage[0].object[i].Objecttype, &stage[0].object[i].use, &stage[0].object[i].Start.x, &stage[0].object[i].Start.y,
						&stage[0].object[i].size.x, &stage[0].object[i].size.y, &stage[0].object[i].health);
				}
				fclose(fp);

				fp = fopen("2.txt", "r");
				fscanf(fp, "%d %d \n", &stage[1].m_BackGroundType, &stage[1].m_TileType);
				for (int i = 0; i < 100; ++i){
					fscanf(fp, "%d %d %d %d %d %d %d \n", &stage[1].object[i].Objecttype, &stage[1].object[i].use, &stage[1].object[i].Start.x, &stage[1].object[i].Start.y,
						&stage[1].object[i].size.x, &stage[1].object[i].size.y, &stage[1].object[i].health);
				}
				fclose(fp);

				fp = fopen("3.txt", "r");
				fscanf(fp, "%d %d \n", &stage[2].m_BackGroundType, &stage[2].m_TileType);
				for (int i = 0; i < 100; ++i){
					fscanf(fp, "%d %d %d %d %d %d %d \n", &stage[2].object[i].Objecttype, &stage[2].object[i].use, &stage[2].object[i].Start.x, &stage[2].object[i].Start.y,
						&stage[2].object[i].size.x, &stage[2].object[i].size.y, &stage[2].object[i].health);
				}
				fclose(fp);


			}
		}
	}
}


void  CGameManager::LoadStage()
{
	FILE *fp;
	OPENFILENAME OFN, SFN;
	char str[200] = "";
	char lpstrFile[200] = "";
	char filter[] = "Every File(*.*)\0*.*\0 Text File\0*.txt\0";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hwnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = "."; // 초기 디렉토리
	if (GetOpenFileName(&OFN) != 0) {
		wsprintf(str, "%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
		MessageBox(m_hwnd, str, "열기 선택", MB_OK);
		fp = fopen(OFN.lpstrFile, "r");
		fscanf(fp, "%d %d \n", &stage[3].m_BackGroundType, &stage[3].m_TileType);
		for (int i = 0; i < 100; ++i){
			fscanf(fp, "%d %d %d %d %d %d %d \n", &stage[3].object[i].Objecttype, &stage[3].object[i].use, &stage[3].object[i].Start.x, &stage[3].object[i].Start.y,
				&stage[3].object[i].size.x, &stage[3].object[i].size.y, &stage[3].object[i].health);
		}
		fclose(fp);
	}

	m_TitleCheck = 0;
	m_CurrentStage = 3;
	player.setPlayerLife(5);
	m_Score = 0;

	CSound::GetInstance()->Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	CSound::GetInstance()->Sound2 = mciSendCommand(2, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&CSound::GetInstance()->mciPlay);
}