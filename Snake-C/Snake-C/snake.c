#include"snake.h"

// ���ù��λ��
void SetPos(int x, int y)
{
	// ����豸���
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ݾ�����ù���λ��
	COORD pos = { x,y };
	SetConsoleCursorPosition(HOutput, pos);
}

// ��ӡ��Ϣ
void WelcomeToGame()
{
	// ��ӡ��ӭ��Ϣ
	SetPos(35, 10);
	printf("��ӭ����̰����С��Ϸ\n");
	SetPos(38, 20);
	system("pause");
	system("cls");

	// ��ӡ������Ϣ
	SetPos(15, 10);
	printf("�� �� . �� . �� . �� �ֱ�����ߵ��ƶ��� F3Ϊ���٣�F4Ϊ����\n");
	SetPos(15, 11);
	printf("�����ܵõ����ߵķ���\n");
	SetPos(38, 20);
	system("pause");
	system("cls");
}

// ��ӡ��ͼ
void CreateMap()
{
	// ��
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}

	// ��
	SetPos(0, 26);
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}

	// ��
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}

	// ��
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
}

// ��ʼ����
void InitSnake(pSnake ps)
{
	// ���� 5 ������Ľڵ�
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

		// ��������
		cur->x = POS_X + i * 2;
		cur->y = POS_Y;
		cur->next = NULL;

		// ͷ�巨
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

	// ��ӡ����
	cur = ps->pSnake;
	while (cur != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}

	// ��ʼ��̰���ߵ�������Ϣ
	ps->dir = RIGHT;
	ps->FoodWeight = 10;
	ps->pFood = NULL;
	ps->Score = 0;
	ps->SleepTime = 200;
	ps->status = OK;
}

// ����ʳ��
// 1.ʳ����������ֵ�->������������ֵ�
// 2.���������ǽ��
// 3.���겻�����ߵ�������
void CreateFood(pSnake ps)
{
	int x = 0;
	int y = 0;

again:
	do {
		x = rand() % 52 + 2;
		y = rand() % 24 + 1;
	} while (x % 2 != 0);

	// ʳ�ﲻ�ܺ������ͻ
	pSnakeNode pcur = ps->pSnake;
	while (pcur != NULL)
	{
		if (pcur->x == x && pcur->y == y)
		{
			goto again;
		}
		pcur = pcur->next;
	}

	// ����ʳ��
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
	// ���ÿ���̨����Ϣ�����ڴ�С��������
	system("mode con lines=30 cols=100");
	system("title ̰����");

	// ���ع��
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	GetConsoleCursorInfo(hOutput, &CursoInfo);    // ��ȡ����̨��Ϣ
	CursoInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursoInfo);

	// ��ӡ��ӭ��Ϣ
	WelcomeToGame();

	// ��ӡ��ͼ
	CreateMap();

	// ��ʼ����
	InitSnake(ps);

	// ����ʳ��
	CreateFood(ps);
}

// ��ӡ������Ϣ
void PrintHelpInfo()
{
	SetPos(61, 15);
	printf("1.���ܴ�ǽ������ҧ���Լ�\n");

	SetPos(61, 16);
	printf("2.�� �� . �� . �� . �� �������ߵ��ƶ�\n");

	SetPos(61, 17);
	printf("3.F3 Ϊ���٣�F4 Ϊ����\n");

	SetPos(61, 18);
	printf("4.ESC���˳���Ϸ��space����ͣ��Ϸ\n");
}

// ��Ϸ��ͣ�ͻָ�
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

// �ж���ͷ��һ��Ҫ�ߵ�λ�ô��Ƿ���ʳ��
int NextIsFood(pSnake ps, pSnakeNode pNextNode)
{
	if (ps->pFood->x == pNextNode->x && ps->pFood->y == pNextNode->y)
	{
		return 1;   // ��һ�����괦��ʳ��
	}
	else
	{
		return 0;
	}
}

// ��һ��Ҫ�ߵ�λ�ô���ʳ��ͳԵ�
void EatFood(pSnake ps, pSnakeNode pNextNode)
{
	// ͷ�巨
	pNextNode->next = ps->pSnake;
	ps->pSnake = pNextNode;
	pSnakeNode pcur = ps->pSnake;

	// ��ӡ����
	while (pcur != NULL)
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%lc", BODY);
		pcur = pcur->next;
	}

	ps->Score += ps->FoodWeight;

	// �ͷžɵ�ʳ��
	free(ps->pFood);
	ps->pFood = NULL;

	// �����µ�ʳ��
	CreateFood(ps);
}

// ��һ��Ҫ�ߵ�λ�ô�����ʳ��Ͳ���
void NotEatFood(pSnake ps, pSnakeNode pNextNode)
{
	// ͷ�巨
	pNextNode->next = ps->pSnake;
	ps->pSnake = pNextNode;
	pSnakeNode pcur = ps->pSnake;

	// ��ӡ����(����ӡβ�ڵ�)
	while (pcur->next->next != NULL)
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%lc", BODY);
		pcur = pcur->next;
	}

	// β�ڵ��ӡΪ�հײ��ͷ�β�ڵ�
	SetPos(pcur->next->x, pcur->next->y);
	printf("  ");
	free(pcur->next);
	pcur->next = NULL;

}

// ���ײǽ
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

// ���ײ���Լ�
void KillByMyself(pSnake ps)
{
	// �ӵڶ����ڵ㿪ʼ
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

// �����ƶ���ÿ����һ��
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

	// �����һ��λ����ʳ��
	if (NextIsFood(ps, pNextNode))
	{
		EatFood(ps, pNextNode);
	}
	else  // �������ʳ��
	{
		NotEatFood(ps, pNextNode);
	}

	// ���ײǽ
	KillByWall(ps);

	// ���ײ���Լ�
	KillByMyself(ps);
}

// ��Ϸ���е������߼�
void GameRun(pSnake ps)
{
	// ��ӡ������Ϣ
	PrintHelpInfo();

	do {
		// ��ǰ�������
		SetPos(61, 10);
		printf("�ܷ֣�%5d\n", ps->Score);

		SetPos(61, 11);
		printf("ʳ��ĵ÷֣�%d\n", ps->FoodWeight);

		// ��ⰴ��(�ϣ��£����ң�ESC���ո�F3��F4)
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
			// ��Ϸ��ͣ�ͻָ�
			pause();
		}
		// ��Ϸ����
		else if (KEY_PRESS(VK_F3))
		{
			// ��Ϸ���٣�����ʱ���̣��÷�Ȩ������
			if (ps->SleepTime >= 80)
			{
				ps->SleepTime -= 30;
				ps->FoodWeight += 2;
			}

		}
		// ��Ϸ����
		else if (KEY_PRESS(VK_F4))
		{
			// ��Ϸ���٣�����ʱ��䳤���÷�Ȩ�ؼ���
			if (ps->FoodWeight > 2)
			{
				ps->SleepTime += 30;
				ps->FoodWeight -= 2;
			}
		}

		// ˯��һ��
		Sleep(ps->SleepTime);

		// ��һ��
		SnakeMove(ps);
	} while (ps->status == OK);

}

// ��Ϸ����(�ƺ���)
void GameEnd(pSnake ps)
{
	SetPos(20, 12);
	switch (ps->status)
	{
	case ESC:
		printf("�����˳�\n");
		break;
	case KILL_BY_WALL:
		printf("���ź���ײǽ�ˣ���Ϸ����\n");
		break;
	case KILL_BY_SELF:
		printf("���ź���ҧ���Լ��ˣ���Ϸ����\n");
		break;
	}

	// �ͷ�����Ľڵ�
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
