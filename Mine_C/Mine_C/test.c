#define _CRT_SECURE_NO_WARNINGS
#include"Game.h"

void menu()
{
	printf("***********************\n");
	printf("******  1. play  ******\n");
	printf("******  0. exit  ******\n");
	printf("***********************\n");
}

enum Option {
	Exit,
	Play
};

void game()
{
	// 存放布置好的雷
	char mine[ROWS][COLS];

	// 存放排查出雷的信息
	char show[ROWS][COLS];

	// 初始化棋盘
	InitBoard(mine, ROWS, COLS, '0');   // mine数组最开始全是 '0'
	InitBoard(show, ROWS, COLS, '*');   // show数组最开始全是 '*'

	// 打印棋盘
	// DisplayBoard(mine, ROW, COL);
	// DisplayBoard(show, ROW, COL);

	// 布置雷
	SetMine(mine, ROW, COL);

	// 打印棋盘
	DisplayBoard(mine, ROW, COL);

	// 排查雷
	FindMine(mine, show, ROW, COL);
}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
		printf("\n");

		switch (input)
		{
		case 1:     // 可以使用枚举的方式进行选择，更形象  case Play:
			game();
			break;
		case 0:     // case Exit;
			break;
		default:
			printf("输入错误请重新输入：\n");
			break;
		}

	} while (input);

	return 0;
}
