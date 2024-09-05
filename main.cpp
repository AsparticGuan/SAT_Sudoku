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
		cout << "    プログラミングコ�`ス�O��へようこそ   " << endl;
		cout << "		  孔嬬暇汽                        " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1.響函cnf猟周	        2.演煽補竃耽倖徨鞘" << endl;
		cout << "3.DPLL箔盾麻箭旺隠贋	4.褒方鏡嗄老  　  " << endl;
		cout << "5.塰佩DPLL圻兵井云�┝�寄辛嬬階扮��       " << endl;
		cout << "0.曜竃                                   " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "萩僉夲低議荷恬[0~5]:                     " << endl;
		cin >> op;
		switch (op){
		case 1:
			printf("補秘勣響函議cnf猟周:");
			scanf_s("%s", FileName, 1000);
			func_result = Read_file(cnf);
			if (!func_result) cout << "猟周響秘扮窟伏危列" << endl;
			else cout << "猟周響秘撹孔" << endl;
			getchar(); getchar();
			break;
		case 2:
			func_result = Print_expression(cnf);
			if (!func_result) cout << "巷塀葎腎" << endl;
			else cout << endl << "巷塀響函撹孔" << endl;
			getchar(); getchar();
			break;
		case 3:
			start = clock();  //柴扮蝕兵;
			try {
				func_result = DPLL_optimized(cnf);
			}
			catch (const std::exception&) {
				cout << "潤惚��-1��塰麻階扮" << endl;
				Destroy_expression(cnf);
				getchar(); getchar();
				break;
			}
			finish = clock();    //潤崩
			if (func_result == -1) cout << "巷塀葎腎" << endl;
			else if (func_result == false) cout << "潤惚��0��巷塀音辛諾怎" << endl;
			else {
				cout << "潤惚��1��巷塀諾怎" << endl << "箔盾潤惚��" << endl;
				for (int i = 1;i <= bool_amt;i++) {
					if (result[i] == 0) cout << i << " ";
					else cout << result[i] * i << " ";
				}
			}
			time1 = (double)(finish - start) / CLOCKS_PER_SEC;//柴麻塰佩扮寂
			cout << endl << "塰佩" << time1 * 1000 << "ms潤崩" << endl;//補竃塰佩扮寂
			if (Write_file(func_result, time1)) cout << "亟秘.res猟周撹孔" << endl;
			getchar(); getchar();
			break;
		case 5:
			printf("補秘勣響函議cnf猟周:");
			scanf_s("%s", FileName, 1000);
			read_file();
			cout << "猟周響秘撹孔" << endl;
			print_expression();
			func_result = dpll(0,0);
			if (func_result == -1) cout << "巷塀葎腎" << endl;
			else if (func_result == false) cout << "潤惚��0��巷塀音辛諾怎" << endl;
			else {
				cout << "潤惚��1��巷塀諾怎" << endl << "箔盾潤惚��" << endl;
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
				cout << "          方忖は鏡附に�泙�!              " << endl;
				cout << "              孔嬬暇汽                   " << endl;
				cout << "-----------------------------------------" << endl;
				cout << "1.伏撹方鏡	        2.盾畳方鏡��螺社��    " << endl;
				cout << "3.隠贋撹cnf猟周	4.盾畳方鏡�┻臘圍�　  " << endl;
				cout << "0.曜竃                                   " << endl;
				cout << "-----------------------------------------" << endl;
				cout << "萩僉夲低議荷恬[0~4]:                     " << endl;
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
					cout << "方鏡厮伏撹��萩梓enter朔僉夲2蝕兵嗄老" << endl;
					getchar(); getchar();
					break;
				case 2:
					//侘撹住札順中
					while (true) {
						system("cls");
						Print_twodoku(sudoku1,sudoku2);
						cout << "萩補秘薙徒園催��恣貧叔葎1��嘔和叔葎2��、佩催��1~9����双催��1~9��嚥補秘議方忖��" << endl;
						cout << "曜竃萩補秘0 0 0 0" << endl;
						cin >> area >> row >> col >> num;
						if (area == 0) break;
						if (area < 1 || area > 2 || row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
							cout << "萩屎鳩補秘" << endl;
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
					cout << "隠贋撹孔" << endl;
					is_saved = true;
					getchar(); getchar();
					break;
				case 4:
					if (!is_saved) cout << "萩枠繍方鏡隠贋葎.cnf猟周" << endl;
					strcpy(FileName, "D:\\悳垂\\僥楼\\恬匍\\殻會譜柴忝栽仁譜\\郊依夕_U202113897_殻會譜柴忝栽仁譜\\twodoku.cnf");
					func_result = Read_file(cnf);
					if (!func_result) {
						cout << "猟周響秘扮窟伏危列" << endl;
						break;
						getchar();getchar();
					}
					start = clock();  //柴扮蝕兵;
					try {
						func_result = DPLL_optimized(cnf);
					}
					catch (const std::exception&) {
						cout << "潤惚��-1��塰麻階扮" << endl;
						getchar(); getchar();
						break;
					}
					finish = clock();    //潤崩
					if (func_result == -1) cout << "巷塀葎腎" << endl;
					else if (func_result == false) cout << "潤惚��0��巷塀音辛諾怎" << endl;
					else {
						cout << "潤惚��1��巷塀諾怎" << endl << "箔盾潤惚��" << endl;
						for (int i = 1;i <= bool_amt;i++) {
							if (result[i] == 0) cout << i << " ";
							else cout << result[i] * i << " ";
						}
					}
					time1 = (double)(finish - start) / CLOCKS_PER_SEC;//柴麻塰佩扮寂
					cout << endl << "塰佩" << time1 * 1000 << "ms潤崩" << endl;//補竃塰佩扮寂
					if (Write_file(func_result, time1)) cout << "亟秘.res猟周撹孔" << endl;
					cout << "恷嶮潤惚��" << endl;
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