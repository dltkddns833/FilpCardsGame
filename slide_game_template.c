#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>


#define MINP      3
#define MAXP      7
#define OFFSET      5
#define KEY_ESC      0x1B
#define KEY_8      '8'
#define KEY_2      '2'
#define KEY_4      '4'
#define KEY_6      '6'
#define KEY_W      'w'
#define KEY_X      'x'
#define KEY_A      'a'
#define KEY_D      'd'
#define UP           72
#define DOWN         80
#define LEFT         75
#define RIGHT        77


int rows;               // board size   퍼즐 크기
int piece[MAXP][MAXP];         // pieces      퍼즐 조각
int blank_i, blank_j;         // empty piece   빈 조각의 위치
int move_count;                   // 이동 횟수
int Difficulty;                  // 난이도
int score;                       // 점수

void init();               // initialize
void move(int key);             // slide a piece
int judge();               // judge the end of the game
void draw_piece(int i, int j);   // draw a piece
void gotoxy(int x, int y);      // move cursor
int black_word(void);           // 초기시작화면 글자
void white_board(void);         // 글자지우기
void start_page(void);          // 테두리
void infor(void);               // 시작 설정


int main(void)
{
	start_page();
	black_word();
	white_board();
	infor();
	init();
	score = rows*Difficulty * 10000;
	do
	{
		move(getch());
		move_count++;
		if (move_count >= 100)
			score -= 100;
		else if (move_count >= 50)
			score -= 50;
		else if (move_count >= 10)
			score -= 25;
		else
			score -= 10;

		gotoxy(46, 13);
		printf("★ MOVE COUNT ★    ★ SCORE ★");
		gotoxy(46, 14);
		printf("       %d              %d", move_count, score);
		if (score < 0)
		{
			gotoxy(60, 22);
			printf("Game OVER!!!!");
			//break;
		}
	} while (judge());

	// exit the game
	gotoxy(60, 23);
	printf("Done!");
	gotoxy(0, 28);
	return 0;
}


// judge the end of the game
int judge()
{
	int i, j;
	int temp = 0;
	/* TODO
	퍼즐 조각 순서가 제대로 됐으면 1을 리턴
	아니면 0 리턴

	*/

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < rows; j++)
		{
			if (piece[i][j] != (j + 1) + i*rows)
				return 1;

		}
	}
	return 0;
}


// slide a piece
void move(int key)
{
	int i, j;
	// 상하좌우 key에 따라 
	// 빈조각과 숫자 조각의 위치를 바꾼다

	switch (key)
	{
	case KEY_4:      // left
	case KEY_A:
	case LEFT:
		// TODO
		if (blank_i < rows - 1)
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i + 1];
			blank_i++;
			gotoxy(rows + 1, rows);
		}
		break;
	case KEY_6:      // right
	case KEY_D:
	case RIGHT:
		// TODO
		if (blank_i > 0)
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i - 1];
			blank_i--;
			gotoxy(rows - 1, rows);
		}
		break;
	case KEY_2:      // down
	case KEY_X:
	case DOWN:
		// TODO

		if (blank_j > 0)
		{
			piece[blank_j][blank_i] = piece[blank_j - 1][blank_i];
			blank_j--;
			gotoxy(rows, rows - 1);
		}
		break;
	case KEY_8:      // up
	case KEY_W:
	case UP:
		// TODO
		if (blank_j < rows - 1)
		{
			piece[blank_j][blank_i] = piece[blank_j + 1][blank_i];
			blank_j++;
			gotoxy(rows, rows + 1);
		}
		break;
	case KEY_ESC:   // ECS 
					//gotoxy(0, rows * 3 + 1 + OFFSET);
		gotoxy(60, 23);
		printf("**Exit!**\n\n");
		gotoxy(0, 28);
		exit(0);
		break;
	case'\t':   // 다시 섞기
		init();
		break;
	}
	piece[blank_j][blank_i] = rows*rows;

	draw_piece(blank_i, blank_j);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < rows; j++)
		{
			gotoxy(5 + j * 6, 5 + i * 3);
			if (piece[i][j] == rows*rows)
				printf(" ");
			else
				printf("%d ", piece[i][j]);
		}
		printf("\n");
	}
}


// initialize
void init()
{
	int i, j;
	int X, x, Y, y;
	int temp;

	// initialize pieces and remove the last piece
	/* TODO
	2차배열 piece를 초기화
	마지막 퍼즐 조각은 0으로 빈 조각으로 만든다
	빈조각의 위치는 blank_i, blank_j로 나타낸다.

	*/
	blank_i = 0;
	blank_j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < rows; j++)
			piece[i][j] = j + +i*rows;
	}

	//draw_piece(rows, rows);
	// random shuffle
	/* TODO
	램덤으로 조각들을 섞는다
	random number generator: srand(), rand()
	p407 참고

	*/

	for (i = 0; i < Difficulty; i++)
	{
		X = rand() % rows;
		x = rand() % rows;
		Y = rand() % rows;
		y = rand() % rows;
		temp = piece[Y][X];
		piece[Y][X] = piece[y][x];
		piece[y][x] = temp;

		if (piece[Y][X] == 0)
		{
			blank_j = Y;
			blank_i = X;
		}
		else if (piece[y][x] == 0)
		{
			blank_j = y;
			blank_i = x;
		}
	}
	// draw pieces
	/* TODO
	모든 조각들을 그린다

	*/
	draw_piece(blank_i, blank_j);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < rows; j++)
		{

			gotoxy(5 + j * 6, 5 + i * 3); // (5,5)부터 채워짐 +6,+3 씩증가
			if (piece[i][j] == 0)
				printf(" ");
			else
				printf("%d ", piece[i][j]);
		}
		printf("\n");
	}
}


// draw a piece
void draw_piece(int i, int j)
{
	/* TODO
	{ 33, 45, 33, 10 }
	};
	퍼즐 조각을 그린다
	border characters: ┌─┐│└─┘
	*/

	//static n = 49;

	int a, b, c;
	char piece_of_piece[3][7] = {
		{ "┌─┐" },
		{ "│  │" },
		{ "└─┘" }
	};
	char blank[3][7] = {
		{ "      " },
		{ "      " },
		{ "      " }
	};
	for (c = 0; c < rows; c++)
	{
		for (b = 0; b < rows; b++)
		{
			for (a = 0; a < 3; a++)
			{
				gotoxy(3 + b * 6, a + c * 3 + 4); // 처음에 (3,4)로 시작
				printf("%s", piece_of_piece[a]);
			}
		}
	}

	for (a = 0; a < 3; a++)
	{
		gotoxy(i * 6 + 3, j * 3 + 4 + a);
		puts(blank[a]);
	}

}


// move cursor to (x,y)
// upper left corner is (0,0)
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void start_page(void)
{
	int i;
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□\n");
	for (i = 0; i < 13; i++)
	{
		printf("■\n");
		printf("□\n");
	}
	for (i = 0; i < 13; i++)
	{
		gotoxy(80, i * 2);
		printf("□");
		gotoxy(80, i * 2 + 1);
		printf("■");
	}
	gotoxy(0, 26);
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□\n");
	gotoxy(82, 25);
	printf(" Seoul Tech, Computer Programming");
	gotoxy(82, 26);
	printf("                 12184407  이상운");
}
int black_word(void)
{
	int i = 0;
	gotoxy(10, 6);
	printf(" ■■■  ■       ■■■  ■■■    ■■■■");
	gotoxy(10, 7);
	printf("■       ■         ■    ■   ■   ■");
	gotoxy(10, 8);
	printf(" ■■■  ■         ■    ■    ■  ■■■■");
	gotoxy(10, 9);
	printf("      ■ ■         ■    ■   ■   ■");
	gotoxy(10, 10);
	printf("■■■   ■■■■ ■■■  ■■■    ■■■■");

	gotoxy(25, 15);
	printf(" ■■■■     ■     ■        ■ ■■■■");
	gotoxy(25, 16);
	printf("■           ■■    ■■    ■■ ■");
	gotoxy(25, 17);
	printf("■   ■■   ■  ■   ■ ■  ■ ■ ■■■■");
	gotoxy(25, 18);
	printf("■     ■  ■■■■  ■  ■■  ■ ■");
	gotoxy(25, 19);
	printf(" ■■■■ ■      ■ ■   ■   ■ ■■■■");
	gotoxy(23, 23);
	printf("--Press any key to start!--");
	getch(i);
	if (i == '\n')
		return 0;

}
void white_board(void)
{
	int i;
	for (i = 2; i < 25; i++)
	{
		gotoxy(3, i);
		printf("                                                                           ");
	}
}
void infor(void)
{
	gotoxy(3, 2);
	printf("Enter a size number (%d~%d) : ", MINP, MAXP);
	scanf("%d", &rows);
	gotoxy(50, 2);
	printf("Set-up Difficulty : ");
	scanf("%d", &Difficulty);
	if (rows < MINP || rows > MAXP)
		rows = MINP;
	//cols = rows;
	gotoxy(50, 5);
	printf("⊙ KEY ⊙");
	gotoxy(50, 10);
	printf("Press ESC to exit.\n");
	gotoxy(50, 11);
	printf("Press TAB to shuffle");
	gotoxy(50, 6);
	printf("  △         UP(8, W)");
	gotoxy(50, 7);
	printf("◁  ▷Left(4, A) / Right(6, D)");
	gotoxy(50, 8);
	printf("  ▽        Down(2, X)");
}
