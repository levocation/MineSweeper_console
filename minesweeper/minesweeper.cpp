#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

enum ConsoleColor {
	CC_BLACK,
	CC_DARKBLUE,
	CC_DARKGREEN,
	CC_DARKCYAN,
	CC_DARKRED,
	CC_DARKMAGENTA,
	CC_DARKYELLOW,
	CC_GRAY,
	CC_DARKGRAY,
	CC_BLUE,
	CC_GREEN,
	CC_CYAN,
	CC_RED,
	CC_MAGENTA,
	CC_YELLOW,
	CC_WHITE,
	CC_LIGHTGRAY = 7,
	CC_ORIGINAL = 7,
	CC_ORIGINALFONT = 7,
	CC_ORIGINALBG = 0
};

int minePos[11][11] = { 0, };
int mineCounter[11][11] = { 0, };
int isOpened[11][11] = { 0, };

void setColor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(bgcolor << 4) | color);
}

void printMine(int value) {
	switch (value)
	{
	case 0:
		printf("□");
		break;
	case 1:
		printf("①");
		break;
	case 2:
		printf("②");
		break;
	case 3:
		printf("③");
		break;
	case 4:
		printf("④");
		break;
	case 5:
		printf("⑤");
		break;
	case 6:
		printf("⑥");
		break;
	case 7:
		printf("⑦");
		break;
	case 8:
		printf("⑧");
		break;
	default:
		printf("★");
		break;
	}
}

void findBlank(int x, int y) {
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i < 0 || i > 10 || j < 0 || j > 10) {
				continue;
			}
			if (isOpened[i][j] == 0) {
				isOpened[i][j] = 1;
				if (mineCounter[i][j] == 0) {
					findBlank(i, j);
				}
			}
		}
	}
}

int main() {

	srand(time(NULL));

	const int MINE_COUNT = 15;

	for (int i = 0; i < 15; i++)
	{
		int r[2] = { rand() % 11, rand() % 11 };
		if (minePos[r[0]][r[1]] == 1) {
			i--;
			continue;
		}
		else {
			minePos[r[0]][r[1]] = 1;
			mineCounter[r[0]][r[1]] = 9;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					if (r[0] + x < 0 || r[1] + y < 0 || r[0] + x > 10 || r[1] + y > 10 || (x == 0 && y == 0)) {
						continue;
					}
					mineCounter[r[0] + x][r[1] + y]++;
				}
			}
		}
	}

	int getPos[2] = { 1,1 };

	while (1 == 1)
	{
		system("cls");
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (isOpened[i][j] == 1) {
					printMine(mineCounter[i][j]);
				}
				else {
					printf("▩");
				}
			}
			printf("\n");
		}

		printf("\n1~11 사이의 숫자로 x,y좌표를 선택하세요.\n");
		scanf_s("%d %d", &getPos[0], &getPos[1]);

		if (getPos[0] < 1 || getPos[0] > 11 || getPos[1] < 1 || getPos[1] > 11) {
			printf("잘못된 입력입니다.\n\n");
			system("pause");
		}
		else if (isOpened[getPos[1] - 1][getPos[0] - 1] == 0) {
			isOpened[getPos[1] - 1][getPos[0] - 1] = 1;

			if (minePos[getPos[1] - 1][getPos[0] - 1] == 1) {
				system("cls");
				for (int i = 0; i < 11; i++)
				{
					for (int j = 0; j < 11; j++)
					{
						if (getPos[1] - 1 == i && getPos[0] - 1 == j) {
							setColor(CC_RED, CC_ORIGINALBG);
						}
						else {
							setColor(CC_ORIGINALFONT, CC_ORIGINALBG);
						}
						printMine(mineCounter[i][j]);
					}
					printf("\n");
				}
				printf("지뢰 발견!\n\n");
				return 0;
			}
			else if (minePos[getPos[1] - 1][getPos[0] - 1] == 0) {
				findBlank(getPos[0] - 1, getPos[1] - 1);
			}
		}
		else {
			printf("이미 열려있는 칸입니다.\n\n");
			system("pause");
		}
	}

	return 0;
}