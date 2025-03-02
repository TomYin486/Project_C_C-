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
	// ��Ų��úõ���
	char mine[ROWS][COLS];

	// ����Ų���׵���Ϣ
	char show[ROWS][COLS];

	// ��ʼ������
	InitBoard(mine, ROWS, COLS, '0');   // mine�����ʼȫ�� '0'
	InitBoard(show, ROWS, COLS, '*');   // show�����ʼȫ�� '*'

	// ��ӡ����
	// DisplayBoard(mine, ROW, COL);
	// DisplayBoard(show, ROW, COL);

	// ������
	SetMine(mine, ROW, COL);

	// ��ӡ����
	DisplayBoard(mine, ROW, COL);

	// �Ų���
	FindMine(mine, show, ROW, COL);
}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��");
		scanf("%d", &input);
		printf("\n");

		switch (input)
		{
		case 1:     // ����ʹ��ö�ٵķ�ʽ����ѡ�񣬸�����  case Play:
			game();
			break;
		case 0:     // case Exit;
			break;
		default:
			printf("����������������룺\n");
			break;
		}

	} while (input);

	return 0;
}
