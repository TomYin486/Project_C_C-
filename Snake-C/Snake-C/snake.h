#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<locale.h>
#include<stdlib.h>
#include<windows.h>

#define WALL L'□'
#define BODY L'●'
#define FOOD L'★'
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK) & 0x1) ? 1 : 0)

// 蛇默认的起始位置
#define POS_X 24
#define POS_Y 5

// 游戏状态
enum GAME_STATUS {
	OK = 1,         // 正常运行
	KILL_BY_WALL,   // 撞墙
	KILL_BY_SELF,   // 撞到自身
	ESC             // 按 ESC 键正常退出
};

// 蛇行走方向
enum DIRECTION {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

// 贪吃蛇，蛇身节点的定义
typedef struct SnakeNode {
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;

typedef struct SnakeNode* pSnakeNode;

// 贪吃蛇
typedef struct Sanke {
	pSnakeNode pSnake;    // 维护整条蛇的指针，指向蛇头
	pSnakeNode pFood;     // 指向食物的指针
	int Score;            // 当前累积的分数
	int FoodWeight;       // 一个食物的分数
	int SleepTime;        // 蛇休眠的时间，休眠的时间越短，蛇移动的速度越快，休眠的时间越长，蛇移动的速度越慢
	enum GAME_STATUS status;    // 游戏当前的状态
	enum DIRECTION dir;         // 蛇当前走的方向
}Snake, * pSnake;

// 设置光标位置
void SetPos(int x, int y);

// 游戏开始前的准备
void GameStart(pSnake ps);

// 打印欢迎信息
void WelcomeToGame();

// 打印地图
void CreateMap();

// 初始化贪吃蛇
void InitSnake(pSnake ps);

// 创建食物
void CreateFood(pSnake ps);

// 游戏运行的整个逻辑
void GameRun(pSnake ps);

// 打印帮助信息
void PrintHelpInfo();

// 蛇身移动，每次走一步
void SnakeMove(pSnake ps);

// 判断蛇头下一步要走的位置处是否是食物
int NextIsFood(pSnake ps, pSnakeNode pNextNode);

// 下一步要走的位置处是食物，就吃掉
void EatFood(pSnake ps, pSnakeNode pNextNode);

// 下一步要走的位置处不是食物，就不吃
void NotEatFood(pSnake ps, pSnakeNode pNextNode);

// 检测撞墙
void KillByWall(pSnake ps);

// 检测撞到自己
void KillByMyself(pSnake ps);

// 游戏结束(善后工作)
void GameEnd(pSnake ps);

