#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 设置雷的个数，M 为雷的数量
#define M 10

#define ROW   9
#define COL   9
#define ROWS  ROW+2
#define COLS  COL+2

// 初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);

// 打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col);

// 布置雷
void SetMine(char board[ROWS][COLS], int row, int col);

// 排查雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);

// 统计输入坐标周围雷的个数
int GetMineCount(char mine[ROWS][COLS], int x, int y);
