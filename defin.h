#pragma once
#include<iostream>
#include<time.h>
using namespace std;

int bool_amt;  //������Ԫ����
int clause_amt;  //�Ӿ�����
char FileName[1000]; //�ļ���
//�洢���ֽ����resultҪ����Է���ؽ���������������ڴ�Ӧ���̶����ʿ��ǲ��ö�̬�����ڴ����飬
//�ڽ�������ʱͬʱ��result���ж�̬�ڴ���䡣
int* result=NULL;
int sudoku1[9][9] = { 0 };
int sudoku2[9][9] = { 0 };
int answer1[9][9] = { 0 };
int answer2[9][9] = { 0 };
int hole_amt = 0;//�����������������ص�������������
bool rows[9][10] = { 0 };
bool cols[9][10] = { 0 };
bool blocks[9][10] = { 0 };
int field[9][9] = { 0 };

typedef struct SATNode {
	int data;  //������
	SATNode* next;
}SATNode;//���ֽ��
typedef struct SATList {
	SATNode* head;  //����ͷ��head->data�����Ӿ��е�������
	SATList* next;
}SATList;//�Ӿ���

//���ԸĽ�һ��
int** expr = NULL;
