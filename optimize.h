#pragma once
#include"defin.h"

//�������ƣ�read_file
//�������ܣ���.cnf�ļ����������ݴ��������У��ɹ�����true��ʧ�ܷ���false
void read_file() {
	FILE* fp;
	char ch;
	fopen_s(&fp, FileName, "r");
	while ((ch = getc(fp)) == 'c') {
		while ((ch = getc(fp)) != '\n') continue;
	}//������ͷע����
	for (int i = 0;i < 4;i++) getc(fp);//����whileѭ��ʱ�Ѿ��������ַ�'p'�������ﻹҪ��' cnf'4���ַ�������
	fscanf(fp, "%d", &bool_amt);//p��ͷ�е�һ������Ϊ������Ԫ����
	fscanf(fp, "%d", &clause_amt);//p��ͷ�еڶ�������Ϊ�Ӿ�����
	//��result���鶯̬�ڴ����
	result = new int[bool_amt + 1];
	memset(result, 0, (bool_amt + 1) * sizeof(int));
	expr = (int**)malloc(sizeof(int*) * (clause_amt + 1));//����ָ�����飬һ����clause_amt���Ӿ䣬����clause_amt+1��λ��
	for (int i = 0;i <= clause_amt;i++) {
		//����ÿ��ָ����ָ������飬ÿ�еĵ�0λ����ָʾ��ǰ�Ӿ���һ���ж��ٸ�����
		//�����0����Ϊ���Ӿ䣬�����-1������ɾ��
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

//�������ƣ�print_expression
//�������ܣ�����ʽ��ӡ����
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

//�������ƣ�unit_clause_rule
//�������ܣ�ͨ�����Ӿ���򻯼�ʽ
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
						expr[j][0] = -1;//���������һ�������־�ɾ���Ӿ䣬��Ϊ���Ӿ�϶�Ϊ����
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

//�������ƣ�highest_frequency_literal
//�������ܣ�ͳ�ƹ�ʽ�г��ִ����������֡������ʽ�д��������־�ѡȡ�������֣����ȫ�Ǹ����֣���ѡȡ�����Ǹ������֣�����ֵΪ������
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

//�������ƣ�dpll
//�������ܣ�ִ���Ż�����DPLL�㷨
int dpll(int num,int mark) {//��������num����ָʾӦ������ĵ��Ӿ�
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