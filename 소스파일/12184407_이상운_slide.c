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


int rows, cols;               // board size   ���� ũ��
int piece[MAXP][MAXP];         // pieces      ���� ����
int blank_i, blank_j;         // empty piece   �� ������ ��ġ


void init();               // initialize
void move(int key);             // slide a piece
int judge();               // judge the end of the game
void draw_piece(int i, int j);   // draw a piece
void gotoxy(int x, int y);      // move cursor


int main(void)
{
	printf("Enter a size number (%d~%d) : ", MINP, MAXP); // ����ڷ� ���� ũ�� �Է¹޴´�.
	scanf("%d", &rows);
	if (rows < MINP || rows > MAXP) // ���� (3~7)�� ����� �ּ�ũ�� 3���� ����
		rows = MINP;
	cols = rows; // �����ٰ� �������� ī�� ������ ����.
	printf("Press ESC to exit.\n");
	printf("Left(4, A), Right(6, D), Down(2, X), Up(8, W)\n");


	init(); // �ʱ��Լ� ����

	do // ������ �ѹ��� �����δ�.
	{
		move(getch()); // ����ڷ� ���� Ű�� �Է¹޾� move�Լ��� �̵�

	} while (judge()); // judge �Լ��� 0�� return�� �� ���� ���� �ݺ�

	return 0; // �ݺ��� ����� �����Լ� ����
}

int judge()
{
	int i, j; // i:������, j:������
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (piece[i][j] != (j + 1) + i*rows) // piece[0][0]���� piece[cols-1][rows-1]���� �����ϸ鼭 �������̶� Ʋ���� �ݺ���(do~while) �������
				return 1;

		}
	} // ��� ī�带 ���� ��� �ݺ��� Ż��
	return 0; // �ݺ��� ����
}

void move(int key)
{
	int i, j; // ��ĭ�� ��ġ ã��
	switch (key)
	{
	case KEY_4:      // left
	case KEY_A:
		if (blank_i < rows - 1) // ī����� �ۿ� ������ �ʰ� ������ ����
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i + 1]; // �����ʿ� �ִ� ī�带 ����(��ĭ�� ��ġ)���� �̵�
			blank_i++; // ��ĭ�� ������ 1����
		}
		break;
	case KEY_6:      // right
	case KEY_D:
		if (blank_i > 0) // ī����� �ۿ� ������ �ʰ� ������ ����
		{
			piece[blank_j][blank_i] = piece[blank_j][blank_i - 1]; // ���ʿ� �ִ� ī�带 ������(��ĭ�� ��ġ)���� �̵�
			blank_i--; // ��ĭ�� ������ 1����
		}
		break;
	case KEY_2:      // down
	case KEY_X:
		if (blank_j > 0) // ī����� �ۿ� ������ �ʰ� ������ ����
		{
			piece[blank_j][blank_i] = piece[blank_j - 1][blank_i]; // ���ʿ� �ִ� ī�带 �Ʒ�(��ĭ�� ��ġ)�� �̵�
			blank_j--; //  ��ĭ�� ������ 1����
		}
		break;
	case KEY_8:      // up
	case KEY_W:
		if (blank_j < rows - 1) // ī����� �ۿ� ������ �ʰ� ������ ����
		{
			piece[blank_j][blank_i] = piece[blank_j + 1][blank_i]; // �Ʒ��ʿ� �ִ� ī�带 ��(��ĭ�� ��ġ)�� �̵�
			blank_j++; // ��ĭ�� ������ 1����
		}
		break;
	case KEY_ESC:   // ECS 
		gotoxy(0, rows * 3 + 1 + OFFSET);
		printf("Exit!\n\n");
		exit(0); // ���α׷� ������ ���̺귯�� �Լ�.
		break;
	}
	piece[blank_j][blank_i] = rows*cols; /* ��ĭ�� rows X cols ������ ����, Judge �Լ��� ���Ǹ� ���� ����
                                            0~rowsXcols-1�� ������ 1~rowsXcols�� ���� */
	draw_piece(blank_i, blank_j); // ��ĭ�� ��ġ�� ���� ������ ���� & ��ĭ�� ������ ���ڿ� ����׸� printf
	for (i = 0; i < rows; i++) 
	{
		for (j = 0; j < rows; j++)
		{
			gotoxy(5 + j * 6, 5 + i * 3);
			if (piece[i][j] == rows*rows) // �ݺ������� ��ĭ�� ����(rowsXcols)�� �迭 piece[rows][cols]���� ��ġ ã��
				printf(" ");
			else
				printf("%d ", piece[i][j]); // ��ĭ�� �ƴ� ���ڴ� ���� ���� printf.
		}
		printf("\n");
	}
}
void init()
{
	int i, j; // �ݺ����� ���� ����
	int num; // ���� ������ ���� ����
	blank_i = 0; // �ʱ� ��ĭ ��ġ ����
	blank_j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			piece[i][j] = j + +i*rows; // �迭�� �ʱⰪ ����, 0~rowsXcols-1���� ����
	}

	srand((int)time(NULL)); // time���� ���� �ð��� ���� �ٸ��� ��Ÿ���� ���� ����
	for (i = 0; i < 10; i++) // ī�鸦 ���� ��, ��ĭ�� �����̸鼭 �������ϱ� ������ ������ ����� ���� move�Լ��� �̵��Ͽ� ����.
	{ // 10�� �����ش�.
		num = rand() % 4; // ������ ������ 0~3�� ���ڷ� ����
		if (num == 1) // 1�� �� ���� �̵�
			move('w');
		else if (num == 2) // 2�� �� �·� �̵�
			move("a");
		else if (num == 3) // 3�� �� ��� �̵�
			move("d");
		else if (num == 0) // 0�� �� �Ʒ��� �̵�
			move("x");
	}
	draw_piece(blank_i, blank_j); // ���� ���� �׸� printf(��ĭ�� ��ġ�� �׸��� ���� �ʴ´�.)
	for (i = 0; i < rows; i++) // ���� ������ ���� ��, �ʱ� ���� ���� ���
	{
		for (j = 0; j < cols; j++)
		{

			gotoxy(5 + j * 6, 5 + i * 3); // (5,5)���� ä���� +6,+3 ������
			if (piece[i][j] == rows*cols) // piece[i][j] �� ��ĭ�� ��ġ�� ��, ���� �����
				printf(" ");
			else
				printf("%d ", piece[i][j]); // ��ĭ�� ��ġ�� �ƴѰ��� ���� ���
		}
		printf("\n");
	}
}

void draw_piece(int i, int j) // i=blank_i, j=blank_j ��ĭ�� ��ġ ����
{
	int a, b, c; // gotoxy�� ���� ��ġ������ ���� ����
	char piece_of_piece[3][7] = { // ���� ���� �׸�
		{ "������" },
		{ "��  ��" },
		{ "������" }
	};
	char blank[3][7] = { // ��ĭ�� ��ġ�� ���� �׸��� �����.
		{ "      " },
		{ "      " },
		{ "      " }
	};
	for (c = 0; c < rows; c++)
	{
		for (b = 0; b < cols; b++)
		{
			for (a = 0; a < 3; a++) // piece_of_piece[0]~[2]���� ���
			{
				gotoxy(3 + b * 6, a + c * 3 + 4); // ó���� (3,4)�� ����
				printf("%s", piece_of_piece[a]);
			}
		}
	}// ó���� ��ĭ�� ��ġ���� ī�� �׸��� �����

	for (a = 0; a < 3; a++)
	{
		gotoxy(i * 6 + 3, j * 3 + 4 + a); // ��ĭ�� ��ġ
		puts(blank[a]); // ī�� ���� �׸��� �����.
	}

}
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}