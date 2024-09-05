#pragma once
#include"defin.h"

//函数名称：read_file
//函数功能：打开.cnf文件，并将数据存入链表中，成功返回true，失败返回false
void read_file() {
	FILE* fp;
	char ch;
	fopen_s(&fp, FileName, "r");
	while ((ch = getc(fp)) == 'c') {
		while ((ch = getc(fp)) != '\n') continue;
	}//舍弃开头注释行
	for (int i = 0;i < 4;i++) getc(fp);//跳出while循环时已经读到了字符'p'，在这里还要把' cnf'4个字符舍弃掉
	fscanf(fp, "%d", &bool_amt);//p开头行第一个数字为布尔变元数量
	fscanf(fp, "%d", &clause_amt);//p开头行第二个数字为子句数量
	//对result数组动态内存分配
	result = new int[bool_amt + 1];
	memset(result, 0, (bool_amt + 1) * sizeof(int));
	expr = (int**)malloc(sizeof(int*) * (clause_amt + 1));//分配指针数组，一共有clause_amt个子句，分配clause_amt+1个位置
	for (int i = 0;i <= clause_amt;i++) {
		//分配每个指针所指向的数组，每行的第0位用来指示当前子句里一共有多少个文字
		//如果是0代表为空子句，如果是-1代表已删除
		expr[i] = (int*)malloc(sizeof(int) * (bool_amt + 1));
		memset(expr[i], 0, (bool_amt + 1) * sizeof(int));
	}
	expr[0][0] = clause_amt;
	for (int i = 1;i <= clause_amt;i++) {
		int num = 0;
		while (true) {
			fscanf(fp, "%d", &num);
			if (num == 0) break;
			else expr[i][abs(num)] = abs(num)/num;
			expr[i][0]++;
			expr[0][abs(num)]++;
		}
	}
	fclose(fp);
}

//函数名称：print_expression
//函数功能：将公式打印出来
void print_expression() {
	for (int i = 1;i <= clause_amt;i++) {
		for (int j = 1;j <= bool_amt;j++) {
			if (expr[i][j] != 0) cout << expr[i][j] * j << " ";
		}
		cout << endl;
	}
}

void insert_clause(int num) {
	expr = (int**)realloc(expr, (expr[0][0] + 2) * sizeof(int*));
	expr[0][0]++;
	expr[expr[0][0]] = (int*)malloc(sizeof(int) * (bool_amt + 1));
	memset(expr[expr[0][0]], 0, sizeof(int) * (bool_amt + 1));
	expr[expr[0][0]][0] = 1;
	if (num > 0) expr[expr[0][0]][num] = 1;
	else if (num < 0) expr[expr[0][0]][-num] = -1;
}

//函数名称：unit_clause_rule
//函数功能：通过单子句规则化简公式
int unit_clause_rule() {
	while (true) {
		bool opt = false;
		for (int i = 1;i <= expr[0][0];i++) {
			if (expr[i][0] == 1) {
				opt = true;
				int del = 0;
				for (int j = 1;j <= bool_amt;j++) {
					if (expr[i][j] != 0) {
						del = j * expr[i][j];
						break;
					}
				}
				//cout << del << endl;
				if (del > 0) result[del] = 1;
				else result[-del] = -1;
				for (int j = 1;j <= expr[0][0];j++) {
					if (expr[j][abs(del)] * del > 0) {
						expr[j][0] = -1;//如果出现了一样的文字就删掉子句，因为该子句肯定为真了
						for (int k = 1;k <= bool_amt;k++) {
							if (expr[j][k] != 0) expr[0][k]--;
						}
					}
					else if (expr[j][abs(del)] * del < 0) {
						expr[j][abs(del)] = 0;
						expr[j][0]--;
						expr[0][abs(del)]--;
						if (expr[j][0] == 0) return false;
					}
				}
			}
		}
		if (!opt) break;
	}
	for (int i = 1;i <= expr[0][0];i++) {
		if (expr[i][0] != -1) return 2;
	}
	return true;
}

//函数名称：highest_frequency_literal
//函数功能：统计公式中出现次数最多的文字。如果公式中存在正文字就选取该正文字，如果全是负文字，就选取最多的那个负文字，返回值为该文字
int highest_frequency_literal() {
	int max = 0;
	int maxnum = 0;
	for (int i = 1;i <= bool_amt;i++) {
		if (expr[0][i] > max) {
			max = expr[0][i];
			maxnum = i;
		}
	}
	return maxnum;
}

//函数名称：dpll
//函数功能：执行优化过的DPLL算法
int dpll(int num,int mark) {//传进来的num用于指示应当插入的单子句
	if (num) {
		if (mark == 1) insert_clause(num);
		else if (mark == -1) insert_clause(-num);
	}
	int rst = unit_clause_rule();
	if (rst == true) return true;
	else if (rst == false) return false;
	int n = highest_frequency_literal();
	if (dpll(n, 1)) return true;
	return (dpll(n, -1));
}