#include"snake.h"

// 设置光标位置
void SetPos(int x, int y)
{
	// 获得设备句柄
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// 根据句柄设置光标的位置
	COORD pos = { x,y };
	SetConsoleCursorPosition(HOutput, pos);
}

// 打印信息
void WelcomeToGame()
{
	// 打印欢迎信息
	SetPos(35, 10);
	printf("欢迎来到贪吃蛇小游戏\n");
	SetPos(38, 20);
	system("pause");
	system("cls");

	// 打印功能信息
	SetPos(15, 10);
	printf("用 ↑ . ↓ . ← . → 分别控制蛇的移动， F3为加速，F4为减速\n");
	SetPos(15, 11);
	printf("加速能得到更高的分数\n");
	SetPos(38, 20);
	system("pause");
	system("cls");
}

// 打印地图
void CreateMap()
{
	// 上
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}

	// 下
	SetPos(0, 26);
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}

	// 左
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}

	// 右
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
}

// 初始化蛇
void InitSnake(pSnake ps)
{
	// 创建 5 个蛇身的节点
	int i = 0;
	pSnakeNode cur = NULL;
	for (i = 0; i < 5; i++)
	{
		cur = (pSnakeNode)malloc(sizeof(SnakeNode));
		if (cur == NULL)
		{
			perror("InitSnake():malloc fail!");
			return;
		}

		// 设置坐标
		cur->x = POS_X + i * 2;
		cur->y = POS_Y;
		cur->next = NULL;

		// 头插法
		if (ps->pSnake == NULL)
		{
			ps->pSnake = cur;
		}
		else
		{
			cur->next = ps->pSnake;
			ps->pSnake = cur;
		}
	}

	// 打印蛇身
	cur = ps->pSnake;
	while (cur != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}

	// 初始化贪吃蛇的其他信息
	ps->dir = RIGHT;
	ps->FoodWeight = 10;
	ps->pFood = NULL;
	ps->Score = 0;
	ps->SleepTime = 200;
	ps->status = OK;
}

// 创建食物
// 1.食物是随机出现的->坐标是随机出现的
// 2.坐标必须在墙内
// 3.坐标不能在蛇的身体上
void CreateFood(pSnake ps)
{
	int x = 0;
	int y = 0;

again:
	do {
		x = rand() % 52 + 2;
		y = rand() % 24 + 1;
	} while (x % 2 != 0);

	// 食物不能和蛇身冲突
	pSnakeNode pcur = ps->pSnake;
	while (pcur != NULL)
	{
		if (pcur->x == x && pcur->y == y)
		{
			goto again;
		}
		pcur = pcur->next;
	}

	// 创建食物
	pSnakeNode pFood = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pFood == NULL)
	{
		perror("CreateFood:malloc fail!");
		return;
	}

	pFood->x = x;
	pFood->y = y;

	ps->pFood = pFood;
	SetPos(x, y);
	wprintf(L"%lc", FOOD);
}

void GameStart(pSnake ps)
{
	// 设置控制台的信息，窗口大小，窗口名
	system("mode con lines=30 cols=100");
	system("title 贪吃蛇");

	// 隐藏光标
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	GetConsoleCursorInfo(hOutput, &CursoInfo);    // 获取控制台信息
	CursoInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursoInfo);

	// 打印欢迎信息
	WelcomeToGame();

	// 打印地图
	CreateMap();

	// 初始化蛇
	InitSnake(ps);

	// 创建食物
	CreateFood(ps);
}

// 打印帮助信息
void PrintHelpInfo()
{
	SetPos(61, 15);
	printf("1.不能穿墙，不能咬到自己\n");

	SetPos(61, 16);
	printf("2.用 ↑ . ↓ . ← . → 来控制蛇的移动\n");

	SetPos(61, 17);
	printf("3.F3 为加速，F4 为减速\n");

	SetPos(61, 18);
	printf("4.ESC：退出游戏，space：暂停游戏\n");
}

// 游戏暂停和恢复
void pause()
{
	while (1)
	{
		Sleep(100);
		if (KEY_PRESS(VK_SPACE))
		{
			break;
		}
	}
}

// 判断蛇头下一步要走的位置处是否是食物
int NextIsFood(pSnake ps, pSnakeNode pNextNode)
{
	if (ps->pFood->x == pNextNode->x && ps->pFood->y == pNextNode->y)
	{
		return 1;   // 下一个坐标处是食物
	}
	else
	{
		return 0;
	}
}

// 下一步要走的位置处是食物，就吃掉
void EatFood(pSnake ps, pSnakeNode pNextNode)
{
	// 头插法
	pNextNode->next = ps->pSnake;
	ps->pSnake = pNextNode;
	pSnakeNode pcur = ps->pSnake;

	// 打印蛇身
	while (pcur != NULL)
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%lc", BODY);
		pcur = pcur->next;
	}

	ps->Score += ps->FoodWeight;

	// 释放旧的食物
	free(ps->pFood);
	ps->pFood = NULL;

	// 创建新的食物
	CreateFood(ps);
}

// 下一步要走的位置处不是食物，就不吃
void NotEatFood(pSnake ps, pSnakeNode pNextNode)
{
	// 头插法
	pNextNode->next = ps->pSnake;
	ps->pSnake = pNextNode;
	pSnakeNode pcur = ps->pSnake;

	// 打印蛇身(不打印尾节点)
	while (pcur->next->next != NULL)
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%lc", BODY);
		pcur = pcur->next;
	}

	// 尾节点打印为空白并释放尾节点
	SetPos(pcur->next->x, pcur->next->y);
	printf("  ");
	free(pcur->next);
	pcur->next = NULL;

}

// 检测撞墙
void KillByWall(pSnake ps)
{
	if (ps->pSnake->x == 0 ||
		ps->pSnake->x == 56 ||
		ps->pSnake->y == 0 ||
		ps->pSnake->y == 26)
	{
		ps->status = KILL_BY_WALL;
	}
}

// 检测撞到自己
void KillByMyself(pSnake ps)
{
	// 从第二个节点开始
	pSnakeNode pcur = ps->pSnake->next;
	while (pcur != NULL)
	{
		if (pcur->x == ps->pSnake->x && pcur->y == ps->pSnake->y)
		{
			ps->status = KILL_BY_SELF;
			return;
		}
		pcur = pcur->next;
	}
}

// 蛇身移动，每次走一步
void SnakeMove(pSnake ps)
{
	pSnakeNode pNextNode = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pNextNode == NULL)
	{
		perror("SnakeMove():malloc fail!");
		return;
	}
	pNextNode->next = NULL;

	switch (ps->dir)
	{
	case UP:
		pNextNode->x = ps->pSnake->x;
		pNextNode->y = ps->pSnake->y - 1;
		break;
	case DOWN:
		pNextNode->x = ps->pSnake->x;
		pNextNode->y = ps->pSnake->y + 1;
		break;
	case LEFT:
		pNextNode->x = ps->pSnake->x - 2;
		pNextNode->y = ps->pSnake->y;
		break;
	case RIGHT:
		pNextNode->x = ps->pSnake->x + 2;
		pNextNode->y = ps->pSnake->y;
		break;
	}

	// 如果下一个位置是食物
	if (NextIsFood(ps, pNextNode))
	{
		EatFood(ps, pNextNode);
	}
	else  // 如果不是食物
	{
		NotEatFood(ps, pNextNode);
	}

	// 检测撞墙
	KillByWall(ps);

	// 检测撞到自己
	KillByMyself(ps);
}

// 游戏运行的整个逻辑
void GameRun(pSnake ps)
{
	// 打印帮助信息
	PrintHelpInfo();

	do {
		// 当前分数情况
		SetPos(61, 10);
		printf("总分：%5d\n", ps->Score);

		SetPos(61, 11);
		printf("食物的得分：%d\n", ps->FoodWeight);

		// 检测按键(上，下，左，右，ESC，空格，F3，F4)
		if (KEY_PRESS(VK_UP) && ps->dir != DOWN)
		{
			ps->dir = UP;
		}
		else if (KEY_PRESS(VK_DOWN) && ps->dir != UP)
		{
			ps->dir = DOWN;
		}
		else if (KEY_PRESS(VK_LEFT) && ps->dir != RIGHT)
		{
			ps->dir = LEFT;
		}
		else if (KEY_PRESS(VK_RIGHT) && ps->dir != LEFT)
		{
			ps->dir = RIGHT;
		}
		else if (KEY_PRESS(VK_ESCAPE))
		{
			ps->status = ESC;
			break;
		}
		else if (KEY_PRESS(VK_SPACE) && ps->dir != UP)
		{
			// 游戏暂停和恢复
			pause();
		}
		// 游戏加速
		else if (KEY_PRESS(VK_F3))
		{
			// 游戏加速，休眠时间变短，得分权重增加
			if (ps->SleepTime >= 80)
			{
				ps->SleepTime -= 30;
				ps->FoodWeight += 2;
			}

		}
		// 游戏减速
		else if (KEY_PRESS(VK_F4))
		{
			// 游戏减速，休眠时间变长，得分权重减少
			if (ps->FoodWeight > 2)
			{
				ps->SleepTime += 30;
				ps->FoodWeight -= 2;
			}
		}

		// 睡眠一下
		Sleep(ps->SleepTime);

		// 走一步
		SnakeMove(ps);
	} while (ps->status == OK);

}

// 游戏结束(善后工作)
void GameEnd(pSnake ps)
{
	SetPos(20, 12);
	switch (ps->status)
	{
	case ESC:
		printf("正常退出\n");
		break;
	case KILL_BY_WALL:
		printf("很遗憾，撞墙了，游戏结束\n");
		break;
	case KILL_BY_SELF:
		printf("很遗憾，咬到自己了，游戏结束\n");
		break;
	}

	// 释放蛇身的节点
	pSnakeNode pcur = ps->pSnake;
	pSnakeNode del = NULL;
	while (pcur != NULL)
	{
		del = pcur;
		pcur = pcur->next;
		free(del);
		del = NULL;
	}

	free(ps->pFood);
	ps->pFood = NULL;
	ps = NULL;
}
