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
#define UP         72 // 방향키 설정
#define DOWN       80
#define LEFT       75
#define RIGHT      77


int rows,cols;               // board size   퍼즐 크기
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
void Cursor(void);              // 커서 지우기
void Score(void);               // 점수매기기
int main(void)
{
	start_page(); // 테두리 그림 함수
	black_word(); // 초기 시작 화면 글자 함수
	white_board(); // black_word함수의 글자 지우기 함수
	infor(); // 시작시 설정값 입력 및 조작방법 printf 함수
	init(); 
	Cursor(); // 커서깜빡임을 지우는 함수
	Score(); // 점수 매기기 함수
    gotoxy(60, 23);
	printf("Done!");
	gotoxy(0, 28);
	return 0;
}
int judge() // Extra : 가로줄을 판단하여 첫번 째 가로줄을 정렬 했을경우 알림을 표시한다. 
{
	int i, j;
	int temp = 0; 
	int n = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			temp++; // temp == 1부터 시작
			if ((temp - 1) % rows == 0) // piece[j][i]가 제 위치에 자리 했을 때매다 temp 값이 1씩 증가됨
			{
				if (temp <= rows) // 0번째 줄 printf방지
					continue;
				gotoxy(46, 16 + n);
				printf("◎ %d 번째 줄 완성!!!", temp / rows);
				n++;
			}
			if (piece[i][j] != (j + 1) + i*rows)
				return 1;


		}
	}
	gotoxy(46, 16 + n);
	printf("◎ %d 번째 줄 완성!!!", temp / rows);
	return 0;
} 
void move(int key) // Extra : 방향키 추가 , 게임 재시작
{
	int i, j;
	switch (key)
	{
	case KEY_4:      // left
	case KEY_A:
	case LEFT:
		if (blank_i < rows - 1)
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i + 1];
			blank_i++;
		}
		break;
	case KEY_6:      // right
	case KEY_D:
	case RIGHT:
		if (blank_i > 0)
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i - 1];
			blank_i--;
		}
		break;
	case KEY_2:      // down
	case KEY_X:
	case DOWN:
		if (blank_j > 0)
		{
			piece[blank_j][blank_i] = piece[blank_j - 1][blank_i];
			blank_j--;
		}
		break;
	case KEY_8:      // up
	case KEY_W:
	case UP:
		if (blank_j < rows - 1)
		{
			piece[blank_j][blank_i] = piece[blank_j + 1][blank_i];
			blank_j++;
		}
		break;
	case KEY_ESC:   // ECS 
		gotoxy(60, 23);
		printf("**Exit!**\n\n");
		gotoxy(0, 28);
		exit(0);
		break;
	case'\t':   // restart 기능 <TAB>
		gotoxy(46, 14);
		printf("                                ");
		init(); // 카드를 다시 섞는다.
		move_count = 0; // 움직인 횟수를 초기값으로 바꾼다.
		Score(); // 스코어 점수를 초기값으로 바꾼다.
		break;
	}
	piece[blank_j][blank_i] = rows*cols;

	draw_piece(blank_i, blank_j);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			gotoxy(5 + j * 6, 5 + i * 3);
			if (piece[i][j] == rows*cols)
				printf(" ");
			else
				printf("%d ", piece[i][j]);
		}
		printf("\n");
	}
} 
void init() // Extra : 게임 난이도 설정, 경고음 추가
{
	int i, j;
	int num;

	blank_i = 0;
	blank_j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			piece[i][j] = j + +i*rows;
	}

	srand((int)time(NULL));
	for (i = 0; i < Difficulty; i++) // Difficulty를 입력 받아 섞는 횟수 설정
	{ 
		// 섞는 횟수가 클수록 카드가 섞이는게 보임
		num = rand() % 5;
		switch (num)
		{
		case 1:
			move('w');
			break;
		case 2:
			move('x');
			break;
		case 3:
			move('a');
			break;
		case 4:
			move('d');
		}

	}
	draw_piece(blank_i, blank_j);
	printf("\a"); // 경고음 추가
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{

			gotoxy(5 + j * 6, 5 + i * 3); // (5,5)부터 채워짐 +6,+3 씩증가
			if (piece[i][j] == 0 || piece[i][j] == rows*cols)
				printf(" ");
			else
				printf("%d ", piece[i][j]);
		}
		printf("\n");
	}
}
void draw_piece(int i, int j)
{
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
		for (b = 0; b < cols; b++)
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
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} // 커서 이동
void start_page(void) // Extra : 게임 테두리 그리기 
{
	int i;
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□\n");
	for (i = 0; i < 13; i++) // 좌측 세로줄 그리기
	{
		printf("■\n");
		printf("□\n");
	}
	for (i = 0; i < 13; i++) // 우측 세로줄 그리기
	{
		gotoxy(80, i * 2); // □이 짝수 세로줄에 printf된다 & ■이 홀수 세로줄에 printf된다.  
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
int black_word(void) // 게임을 실행시 글자 printf("SLIDE GAME")
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
	if (i == '\n') // 아무키나 누를시 다음 함수로 넘어감.
		return 0;

}
void white_board(void) // black_word함수의 글자를 지워준다.
{
	int i;
	for (i = 2; i < 25; i++)
	{
		gotoxy(3, i);
		printf("                                                                           ");
	}
}
void infor(void) // Extra : 게임 난이도 설정
{
	gotoxy(3, 2);
	printf("Enter a size number (%d~%d) : ", MINP, MAXP);
	scanf("%d", &rows);
	gotoxy(50, 3);
	printf("<1.Esay> <2.Normal> <3.Hard>"); // 게임의 난이도 설정
	gotoxy(50, 2);
	printf("Set-up Difficulty : "); // Difficulty 전역 변수에 입력
	scanf("%d", &Difficulty);
	if (rows < MINP || rows > MAXP)
		rows = MINP;
	switch (Difficulty)
	{
	case 1: // 1 입력시 10번 섞는다.
		Difficulty = 10;
		break;
	case 2: // 2 입력시 50번 섞는다.
		Difficulty = 50;
		break;
	case 3: // 3 입력시 100번 섞는다.
		Difficulty = 100;
		break;
	default: // 그외의 숫자 입력시 50번 섞는다.
		Difficulty = 50;
	}
	cols = rows;
	gotoxy(50, 5);
	printf("⊙ KEY ⊙");
	gotoxy(50, 10);
	printf("Press ESC to exit.\n");
	gotoxy(50, 11);
	printf("Press TAB to Restart");
	gotoxy(50, 6);
	printf("  △         UP(8, W)");
	gotoxy(50, 7);
	printf("◁  ▷Left(4, A) / Right(6, D)");
	gotoxy(50, 8);
	printf("  ▽        Down(2, X)");
}
void Cursor(void) // 커서를 지워주는 라이브러리 함수
{
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}
void Score(void) // Extra : 게임 점수제 설정, 이동 횟수 표시
{
	score = rows*cols*Difficulty * 100; // 초기 점수 값 (난이도와 퍼즐 갯수에 따라 점수가 다름)
	gotoxy(46, 13);
	printf("★ MOVE COUNT ★    ★ SCORE ★\n");
	
	do
	{
		gotoxy(46, 14);
		printf("       %d               %d", move_count/2, score);
		move(getch());
		++move_count; // move_count 증가
		if (move_count >= 100) // move_count가 증가 할 때마다 score점수는 깎인다.
			score -= 10;       // 많이 증가할수록 점수는 더 많이 감소한다.
		else if (move_count >= 50)
			score -= 5;
		else if (move_count >= 10)
			score -= 2;
		else
			score -= 1;
		if (score < 0) // 점수가 음수일시, 게임 종료
		{
			gotoxy(60, 22);
			printf("Game OVER!!!!");
			break; // judge함수와 상관 없이 do~while문 탈출
		}
	} while (judge());
}