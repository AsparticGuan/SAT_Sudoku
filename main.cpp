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
		cout << "    プログラミングコース設計へようこそ   " << endl;
		cout << "		  功能菜单                        " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1.读取cnf文件	        2.遍历输出每个子句" << endl;
		cout << "3.DPLL求解算例并保存	4.双数独游戏  　  " << endl;
		cout << "5.运行DPLL原始版本（极大可能超时）       " << endl;
		cout << "0.退出                                   " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "请选择你的操作[0~5]:                     " << endl;
		cin >> op;
		switch (op){
		case 1:
			printf("输入要读取的cnf文件:");
			scanf_s("%s", FileName, 1000);
			func_result = Read_file(cnf);
			if (!func_result) cout << "文件读入时发生错误" << endl;
			else cout << "文件读入成功" << endl;
			getchar(); getchar();
			break;
		case 2:
			func_result = Print_expression(cnf);
			if (!func_result) cout << "公式为空" << endl;
			else cout << endl << "公式读取成功" << endl;
			getchar(); getchar();
			break;
		case 3:
			start = clock();  //计时开始;
			try {
				func_result = DPLL_optimized(cnf);
			}
			catch (const std::exception&) {
				cout << "结果：-1，运算超时" << endl;
				Destroy_expression(cnf);
				getchar(); getchar();
				break;
			}
			finish = clock();    //结束
			if (func_result == -1) cout << "公式为空" << endl;
			else if (func_result == false) cout << "结果：0，公式不可满足" << endl;
			else {
				cout << "结果：1，公式满足" << endl << "求解结果：" << endl;
				for (int i = 1;i <= bool_amt;i++) {
					if (result[i] == 0) cout << i << " ";
					else cout << result[i] * i << " ";
				}
			}
			time1 = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
			cout << endl << "运行" << time1 * 1000 << "ms结束" << endl;//输出运行时间
			if (Write_file(func_result, time1)) cout << "写入.res文件成功" << endl;
			getchar(); getchar();
			break;
		case 5:
			printf("输入要读取的cnf文件:");
			scanf_s("%s", FileName, 1000);
			read_file();
			cout << "文件读入成功" << endl;
			print_expression();
			func_result = dpll(0,0);
			if (func_result == -1) cout << "公式为空" << endl;
			else if (func_result == false) cout << "结果：0，公式不可满足" << endl;
			else {
				cout << "结果：1，公式满足" << endl << "求解结果：" << endl;
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
				cout << "          数字は独身に限る!              " << endl;
				cout << "              功能菜单                   " << endl;
				cout << "-----------------------------------------" << endl;
				cout << "1.生成数独	        2.解决数独（玩家）    " << endl;
				cout << "3.保存成cnf文件	4.解决数独（电脑）　  " << endl;
				cout << "0.退出                                   " << endl;
				cout << "-----------------------------------------" << endl;
				cout << "请选择你的操作[0~4]:                     " << endl;
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
					cout << "数独已生成，请按enter后选择2开始游戏" << endl;
					getchar(); getchar();
					break;
				case 2:
					//形成交互界面
					while (true) {
						system("cls");
						Print_twodoku(sudoku1,sudoku2);
						cout << "请输入棋盘编号（左上角为1，右下角为2）、行号（1~9），列号（1~9）与输入的数字：" << endl;
						cout << "退出请输入0 0 0 0" << endl;
						cin >> area >> row >> col >> num;
						if (area == 0) break;
						if (area < 1 || area > 2 || row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
							cout << "请正确输入" << endl;
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
					cout << "保存成功" << endl;
					is_saved = true;
					getchar(); getchar();
					break;
				case 4:
					if (!is_saved) cout << "请先将数独保存为.cnf文件" << endl;
					strcpy(FileName, "D:\\总库\\学习\\作业\\程序设计综合课设\\官巴图_U202113897_程序设计综合课设\\twodoku.cnf");
					func_result = Read_file(cnf);
					if (!func_result) {
						cout << "文件读入时发生错误" << endl;
						break;
						getchar();getchar();
					}
					start = clock();  //计时开始;
					try {
						func_result = DPLL_optimized(cnf);
					}
					catch (const std::exception&) {
						cout << "结果：-1，运算超时" << endl;
						getchar(); getchar();
						break;
					}
					finish = clock();    //结束
					if (func_result == -1) cout << "公式为空" << endl;
					else if (func_result == false) cout << "结果：0，公式不可满足" << endl;
					else {
						cout << "结果：1，公式满足" << endl << "求解结果：" << endl;
						for (int i = 1;i <= bool_amt;i++) {
							if (result[i] == 0) cout << i << " ";
							else cout << result[i] * i << " ";
						}
					}
					time1 = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
					cout << endl << "运行" << time1 * 1000 << "ms结束" << endl;//输出运行时间
					if (Write_file(func_result, time1)) cout << "写入.res文件成功" << endl;
					cout << "最终结果：" << endl;
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