#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<locale.h>
#include<stdlib.h>
#include<windows.h>

#define WALL L'��'
#define BODY L'��'
#define FOOD L'��'
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK) & 0x1) ? 1 : 0)

// ��Ĭ�ϵ���ʼλ��
#define POS_X 24
#define POS_Y 5

// ��Ϸ״̬
enum GAME_STATUS {
	OK = 1,         // ��������
	KILL_BY_WALL,   // ײǽ
	KILL_BY_SELF,   // ײ������
	ESC             // �� ESC �������˳�
};

// �����߷���
enum DIRECTION {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

// ̰���ߣ�����ڵ�Ķ���
typedef struct SnakeNode {
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;

typedef struct SnakeNode* pSnakeNode;

// ̰����
typedef struct Sanke {
	pSnakeNode pSnake;    // ά�������ߵ�ָ�룬ָ����ͷ
	pSnakeNode pFood;     // ָ��ʳ���ָ��
	int Score;            // ��ǰ�ۻ��ķ���
	int FoodWeight;       // һ��ʳ��ķ���
	int SleepTime;        // �����ߵ�ʱ�䣬���ߵ�ʱ��Խ�̣����ƶ����ٶ�Խ�죬���ߵ�ʱ��Խ�������ƶ����ٶ�Խ��
	enum GAME_STATUS status;    // ��Ϸ��ǰ��״̬
	enum DIRECTION dir;         // �ߵ�ǰ�ߵķ���
}Snake, * pSnake;

// ���ù��λ��
void SetPos(int x, int y);

// ��Ϸ��ʼǰ��׼��
void GameStart(pSnake ps);

// ��ӡ��ӭ��Ϣ
void WelcomeToGame();

// ��ӡ��ͼ
void CreateMap();

// ��ʼ��̰����
void InitSnake(pSnake ps);

// ����ʳ��
void CreateFood(pSnake ps);

// ��Ϸ���е������߼�
void GameRun(pSnake ps);

// ��ӡ������Ϣ
void PrintHelpInfo();

// �����ƶ���ÿ����һ��
void SnakeMove(pSnake ps);

// �ж���ͷ��һ��Ҫ�ߵ�λ�ô��Ƿ���ʳ��
int NextIsFood(pSnake ps, pSnakeNode pNextNode);

// ��һ��Ҫ�ߵ�λ�ô���ʳ��ͳԵ�
void EatFood(pSnake ps, pSnakeNode pNextNode);

// ��һ��Ҫ�ߵ�λ�ô�����ʳ��Ͳ���
void NotEatFood(pSnake ps, pSnakeNode pNextNode);

// ���ײǽ
void KillByWall(pSnake ps);

// ���ײ���Լ�
void KillByMyself(pSnake ps);

// ��Ϸ����(�ƺ���)
void GameEnd(pSnake ps);

