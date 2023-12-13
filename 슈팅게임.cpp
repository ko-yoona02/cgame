#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

//미사일 구조체
struct BULLET
{
	int x;      //x좌표
	int y;      //y좌표
	bool fire;  //미사일 발사했는지 체크
};

char bg[25][80];

//플레이어좌표
int playerX;
int playerY;

//적좌표
int enemyX;
int enemyY;

BULLET playerBullet[20];

//함수설계
void ClearScreen();  //화면을 지운다.
void GameMain(); //게임 메인
void PrintScreen(); //화면 그리기
void KeyControl(); //키 관련 함수
void BulletDraw(); //미사일 그리는 함수
void PlayerDraw(); //플레이어 그리는 함수
void EnemyDraw();  //적 그리는 함수
void EnemyMove();  //적 움직이는 함수
void ClashEnemyAndBullet(); //충돌 처리 함수


void main()
{
	srand(time(NULL)); //랜덤값 시드 만들기

	//플레이어 좌표위치
	playerX = 0;
	playerY = 12;

	//적 좌표 위치
	enemyX = 77;
	enemyY = 12;


	for (int i = 0; i < 20; i++)
	{
		playerBullet[i].x = 0;
		playerBullet[i].y = 0;
		playerBullet[i].fire = false;
	}


	int dwTime = GetTickCount();


	while (true)
	{

		if (dwTime + 50 < GetTickCount())
		{
			dwTime = GetTickCount();

			//지우고
			ClearScreen();
			//플레이어나 적이 움직이고
			GameMain();
			//그려준다.
			PrintScreen();
		}
	}
}

void ClearScreen()
{
	system("cls");

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			bg[y][x] = ' ';
		}
	}
}

void GameMain()
{
	//키입력
	KeyControl();
	//미사일 그리기
	BulletDraw();
	//플레이어 그리기
	PlayerDraw();
	//적의 움직임
	EnemyMove();
	//적을 그려주는 부분
	EnemyDraw();
	//미사일 적의 충돌
	ClashEnemyAndBullet();
}

void PrintScreen()
{
	bg[24][79] = '\0';
	printf("%s", bg);
}

void KeyControl()
{
	char pressKey;

	//키가 입력되면 잡아준다.
	if (_kbhit())
	{
		pressKey = _getch();

		switch (pressKey)
		{
		case 72:
			//위쪽방향
			playerY--;
			if (playerY < 1)
				playerY = 1;
			break;
		case 75:
			playerX--;
			if (playerX < 0)
				playerX = 0;
			break;
		case 77:
			playerX++;
			if (playerX > 75)
				playerX = 75;
			break;
		case 80:
			playerY++;
			if (playerY > 23)
				playerY = 23;
			break;
		case 32: //스페이바 누르면 총알 발사

			for (int i = 0; i < 20; i++)
			{
				//미사일이 발사가능상태인지 확인
				if (playerBullet[i].fire == false)
				{
					playerBullet[i].fire = true;
					
					playerBullet[i].x = playerX + 5;
					playerBullet[i].y = playerY;
					
					break;
				}
			}
			break;
		}
	}
}

void BulletDraw()
{
	for (int i = 0; i < 20; i++)
	{
		if (playerBullet[i].fire == true)
		{
			bg[playerBullet[i].y][playerBullet[i].x - 1] = '-';
			bg[playerBullet[i].y][playerBullet[i].x + 0] = '>';
			playerBullet[i].x++;

			if (playerBullet[i].x > 70)
			{
				playerBullet[i].fire = false;
			}
		}
	}
}

void PlayerDraw()
{
	bg[playerY - 1][playerX + 1] = '>';
	bg[playerY - 1][playerX + 0] = '-';
	bg[playerY + 0][playerX + 1] = '>';
	bg[playerY + 0][playerX + 2] = '>';
	bg[playerY + 0][playerX + 3] = '>';
	bg[playerY + 1][playerX + 0] = '-';
	bg[playerY + 1][playerX + 1] = '>';
}

void EnemyDraw()
{
	bg[enemyY][enemyX - 2] = '<';
	bg[enemyY][enemyX - 1] = '-';
	bg[enemyY][enemyX - 0] = 'O';
	bg[enemyY][enemyX + 1] = '-';
	bg[enemyY][enemyX + 2] = '>';
}

void EnemyMove()
{

	enemyX--;

	if (enemyX < 2)
	{
		enemyX = 77;
		enemyY = (rand() % 20) + 2;  //0~19 2~21
	}


}
//충돌
void ClashEnemyAndBullet()
{

	for (int i = 0; i < 20; i++)
	{
		if (playerBullet[i].fire == true)
		{
			if (playerBullet[i].y == enemyY)
			{
				if (playerBullet[i].x >= (enemyX - 1)
					&& playerBullet[i].x <= (enemyX + 1))
				{
					//충돌
					enemyX = 77;
					enemyY = (rand() % 20) + 2;
					playerBullet[i].fire = false;
				}
			}
		}
	}



}
