#pragma once
#include"defin.h"

//函数名称：Destroy_expression
//函数功能：销毁整个公式
bool Destroy_expression(SATList*& cnf) {
	if (!cnf) return false;
	SATList* list1, * list2;//一个负责删，一个负责指向下一个
	SATNode* node1, * node2;
	for (list1 = cnf; list1 != NULL; list1 = list2) {
		list2 = list1->next;
		for (node1 = list1->head; node1 != NULL; node1 = node2) {
			node2 = node1->next;
			delete node1;
		}
		delete list1;
	}
	cnf = NULL;
	return true;
}

//函数名称：Read_file
//函数功能：打开.cnf文件，并将数据存入链表中，成功返回true，失败返回false
bool Read_file(SATList*& cnf) {
	if (cnf) Destroy_expression(cnf);//操作的必须是空链表
	FILE* fp;
	char ch;
	if (fopen_s(&fp, FileName, "r")) return false;
	while ((ch = getc(fp)) == 'c') {
		while ((ch = getc(fp)) != '\n') continue;
	}//舍弃开头注释行
	for (int i = 0;i < 4;i++) getc(fp);//跳出while循环时已经读到了字符'p'，在这里还要把' cnf'4个字符舍弃掉
	fscanf(fp, "%d", &bool_amt);//p开头行第一个数字为布尔变元数量
	fscanf(fp, "%d", &clause_amt);//p开头行第二个数字为子句数量
	//对result数组动态内存分配
	cnf = new SATList;
	cnf->head = new SATNode;
	cnf->head->next = NULL;
	cnf->next = NULL;
	result = new int[bool_amt+1];
	memset(result, 0, (bool_amt + 1) * sizeof(int));
	//下面把每个子句的数据存入链表中
	SATList* p = cnf;//p指针指向子句结点，用于指示最后一个子句
	SATNode* q = NULL;//q指针指示子句中的最后一个文字
	int num = 0;//读取文字值
	for (int i = 0;i < clause_amt;i++) {
		SATList* r = new SATList;//新建一个子句结点
		r->head = new SATNode;
		r->head->next = NULL;
		r->next = NULL;
		p->next = r;
		p = r;
		q = r->head;
		while (true) {
			fscanf(fp, "%d", &num);
			if (num == 0) break;
			SATNode* s = new SATNode;//新建一个文字结点
			s->data = num;
			s->next = NULL;
			q->next = s;
			q = s;
		}
	}
	fclose(fp);
	return true;
}

//函数名称：Print_expression
//函数功能：将公式打印出来
bool Print_expression(SATList* cnf) {
	if (cnf == NULL) return false;
	SATList* p = cnf->next;
	while (p) {
		SATNode* q = p->head->next;
		if (q) cout << '(';
		while (q) {
			if (q->data > 0) cout << q->data;
			else cout << "-" << -q->data;
			if (q->next) cout << "∨";
			q = q->next;
		}
		cout << ')';
		if (p->next) cout << "∧";
		p = p->next;
	}
	return true;
}

//函数名称：Is_unit_clause
//函数功能：判断子句是否为单子句
bool Is_unit_clause(SATNode* L) {
	if (L == NULL) return false;
	if (L->next == NULL) return false;
	else if (L->next->next != NULL) return false;
	else return true;
}

//函数名称：Exist_literal
//函数功能：判断子句中是否存在某一文字
bool Exist_literal(SATNode* head, int lit) {
	if (head == NULL) return false;
	if (head->next == NULL) return false;
	SATNode* p = head->next;
	while (p != NULL && p->data != lit) p = p->next;
	if (!p) return false;
	return true;
}

//函数名称：Insert_clause
//函数功能：在公式中加入一个子句
bool Insert_clause(SATList*& cnf, SATList*& add) {
	if (cnf == NULL) return false;
	add->next = cnf->next;
	cnf->next = add;
	return true;
}

//函数名称：Exist_empty_clause
//函数功能：判断公式中是否存在空子句（公式为空时也判断为存在空子句）
bool Exist_empty_clause(SATList* cnf) {
	if (cnf == NULL) return true;
	SATList* p = cnf->next;
	while (p != NULL) {
		if (p->head->next == NULL) return true;
		p = p->next;
	}
	return false;	
}

//函数名称：Exist_unit_clause
//函数功能：判断公式中是否有单子句
bool Exist_unit_clause(SATList* cnf) {
	if (cnf == NULL) return false;
	SATList* p = cnf;
	while (p->next != NULL) {
		if (Is_unit_clause(p->next->head)) return true;
		p = p->next;
	}
	return false;
}

//函数名称：Unit_clause_rule
//函数功能：通过单子句规则化简公式
int Unit_clause_rule(SATList*& cnf) {
	if (cnf == NULL) return false;
	while (Exist_unit_clause(cnf)) {
		SATList* p = cnf;
		while (p->next != NULL) {
			if (Is_unit_clause(p->next->head)) break;
			p = p->next;
		}
		int del = p->next->head->next->data;
		//cout <<"该delete的："<< del << endl;
		//标记该文字应取的真值
		if (del > 0) result[del] = 1;
		else result[-del] = -1;
		//for (int i = 1;i <= bool_amt;i++) cout << result[i] << " ";
		//cout << endl;
		//下面根据单文字规则化简该式，即如果出现了一样的文字就删掉子句，因为该子句肯定为真了；
		//如果出现了恰好相反的文字就删掉该文字，因为该文字肯定为假，在子句中没用了
		p = cnf;
		while (p->next != NULL) {
			//出现相同文字的情况
			if (Exist_literal(p->next->head, del)) {
				SATList* q = p->next;
				p->next = p->next->next;
				delete q;
				if (!p) break;
			}
			//出现恰好相反文字的情况
			else if (Exist_literal(p->next->head, -del)) {
				SATNode* r = p->next->head;
				while (r->next->data != -del) r = r->next;
				SATNode* s = r->next;
				r->next = r->next->next;
				delete s;
				p = p->next;
			}
			else p = p->next;
		}
		//每处理完一次单子句后进行一次判断。如果处理完后公式为空，那么公式可满足，返回true；
		//而如果处理完后公式中出现了空子句，那么代表原始公式中该子句和其他单子句完全矛盾，故公式不可满足。
		//Print_expression(cnf);
		//cout << endl;
		if (cnf->next == NULL) return true;
		if (Exist_empty_clause(cnf)) return false;
	}
	return 2;
}

//函数名称：Highest_frequency_literal
//函数功能：统计公式中出现次数最多的文字。如果公式中存在正文字就选取该正文字，如果全是负文字，就选取最多的那个负文字，返回值为该文字
int Highest_frequency_literal(SATList* cnf) {
	if (cnf == NULL) return -1;
	int* cnt = new int[bool_amt * 2 + 1];//记录每个文字出现的次数，其中1~bool_amt为正文字记录区，bool_amt+1~2*bool_amt为负文字记录区
	memset(cnt, 0, (bool_amt * 2 + 1) * sizeof(int));
	SATList* p = cnf->next;
	while (p) {
		SATNode* q = p->head->next;
		while (q) {
			if (q->data > 0) cnt[q->data]++;
			else cnt[-q->data + bool_amt]++;
			q = q->next;
		}
		p = p->next;
	}
	//for (int i = 0;i <= bool_amt * 2 + 1;i++) cout << cnt[i] << " ";
	int max = 0;
	int maxnum = 0;
	for (int i = 1;i <= bool_amt;i++) {
		if (cnt[i] > max) {
			max = cnt[i];
			maxnum = i;
		}
	}
	if (max > 0) return maxnum;
	for (int i = bool_amt;i <= 2 * bool_amt;i++) {
		if (cnt[i] > max) {
			max = cnt[i];
			maxnum = i;
		}
	}
	return (bool_amt - maxnum);
}

//函数名称: Copy_clause
//函数功能: 将链表b的值复制到空链表a中
bool Copy_clause(SATList*& cpy, SATList* cnf){
	if (cnf == NULL) return true;
	cpy = new SATList;
	cpy->head = NULL;
	cpy->next = new SATList;
	SATList* p_cpy = cpy->next;
	SATList* p_cnf = cnf->next;
	while (p_cnf) {
		p_cpy->head = new SATNode;
		p_cpy->head->data = p_cnf->head->data;
		SATNode* q_cnf = p_cnf->head->next;
		SATNode* q_cpy = p_cpy->head;
		while (q_cnf) {
			q_cpy->next = new SATNode;
			q_cpy->next->data = q_cnf->data;
			q_cpy->next->next = NULL;
			q_cnf = q_cnf->next;
			q_cpy = q_cpy->next;
		}
		p_cnf = p_cnf->next;
		if (p_cnf) {
			p_cpy->next = new SATList;
			p_cpy = p_cpy->next;
			p_cpy->head = NULL;
			p_cpy->next = NULL;
		}
		else {
			p_cpy->next = NULL;
			return true;
		}
	}
}

//函数名称：DPLL_optimized
//函数功能：执行优化过的DPLL算法
int DPLL_optimized(SATList*& cnf) {
	if (cnf == NULL) return -1;
	int rst = Unit_clause_rule(cnf);
	if (rst == true) return true;
	else if (rst == false) return false;
	int num = Highest_frequency_literal(cnf);
	//cout << endl<<"出现频率最高的：" << num << endl;
	//将该文字及其相反的文字各打包成一个子句
	//打包该文字
	SATList* add1 = new SATList;
	SATNode* addnum1 = new SATNode;
	add1->head = new SATNode;
	add1->head->next = addnum1;
	add1->next = NULL;
	addnum1->data = num;
	addnum1->next = NULL;
	//打包相反文字
	SATList* add2 = new SATList;
	SATNode* addnum2 = new SATNode;
	add2->head = new SATNode;
	add2->head->next = addnum2;
	add2->next = NULL;
	addnum2->data = -num;
	addnum2->next = NULL;
	//将子句插入cnf中，原来的cnf需要复制一份
	SATList* cnf1 = NULL;
	SATList* cnf2 = NULL;
	Copy_clause(cnf1, cnf);
	Copy_clause(cnf2, cnf);
	Insert_clause(cnf1, add1);
	Insert_clause(cnf2, add2);
	if (DPLL_optimized(cnf1)) return true;
	return (DPLL_optimized(cnf2));
}

//函数名称: WriteFile
//函数功能: 将运行结果保存至同名文件，文件拓展名为.res
bool Write_file(int func_result, double time){
	FILE* fp;
	for (int i = 0; FileName[i] != '\0'; i++){
		//修改拓展名
		if (FileName[i] == '.' && FileName[i + 4] == '\0'){
			FileName[i + 1] = 'r';
			FileName[i + 2] = 'e';
			FileName[i + 3] = 's';
			break;
		}
	}
	if (fopen_s(&fp, FileName, "w")) {
		printf("文件打开失败!\n");
		return false;
	}
	fprintf(fp, "s %d\nv ", func_result);  //求解结果
	if (func_result == 1){
		//保存解值
		for (int i = 1; i <= bool_amt; i++){
			if (result[i] == 0) fprintf(fp, "%d ", i);
			else fprintf(fp, "%d ", result[i] * i);
		}
	}
	fprintf(fp, "\nt %lf", time * 1000);  //运行时间/毫秒
	fprintf(fp, "ms");
	fclose(fp);
	return true;
}

//函数名称：DPLL
//函数功能：执行DPLL算法
int DPLL(SATList*& cnf) {
	if (cnf == NULL) return -1;
	int rst = Unit_clause_rule(cnf);
	if (rst == true) return true;
	else if (rst == false) return false;
	int num = cnf->next->head->next->data;
	//cout << endl<<"出现频率最高的：" << num << endl;
	if (num >= bool_amt) return true;
	//将该文字及其相反的文字各打包成一个子句
	//打包该文字
	SATList* add1 = new SATList;
	SATNode* addnum1 = new SATNode;
	add1->head = new SATNode;
	add1->head->next = addnum1;
	add1->next = NULL;
	addnum1->data = num;
	addnum1->next = NULL;
	//打包相反文字
	SATList* add2 = new SATList;
	SATNode* addnum2 = new SATNode;
	add2->head = new SATNode;
	add2->head->next = addnum2;
	add2->next = NULL;
	addnum2->data = -num;
	addnum2->next = NULL;
	//将子句插入cnf中，原来的cnf需要复制一份
	SATList* cnf1 = NULL;
	SATList* cnf2 = NULL;
	Copy_clause(cnf1, cnf);
	Copy_clause(cnf2, cnf);
	Insert_clause(cnf1, add1);
	Insert_clause(cnf2, add2);
	if (DPLL(cnf1)) return true;
	return (DPLL(cnf2));
}
