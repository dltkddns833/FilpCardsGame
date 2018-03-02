#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>


#define MINP       3
#define MAXP       7
#define OFFSET     5
#define KEY_ESC    0x1B
#define KEY_8      '8'
#define KEY_2      '2'
#define KEY_4      '4'
#define KEY_6      '6'
#define KEY_W      'w'
#define KEY_X      'x'
#define KEY_A      'a'
#define KEY_D      'd'


int rows, cols;               // board size   퍼즐 크기
int piece[MAXP][MAXP];         // pieces      퍼즐 조각
int blank_i, blank_j;         // empty piece   빈 조각의 위치


void init();               // initialize
void move(int key);             // slide a piece
int judge();               // judge the end of the game
void draw_piece(int i, int j);   // draw a piece
void gotoxy(int x, int y);      // move cursor


int main(void)
{
	printf("Enter a size number (%d~%d) : ", MINP, MAXP); // 사용자로 부터 크기 입력받는다.
	scanf("%d", &rows);
	if (rows < MINP || rows > MAXP) // 범위 (3~7)을 벗어나면 최소크기 3으로 고정
		rows = MINP;
	cols = rows; // 가로줄과 세로줄의 카드 갯수는 같다.
	printf("Press ESC to exit.\n");
	printf("Left(4, A), Right(6, D), Down(2, X), Up(8, W)\n");


	init(); // 초기함수 시작

	do // 무조건 한번은 움직인다.
	{
		move(getch()); // 사용자로 부터 키를 입력받아 move함수로 이동

	} while (judge()); // judge 함수가 0을 return할 때 까지 무한 반복

	return 0; // 반복문 종료시 메인함수 종료
}

int judge()
{
	int i, j; // i:가로줄, j:세로줄
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (piece[i][j] != (j + 1) + i*rows) // piece[0][0]부터 piece[cols-1][rows-1]까지 진행하면서 한조각이라도 틀릴시 반복문(do~while) 계속진행
				return 1;

		}
	} // 모든 카드를 맞출 경우 반복문 탈출
	return 0; // 반복문 종료
}

void move(int key)
{
	int i, j; // 빈칸의 위치 찾기
	switch (key)
	{
	case KEY_4:      // left
	case KEY_A:
		if (blank_i < rows - 1) // 카드범위 밖에 나가지 않게 범위를 지정
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i + 1]; // 오른쪽에 있는 카드를 왼쪽(빈칸의 위치)으로 이동
			blank_i++; // 빈칸의 가로줄 1증가
		}
		break;
	case KEY_6:      // right
	case KEY_D:
		if (blank_i > 0) // 카드범위 밖에 나가지 않게 범위를 지정
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i - 1]; // 왼쪽에 있는 카드를 오른쪽(빈칸의 위치)으로 이동
			blank_i--; // 빈칸의 가로줄 1감소
		}
		break;
	case KEY_2:      // down
	case KEY_X:
		if (blank_j > 0) // 카드범위 밖에 나가지 않게 범위를 지정
		{
			piece[blank_j][blank_i] = piece[blank_j - 1][blank_i]; // 위쪽에 있는 카드를 아래(빈칸의 위치)로 이동
			blank_j--; //  빈칸의 세로줄 1감소
		}
		break;
	case KEY_8:      // up
	case KEY_W:
		if (blank_j < rows - 1) // 카드범위 밖에 나가지 않게 범위를 지정
		{
			piece[blank_j][blank_i] = piece[blank_j + 1][blank_i]; // 아래쪽에 있는 카드를 위(빈칸의 위치)로 이동
			blank_j++; // 빈칸의 세로줄 1증가
		}
		break;
	case KEY_ESC:   // ECS 
		gotoxy(0, rows * 3 + 1 + OFFSET);
		printf("Exit!\n\n");
		exit(0); // 프로그램 종료의 라이브러리 함수.
		break;
	}
	piece[blank_j][blank_i] = rows*cols; /* 빈칸을 rows X cols 값으로 지정, Judge 함수의 편의를 위해 기존
                                            0~rowsXcols-1의 범위를 1~rowsXcols로 지정 */
	draw_piece(blank_i, blank_j); // 빈칸의 위치에 퍼즐 조각을 없앰 & 빈칸을 제외한 숫자에 퍼즐그림 printf
	for (i = 0; i < rows; i++) 
	{
		for (j = 0; j < rows; j++)
		{
			gotoxy(5 + j * 6, 5 + i * 3);
			if (piece[i][j] == rows*rows) // 반복문으로 빈칸의 숫자(rowsXcols)를 배열 piece[rows][cols]에서 위치 찾기
				printf(" ");
			else
				printf("%d ", piece[i][j]); // 빈칸이 아닌 숫자는 원래 숫자 printf.
		}
		printf("\n");
	}
}
void init()
{
	int i, j; // 반복문을 위한 변수
	int num; // 난수 생성을 위한 변수
	blank_i = 0; // 초기 빈칸 위치 선정
	blank_j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			piece[i][j] = j + +i*rows; // 배열의 초기값 설정, 0~rowsXcols-1까지 설정
	}

	srand((int)time(NULL)); // time으로 인한 시간에 따라 다르게 나타나는 난수 설정
	for (i = 0; i < 10; i++) // 카들를 섞을 땐, 빈칸이 움직이면서 섞여야하기 때문에 난수의 경우의 수로 move함수로 이동하여 섞음.
	{ // 10번 섞어준다.
		num = rand() % 4; // 난수의 범위를 0~3의 숫자로 지정
		if (num == 1) // 1일 때 위로 이동
			move('w');
		else if (num == 2) // 2일 때 좌로 이동
			move("a");
		else if (num == 3) // 3일 때 우로 이동
			move("d");
		else if (num == 0) // 0일 때 아래로 이동
			move("x");
	}
	draw_piece(blank_i, blank_j); // 퍼즐 조각 그림 printf(빈칸의 위치엔 그림을 넣지 않는다.)
	for (i = 0; i < rows; i++) // 퍼즐 조각을 섞은 후, 초기 퍼즐 숫자 출력
	{
		for (j = 0; j < cols; j++)
		{

			gotoxy(5 + j * 6, 5 + i * 3); // (5,5)부터 채워짐 +6,+3 씩증가
			if (piece[i][j] == rows*cols) // piece[i][j] 가 빈칸의 위치일 때, 숫자 지우기
				printf(" ");
			else
				printf("%d ", piece[i][j]); // 빈칸의 위치가 아닌곳은 숫자 출력
		}
		printf("\n");
	}
}

void draw_piece(int i, int j) // i=blank_i, j=blank_j 빈칸의 위치 변수
{
	int a, b, c; // gotoxy로 인한 위치지정을 위한 벼수
	char piece_of_piece[3][7] = { // 퍼즐 조각 그림
		{ "┌─┐" },
		{ "│  │" },
		{ "└─┘" }
	};
	char blank[3][7] = { // 빈칸의 위치엔 조각 그림을 지운다.
		{ "      " },
		{ "      " },
		{ "      " }
	};
	for (c = 0; c < rows; c++)
	{
		for (b = 0; b < cols; b++)
		{
			for (a = 0; a < 3; a++) // piece_of_piece[0]~[2]까지 출력
			{
				gotoxy(3 + b * 6, a + c * 3 + 4); // 처음에 (3,4)로 시작
				printf("%s", piece_of_piece[a]);
			}
		}
	}// 처음엔 빈칸의 위치에도 카드 그림을 출력함

	for (a = 0; a < 3; a++)
	{
		gotoxy(i * 6 + 3, j * 3 + 4 + a); // 빈칸의 위치
		puts(blank[a]); // 카드 조각 그림을 지운다.
	}

}
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}