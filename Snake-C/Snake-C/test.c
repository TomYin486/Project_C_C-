#include"snake.h"

void test()
{
	int ch = 0;
	do {
		// 创建贪吃蛇
		Snake snake = { 0 };
		GameStart(&snake);    // 游戏开始前的初始
		GameRun(&snake);      // 玩游戏的过程
		GameEnd(&snake);      // 善后的工作

		SetPos(20, 15);
		printf("再来一局吗? (Y/N):");
		ch = getchar();
		getchar();        // 清理 \n
	} while (ch == 'Y');
}

int main()
{
	// 修改适配本地中文环境
	setlocale(LC_ALL, "");

	// 贪吃蛇游戏的测试
	test();
	SetPos(0, 27);
	return 0;
}
