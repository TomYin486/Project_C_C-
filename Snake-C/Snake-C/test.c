#include"snake.h"

void test()
{
	int ch = 0;
	do {
		// ����̰����
		Snake snake = { 0 };
		GameStart(&snake);    // ��Ϸ��ʼǰ�ĳ�ʼ
		GameRun(&snake);      // ����Ϸ�Ĺ���
		GameEnd(&snake);      // �ƺ�Ĺ���

		SetPos(20, 15);
		printf("����һ����? (Y/N):");
		ch = getchar();
		getchar();        // ���� \n
	} while (ch == 'Y');
}

int main()
{
	// �޸����䱾�����Ļ���
	setlocale(LC_ALL, "");

	// ̰������Ϸ�Ĳ���
	test();
	SetPos(0, 27);
	return 0;
}
