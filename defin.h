#pragma once
#include<iostream>
#include<time.h>
using namespace std;

int bool_amt;  //布尔变元数量
int clause_amt;  //子句数量
char FileName[1000]; //文件名
//存储文字结果的result要求可以方便地进行随机检索，且内存应不固定，故考虑采用动态分配内存数组，
//在建立链表时同时对result进行动态内存分配。
int* result=NULL;
int sudoku1[9][9] = { 0 };
int sudoku2[9][9] = { 0 };
int answer1[9][9] = { 0 };
int answer2[9][9] = { 0 };
int hole_amt = 0;//洞的数量，两数独重叠部分算两个洞
bool rows[9][10] = { 0 };
bool cols[9][10] = { 0 };
bool blocks[9][10] = { 0 };
int field[9][9] = { 0 };

typedef struct SATNode {
	int data;  //数据域
	SATNode* next;
}SATNode;//文字结点
typedef struct SATList {
	SATNode* head;  //文字头，head->data保存子句中的文字数
	SATList* next;
}SATList;//子句结点

//尝试改进一下
int** expr = NULL;
