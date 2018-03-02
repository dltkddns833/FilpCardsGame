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
#define UP         72 // ����Ű ����
#define DOWN       80
#define LEFT       75
#define RIGHT      77


int rows,cols;               // board size   ���� ũ��
int piece[MAXP][MAXP];         // pieces      ���� ����
int blank_i, blank_j;         // empty piece   �� ������ ��ġ
int move_count;                   // �̵� Ƚ��
int Difficulty;                  // ���̵�
int score;                       // ����

void init();               // initialize
void move(int key);             // slide a piece
int judge();               // judge the end of the game
void draw_piece(int i, int j);   // draw a piece
void gotoxy(int x, int y);      // move cursor
int black_word(void);           // �ʱ����ȭ�� ����
void white_board(void);         // ���������
void start_page(void);          // �׵θ�
void infor(void);               // ���� ����
void Cursor(void);              // Ŀ�� �����
void Score(void);               // �����ű��
int main(void)
{
	start_page(); // �׵θ� �׸� �Լ�
	black_word(); // �ʱ� ���� ȭ�� ���� �Լ�
	white_board(); // black_word�Լ��� ���� ����� �Լ�
	infor(); // ���۽� ������ �Է� �� ���۹�� printf �Լ�
	init(); 
	Cursor(); // Ŀ���������� ����� �Լ�
	Score(); // ���� �ű�� �Լ�
    gotoxy(60, 23);
	printf("Done!");
	gotoxy(0, 28);
	return 0;
}
int judge() // Extra : �������� �Ǵ��Ͽ� ù�� ° �������� ���� ������� �˸��� ǥ���Ѵ�. 
{
	int i, j;
	int temp = 0; 
	int n = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			temp++; // temp == 1���� ����
			if ((temp - 1) % rows == 0) // piece[j][i]�� �� ��ġ�� �ڸ� ���� ���Ŵ� temp ���� 1�� ������
			{
				if (temp <= rows) // 0��° �� printf����
					continue;
				gotoxy(46, 16 + n);
				printf("�� %d ��° �� �ϼ�!!!", temp / rows);
				n++;
			}
			if (piece[i][j] != (j + 1) + i*rows)
				return 1;


		}
	}
	gotoxy(46, 16 + n);
	printf("�� %d ��° �� �ϼ�!!!", temp / rows);
	return 0;
} 
void move(int key) // Extra : ����Ű �߰� , ���� �����
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
	case'\t':   // restart ��� <TAB>
		gotoxy(46, 14);
		printf("                                ");
		init(); // ī�带 �ٽ� ���´�.
		move_count = 0; // ������ Ƚ���� �ʱⰪ���� �ٲ۴�.
		Score(); // ���ھ� ������ �ʱⰪ���� �ٲ۴�.
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
void init() // Extra : ���� ���̵� ����, ����� �߰�
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
	for (i = 0; i < Difficulty; i++) // Difficulty�� �Է� �޾� ���� Ƚ�� ����
	{ 
		// ���� Ƚ���� Ŭ���� ī�尡 ���̴°� ����
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
	printf("\a"); // ����� �߰�
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{

			gotoxy(5 + j * 6, 5 + i * 3); // (5,5)���� ä���� +6,+3 ������
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
		{ "������" },
		{ "��  ��" },
		{ "������" }
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
				gotoxy(3 + b * 6, a + c * 3 + 4); // ó���� (3,4)�� ����
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
} // Ŀ�� �̵�
void start_page(void) // Extra : ���� �׵θ� �׸��� 
{
	int i;
	printf("������������������������������������������\n");
	for (i = 0; i < 13; i++) // ���� ������ �׸���
	{
		printf("��\n");
		printf("��\n");
	}
	for (i = 0; i < 13; i++) // ���� ������ �׸���
	{
		gotoxy(80, i * 2); // ���� ¦�� �����ٿ� printf�ȴ� & ���� Ȧ�� �����ٿ� printf�ȴ�.  
		printf("��");
		gotoxy(80, i * 2 + 1);
		printf("��");
	}
	gotoxy(0, 26);
	printf("������������������������������������������\n");
	gotoxy(82, 25);
	printf(" Seoul Tech, Computer Programming");
	gotoxy(82, 26);
	printf("                 12184407  �̻��");
}
int black_word(void) // ������ ����� ���� printf("SLIDE GAME")
{
	int i = 0;
	gotoxy(10, 6);
	printf(" ����  ��       ����  ����    �����");
	gotoxy(10, 7);
	printf("��       ��         ��    ��   ��   ��");
	gotoxy(10, 8);
	printf(" ����  ��         ��    ��    ��  �����");
	gotoxy(10, 9);
	printf("      �� ��         ��    ��   ��   ��");
	gotoxy(10, 10);
	printf("����   ����� ����  ����    �����");

	gotoxy(25, 15);
	printf(" �����     ��     ��        �� �����");
	gotoxy(25, 16);
	printf("��           ���    ���    ��� ��");
	gotoxy(25, 17);
	printf("��   ���   ��  ��   �� ��  �� �� �����");
	gotoxy(25, 18);
	printf("��     ��  �����  ��  ���  �� ��");
	gotoxy(25, 19);
	printf(" ����� ��      �� ��   ��   �� �����");
	gotoxy(23, 23);
	printf("--Press any key to start!--");
	getch(i);
	if (i == '\n') // �ƹ�Ű�� ������ ���� �Լ��� �Ѿ.
		return 0;

}
void white_board(void) // black_word�Լ��� ���ڸ� �����ش�.
{
	int i;
	for (i = 2; i < 25; i++)
	{
		gotoxy(3, i);
		printf("                                                                           ");
	}
}
void infor(void) // Extra : ���� ���̵� ����
{
	gotoxy(3, 2);
	printf("Enter a size number (%d~%d) : ", MINP, MAXP);
	scanf("%d", &rows);
	gotoxy(50, 3);
	printf("<1.Esay> <2.Normal> <3.Hard>"); // ������ ���̵� ����
	gotoxy(50, 2);
	printf("Set-up Difficulty : "); // Difficulty ���� ������ �Է�
	scanf("%d", &Difficulty);
	if (rows < MINP || rows > MAXP)
		rows = MINP;
	switch (Difficulty)
	{
	case 1: // 1 �Է½� 10�� ���´�.
		Difficulty = 10;
		break;
	case 2: // 2 �Է½� 50�� ���´�.
		Difficulty = 50;
		break;
	case 3: // 3 �Է½� 100�� ���´�.
		Difficulty = 100;
		break;
	default: // �׿��� ���� �Է½� 50�� ���´�.
		Difficulty = 50;
	}
	cols = rows;
	gotoxy(50, 5);
	printf("�� KEY ��");
	gotoxy(50, 10);
	printf("Press ESC to exit.\n");
	gotoxy(50, 11);
	printf("Press TAB to Restart");
	gotoxy(50, 6);
	printf("  ��         UP(8, W)");
	gotoxy(50, 7);
	printf("��  ��Left(4, A) / Right(6, D)");
	gotoxy(50, 8);
	printf("  ��        Down(2, X)");
}
void Cursor(void) // Ŀ���� �����ִ� ���̺귯�� �Լ�
{
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}
void Score(void) // Extra : ���� ������ ����, �̵� Ƚ�� ǥ��
{
	score = rows*cols*Difficulty * 100; // �ʱ� ���� �� (���̵��� ���� ������ ���� ������ �ٸ�)
	gotoxy(46, 13);
	printf("�� MOVE COUNT ��    �� SCORE ��\n");
	
	do
	{
		gotoxy(46, 14);
		printf("       %d               %d", move_count/2, score);
		move(getch());
		++move_count; // move_count ����
		if (move_count >= 100) // move_count�� ���� �� ������ score������ ���δ�.
			score -= 10;       // ���� �����Ҽ��� ������ �� ���� �����Ѵ�.
		else if (move_count >= 50)
			score -= 5;
		else if (move_count >= 10)
			score -= 2;
		else
			score -= 1;
		if (score < 0) // ������ �����Ͻ�, ���� ����
		{
			gotoxy(60, 22);
			printf("Game OVER!!!!");
			break; // judge�Լ��� ��� ���� do~while�� Ż��
		}
	} while (judge());
}