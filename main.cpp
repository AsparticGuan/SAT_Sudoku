#define _CRT_SECURE_NO_WARNINGS
#include"defin.h"
#include"dpll.h"
#include"sudoku.h"
#include"optimize.h"

int main() {
	SATList* cnf = NULL;
	double time1;
	double time2;
	int op = 1;
	int sdkop = 1;
	int func_result = 0;
	int area = 0;
	int row = 0;
	int col = 0;
	int num = 0;
	bool is_saved = false;
	clock_t start, finish;
	while (op){
		system("cls");
		cout << "    �ץ���ߥ󥰥��`���OӋ�ؤ褦����   " << endl;
		cout << "		  ���ܲ˵�                        " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1.��ȡcnf�ļ�	        2.�������ÿ���Ӿ�" << endl;
		cout << "3.DPLL�������������	4.˫������Ϸ  ��  " << endl;
		cout << "5.����DPLLԭʼ�汾��������ܳ�ʱ��       " << endl;
		cout << "0.�˳�                                   " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "��ѡ����Ĳ���[0~5]:                     " << endl;
		cin >> op;
		switch (op){
		case 1:
			printf("����Ҫ��ȡ��cnf�ļ�:");
			scanf_s("%s", FileName, 1000);
			func_result = Read_file(cnf);
			if (!func_result) cout << "�ļ�����ʱ��������" << endl;
			else cout << "�ļ�����ɹ�" << endl;
			getchar(); getchar();
			break;
		case 2:
			func_result = Print_expression(cnf);
			if (!func_result) cout << "��ʽΪ��" << endl;
			else cout << endl << "��ʽ��ȡ�ɹ�" << endl;
			getchar(); getchar();
			break;
		case 3:
			start = clock();  //��ʱ��ʼ;
			try {
				func_result = DPLL_optimized(cnf);
			}
			catch (const std::exception&) {
				cout << "�����-1�����㳬ʱ" << endl;
				Destroy_expression(cnf);
				getchar(); getchar();
				break;
			}
			finish = clock();    //����
			if (func_result == -1) cout << "��ʽΪ��" << endl;
			else if (func_result == false) cout << "�����0����ʽ��������" << endl;
			else {
				cout << "�����1����ʽ����" << endl << "�������" << endl;
				for (int i = 1;i <= bool_amt;i++) {
					if (result[i] == 0) cout << i << " ";
					else cout << result[i] * i << " ";
				}
			}
			time1 = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
			cout << endl << "����" << time1 * 1000 << "ms����" << endl;//�������ʱ��
			if (Write_file(func_result, time1)) cout << "д��.res�ļ��ɹ�" << endl;
			getchar(); getchar();
			break;
		case 5:
			printf("����Ҫ��ȡ��cnf�ļ�:");
			scanf_s("%s", FileName, 1000);
			read_file();
			cout << "�ļ�����ɹ�" << endl;
			print_expression();
			func_result = dpll(0,0);
			if (func_result == -1) cout << "��ʽΪ��" << endl;
			else if (func_result == false) cout << "�����0����ʽ��������" << endl;
			else {
				cout << "�����1����ʽ����" << endl << "�������" << endl;
				for (int i = 1;i <= bool_amt;i++) {
					if (result[i] == 0) cout << i << " ";
					else cout << result[i] * i << " ";
				}
			}
			getchar(); getchar();
			getchar(); getchar();
			break;
		case 4:
			sdkop = 1;
			while (sdkop) {
				system("cls");
				cout << "          ���֤϶�����ޤ�!              " << endl;
				cout << "              ���ܲ˵�                   " << endl;
				cout << "-----------------------------------------" << endl;
				cout << "1.��������	        2.�����������ң�    " << endl;
				cout << "3.�����cnf�ļ�	4.������������ԣ���  " << endl;
				cout << "0.�˳�                                   " << endl;
				cout << "-----------------------------------------" << endl;
				cout << "��ѡ����Ĳ���[0~4]:                     " << endl;
				cin >> sdkop;
				switch (sdkop){
				case 1:
					Create_sudoku();
					Create_twodoku();
					Create_holes_optimized(sudoku1);
					Create_holes_optimized(sudoku2);
					Check_create_holes_optimized();
					for (int i = 0;i < 9;i++) {
						for (int j = 0;j < 9;j++) {
							answer1[i][j] = sudoku1[i][j];
							answer2[i][j] = sudoku2[i][j];
						}
					}
					cout << "���������ɣ��밴enter��ѡ��2��ʼ��Ϸ" << endl;
					getchar(); getchar();
					break;
				case 2:
					//�γɽ�������
					while (true) {
						system("cls");
						Print_twodoku(sudoku1,sudoku2);
						cout << "���������̱�ţ����Ͻ�Ϊ1�����½�Ϊ2�����кţ�1~9�����кţ�1~9������������֣�" << endl;
						cout << "�˳�������0 0 0 0" << endl;
						cin >> area >> row >> col >> num;
						if (area == 0) break;
						if (area < 1 || area > 2 || row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
							cout << "����ȷ����" << endl;
							getchar();getchar();
							continue;
						}
						if (area == 1) sudoku1[row - 1][col - 1] = num;
						else if (area == 2) sudoku2[row - 1][col - 1] = num;
						if (area == 1 && 7 <= row && row <= 9 && 7 <= col && col <= 9) sudoku2[row - 7][col - 7] = num;
						if (area == 2 && 1 <= row && row <= 3 && 1 <= col && col <= 3) sudoku1[row + 5][col + 5] = num;
					}
					break;
				case 3:
					if (cnf != NULL) Destroy_expression(cnf);
					Twodoku_to_cnf();
					cout << "����ɹ�" << endl;
					is_saved = true;
					getchar(); getchar();
					break;
				case 4:
					if (!is_saved) cout << "���Ƚ���������Ϊ.cnf�ļ�" << endl;
					strcpy(FileName, "D:\\�ܿ�\\ѧϰ\\��ҵ\\��������ۺϿ���\\�ٰ�ͼ_U202113897_��������ۺϿ���\\twodoku.cnf");
					func_result = Read_file(cnf);
					if (!func_result) {
						cout << "�ļ�����ʱ��������" << endl;
						break;
						getchar();getchar();
					}
					start = clock();  //��ʱ��ʼ;
					try {
						func_result = DPLL_optimized(cnf);
					}
					catch (const std::exception&) {
						cout << "�����-1�����㳬ʱ" << endl;
						getchar(); getchar();
						break;
					}
					finish = clock();    //����
					if (func_result == -1) cout << "��ʽΪ��" << endl;
					else if (func_result == false) cout << "�����0����ʽ��������" << endl;
					else {
						cout << "�����1����ʽ����" << endl << "�������" << endl;
						for (int i = 1;i <= bool_amt;i++) {
							if (result[i] == 0) cout << i << " ";
							else cout << result[i] * i << " ";
						}
					}
					time1 = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
					cout << endl << "����" << time1 * 1000 << "ms����" << endl;//�������ʱ��
					if (Write_file(func_result, time1)) cout << "д��.res�ļ��ɹ�" << endl;
					cout << "���ս����" << endl;
					for (int i = 1;i <= 1458;i++) {
						if (result[i] >= 0 && i <= 729) {
							row = i / 81;
							col = (i - row * 81) / 9;
							num = i - row * 81 - col * 9;
							answer1[row][col] = num;
						}
						else if (result[i] >= 0 && i > 729) {
							row = (i - 729) / 81;
							col = (i - 729 - row * 81) / 9;
							num = i - 729 - row * 81 - col * 9;
							answer2[row][col] = num;
						}
					}
					for (int i = 0;i < 9;i++) {
						for (int j = 0;j < 9;j++) {
							if (answer1[i][j] == 0) answer1[i][j] = 9;
							if (answer2[i][j] == 0) answer2[i][j] = 9;
						}
					}
					Print_twodoku(answer1,answer2);
					getchar(); getchar();
					getchar(); getchar();
					break;
				case 0:
					break;
				}
			}
			break;
		case 0:
			break;
		}
	}
	return 0;
}