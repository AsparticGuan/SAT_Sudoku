#pragma once
#include"defin.h"
#include"dpll.h"

SATList* cnf1;
//函数名称：Print_twodoku
//函数功能：生成双数独棋盘
void Print_twodoku(int a[][9],int b[][9]) {
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) cout << "|";
            if (a[i][j] != 0) cout << " " << a[i][j] << " ";
            else cout << " _ ";
            if (j == 8) cout << "|" << endl;
        }
        if (i == 2) cout << "-------------------------------" << endl;
    }
    cout << "---------------------------------------------------" << endl;
    for (int i = 6;i < 9;i++) {
        for (int j = 0;j < 9;j++) {
            if (j % 3 == 0) cout << "|";
            if (a[i][j] != 0) cout << " " << a[i][j] << " ";
            else cout << " _ ";
        }
        for (int j = 3;j < 9;j++) {
            if (j % 3 == 0) cout << "|";
            if (b[i-6][j] != 0) cout << " " << b[i-6][j] << " ";
            else cout << " _ ";
            if (j == 8) cout << "|" << endl;
        }
    }
    cout << "---------------------------------------------------" << endl;
    for (int i = 3;i < 9;i++) {
        cout << "                    ";
        for (int j = 0;j < 9;j++) {
            if (j % 3 == 0) cout << "|";
            if (b[i][j] != 0) cout << " " << b[i][j] << " ";
            else cout << " _ ";
            if (j == 8) cout << "|" << endl;
        }
        if ((i + 1) % 3 == 0)cout << "                    -------------------------------" << endl;
    }
}

//函数名称：Create_sudoku
//函数功能：生成单数独的终盘
void Create_sudoku() {
    //生成一个1~9的随机序列
    bool is_selected[10] = { false };
    int select[9] = { 0 };
    int i = 0;
    srand(time(NULL));
    while (i < 9) {
        int num = rand() % 9 + 1;
        if (is_selected[num] == false) {
            is_selected[num] = true;
            select[i++] = num;
        }
    }
    //将这个数列按一定顺序打乱填入数独中
    for (int i = 0;i < 9;i++) sudoku1[0][i] = sudoku2[0][i] = select[i];
    for (int i = 1;i < 9;i++) {
        for (int j = 0;j < 9;j++) {
            if (i % 3) sudoku1[i][j] = sudoku2[i][j] = sudoku1[i - 1][(j + 6) % 9];
            else sudoku1[i][j] = sudoku2[i][j] = sudoku1[i - 1][(j + 5) % 9];
        }
    }
}

//函数名称：Create_twodoku
//函数功能：生成双数独终盘。生成方法为：在单数独对其第1~3行和1~3列进行同样的交换操作，对4~6行，7~9行与4~6列，7~9列进行不同的交换操作，
//然后把第一个单数独翻转180度即可
void Create_twodoku() {
    srand(time(NULL));
    //首先对第1~3行和1~3列进行同样的交换操作，具体如何交换由随机数决定
    int change[3][2] = { {0,1},{1,2},{0,2} };
    //交换行
    for (int i = 0;i < 3;i++) {
        int num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) {
                swap(sudoku1[change[i][0]][j], sudoku1[change[i][1]][j]);
                swap(sudoku2[change[i][0]][j], sudoku2[change[i][1]][j]);
            }
        }
    }
    //交换列
    for (int i = 0;i < 3;i++) {
        int num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) {
                swap(sudoku1[j][change[i][0]], sudoku1[j][change[i][1]]);
                swap(sudoku2[j][change[i][0]], sudoku2[j][change[i][1]]);
            }
        }
    }
    //然后是对4~6行，7~9行与4~6列，7~9列进行不同的交换操作
    //4~6行交换行
    for (int i = 0;i < 3;i++) {
        int num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku1[change[i][0] + 3][j], sudoku1[change[i][1] + 3][j]);
        }
        num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku2[change[i][0] + 3][j], sudoku2[change[i][1] + 3][j]);
        }
    }
    //4~6列交换列
    for (int i = 0;i < 3;i++) {
        int num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku1[j][change[i][0] + 3], sudoku1[j][change[i][1] + 3]);
        }
        num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku2[j][change[i][0] + 3], sudoku2[j][change[i][1] + 3]);
        }
    }
    //7~9行交换行
    for (int i = 0;i < 3;i++) {
        int num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku1[change[i][0] + 3][j], sudoku1[change[i][1] + 3][j]);
        }
        num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku2[change[i][0] + 3][j], sudoku2[change[i][1] + 3][j]);
        }
    }
    //7~9列交换列
    for (int i = 0;i < 3;i++) {
        int num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku1[j][change[i][0] + 6], sudoku1[j][change[i][1] + 6]);
        }
        num = rand();
        if (num % 2) {
            for (int j = 0;j < 9;j++) swap(sudoku2[j][change[i][0] + 6], sudoku2[j][change[i][1] + 6]);
        }
    }
    //翻转第一个单数独（用电话上数字顺序对九宫格编号，即147先与369换位置，然后321与987换位置
    //147与369换位置
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 9;j++) swap(sudoku1[j][i], sudoku1[j][i + 6]);
    }
    //321和987换位置
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 9;j++) swap(sudoku1[i][j], sudoku1[i + 6][j]);
    }
}

//函数名称：Create_holes
//函数功能：随机在双数独上挖洞,据不完全统计，要挖出110~120个洞
void Create_holes() {
    srand(time(NULL));
    int i = 0;
    int round = rand() % 11 + 110;
    while (i < round) {
        int area = rand() % 2;
        int row = rand() % 9;
        int col = rand() % 9;
        if (area == 0 && sudoku1[row][col] != 0) {
            sudoku1[row][col] = 0;
            hole_amt++;
            if (6 <= row && row <= 8 && 6 <= col && col <= 8) {
                sudoku2[row - 6][col - 6] = 0;
                hole_amt++;
            }
            i++;
        }
        else if (area == 1 && sudoku2[row][col] != 0) {
            sudoku2[row][col] = 0;
            hole_amt++;
            if (0 <= row && row <= 2 && 0 <= col && col <= 2) {
                sudoku1[row + 6][col + 6] = 0;
                hole_amt++;
            }
            i++;
        }
    }
}

//函数名称：Twodoku_to_cnf
//函数功能：将数独信息写入.cnf文件中
void Twodoku_to_cnf() {
    FILE* fp;
    fp = fopen("twodoku.cnf", "w+");
    fprintf(fp, "p cnf %d %d\n", 729 * 2, 37 * 81 * 2 + 37 * 9 * 18 * 2 + 37 * 9 * 9 * 2 + 162 + 81 * 2 - hole_amt);
    //变元与棋盘对应规则：左上角盘的第i行第j列的数字n转化为i*81+j*9+n，右下角盘的第i行第j列的数字n转化为i*81+j*9+n+729
    //单元格约束
    for (int a = 0;a < 9;a++) {
        for (int b = 0;b < 9;b++) {
            for (int c = 1;c < 10;c++) fprintf(fp, "%d ", 81 * a + 9 * b + c);
            fprintf(fp, "0\n");
            for (int c = 1;c < 9;c++) {
                for (int d = c + 1;d <= 9;d++) {
                    fprintf(fp, "%d %d 0\n", -(81 * a + 9 * b + c), -(81 * a + 9 * b + d));
                }
            }
        }
    }
    for (int a = 0;a < 9;a++) {
        for (int b = 0;b < 9;b++) {
            for (int c = 1;c < 10;c++) fprintf(fp, "%d ", 729 + 81 * a + 9 * b + c);
            fprintf(fp, "0\n");
            for (int c = 1;c < 9;c++) {
                for (int d = c + 1;d <= 9;d++) {
                    fprintf(fp, "%d %d 0\n", -(729 + 81 * a + 9 * b + c), -(729 + 81 * a + 9 * b + d));
                }
            }
        }
    }
    //行约束
    for (int a = 0;a < 9;a++) {
        for (int b = 1;b < 10;b++) {
            for (int c = 0;c < 9;c++) fprintf(fp, "%d ", 81 * a + b + 9 * c);
            fprintf(fp, "0\n");
            for (int c = 0;c < 8;c++) {
                for (int d = c + 1;d <= 8;d++) {
                    fprintf(fp, "%d %d 0\n", -(81 * a + b + 9 * c), -(81 * a + b + 9 * d));
                }
            }
        }
    }
    for (int a = 0;a < 9;a++) {
        for (int b = 1;b < 10;b++) {
            for (int c = 0;c < 9;c++) fprintf(fp, "%d ", 729 + 81 * a + b + 9 * c);
            fprintf(fp, "0\n");
            for (int c = 0;c < 8;c++) {
                for (int d = c + 1;d <= 8;d++) {
                    fprintf(fp, "%d %d 0\n", -(729 + 81 * a + b + 9 * c), -(729 + 81 * a + b + 9 * d));
                }
            }
        }
    }
    //列约束
    for (int a = 0;a < 9;a++) {
        for (int b = 1;b < 10;b++) {
            for (int c = 0;c < 9;c++) fprintf(fp, "%d ", 81 * c + b + 9 * a);
            fprintf(fp, "0\n");
            for (int c = 0;c < 8;c++) {
                for (int d = c + 1;d <= 8;d++) {
                    fprintf(fp, "%d %d 0\n", -(81 * c + b + 9 * a), -(81 * d + b + 9 * a));
                }
            }
        }
    }
    for (int a = 0;a < 9;a++) {
        for (int b = 1;b < 10;b++) {
            for (int c = 0;c < 9;c++) fprintf(fp, "%d ", 729 + 81 * c + b + 9 * a);
            fprintf(fp, "0\n");
            for (int c = 0;c < 8;c++) {
                for (int d = c + 1;d <= 8;d++) {
                    fprintf(fp, "%d %d 0\n", -(729 + 81 * c + b + 9 * a), -(729 + 81 * d + b + 9 * a));
                }
            }
        }
    }
    //3×3盒子约束
    for (int u = 0;u <= 6;u += 3) {
        for (int v = 0;v <= 6;v += 3) {
            for (int n = 1;n <= 9;n++) {
                for (int i = u;i < u + 3;i++) {
                    for (int j = v;j < v + 3;j++) fprintf(fp, "%d ", 81 * i + 9 * j + n);
                }
                fprintf(fp, "0\n");
                for (int i = u;i < u + 3;i++) {
                    for (int j = v;j < v + 3;j++) {
                        for (int r = u;r < u + 3;r++) {
                            for (int s = v;s < v + 3;s++) {
                                if ((r == i && s > j) || (r > i)) fprintf(fp, "%d %d 0\n", -(81 * i + 9 * j + n), -(81 * r + 9 * s + n));
                            }
                        }
                    }
                }
            }
        }
    }
    for (int u = 0;u <= 6;u += 3) {
        for (int v = 0;v <= 6;v += 3) {
            for (int n = 1;n <= 9;n++) {
                for (int i = u;i < u + 3;i++) {
                    for (int j = v;j < v + 3;j++) fprintf(fp, "%d ", 729 + 81 * i + 9 * j + n);
                }
                fprintf(fp, "0\n");
                for (int i = u;i < u + 3;i++) {
                    for (int j = v;j < v + 3;j++) {
                        for (int r = u;r < u + 3;r++) {
                            for (int s = v;s < v + 3;s++) {
                                if ((r == i && s > j) || (r > i)) fprintf(fp, "%d %d 0\n", -(729 + 81 * i + 9 * j + n), -(729 + 81 * r + 9 * s + n));
                            }
                        }
                    }
                }
            }
        }
    }
    //双数独共享盒子约束
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            for (int n = 1;n <= 9;n++) {
                fprintf(fp, "%d %d 0\n%d %d 0\n", -(81 * (i + 6) + 9 * (j + 6) + n), (729 + 81 * i + 9 * j + n), (81 * (i + 6) + 9 * (j + 6) + n), -(729 + 81 * i + 9 * j + n));
            }
        }
    }
    //已填入的数字约束
    for (int i = 0;i < 9;i++) {
        for (int j = 0;j < 9;j++) {
            if (sudoku1[i][j] != 0) fprintf(fp, "%d 0\n", 81 * i + 9 * j + sudoku1[i][j]);
        }
    }
    for (int i = 0;i < 9;i++) {
        for (int j = 0;j < 9;j++) {
            if (sudoku2[i][j] != 0) fprintf(fp, "%d 0\n", 729 + 81 * i + 9 * j + sudoku2[i][j]);
        }
    }
    fclose(fp);
}

//函数名称：Prep_for_dfs
//函数功能：将数独上的内容补充到dfs所需的数组里面
void Prep_for_dfs(int sudoku[9][9]) {
    for (int i = 0;i < 9;i++) {
        for (int j = 0;j < 9;j++) {
            int k = i / 3 * 3 + j / 3;
            field[i][j] = sudoku[i][j];
            rows[i][field[i][j]] = true;
            cols[j][field[i][j]] = true;
            blocks[k][field[i][j]] = true;
        }
    }
}

//函数名称：Solve_by_dfs
//函数功能：用DFS来解数独
bool Solve_by_dfs(int f[9][9], bool ro[9][10], bool co[9][10], bool bl[9][10]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (f[i][j] == 0) {
                int k = i / 3 * 3 + j / 3;
                // 尝试填入1~9
                for (int n = 1; n < 10; n++) {
                    if (!ro[i][n] && !co[j][n] && !bl[k][n]) {
                        // 尝试填入一个数
                        ro[i][n] = true;
                        co[j][n] = true;
                        bl[k][n] = true;
                        f[i][j] = n;
                        // 检查是否满足数独正解
                        if (Solve_by_dfs(f, ro, co, bl)) return true;
                        // 不满足则回溯
                        ro[i][n] = false;
                        co[j][n] = false;
                        bl[k][n] = false;
                        f[i][j] = 0;
                    }
                }
                // 尝试所有数字都不满足则回溯
                return false;
            }
        }
    }
    return true;
}

//函数名称：Check_unique
//函数功能：确保唯一解
bool Check_unique(int r, int c) {
    // 挖掉第一个位置一定有唯一解
    if (r == 0 && c == 0) return true;
    int k = r / 3 * 3 + c / 3;
    bool trows[9][10] = { 0 };
    bool tcols[9][10] = { 0 };
    bool tblocks[9][10] = { 0 };
    int tfield[9][9] = { 0 };
    // 临时数组
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            trows[i][j + 1] = rows[i][j + 1];
            tcols[i][j + 1] = cols[i][j + 1];
            tblocks[i][j + 1] = blocks[i][j + 1];
            tfield[i][j] = field[i][j];
        }
    }
    // 假设挖掉这个数字
    trows[r][field[r][c]] = false;
    tcols[c][field[r][c]] = false;
    tblocks[k][field[r][c]] = false;
    for (int i = 1; i < 10; i++) {
        if (i != field[r][c]) {
            tfield[r][c] = i;
            if (!trows[r][i] && !tcols[c][i] && !tblocks[k][i]) {
                trows[r][i] = true;
                tcols[c][i] = true;
                tblocks[k][i] = true;
                // 更换一个数字之后检查是否还有另一解
                if (Solve_by_dfs(tfield, trows, tcols, tblocks)) return false;
                trows[r][i] = false;
                tcols[c][i] = false;
                tblocks[k][i] = false;
            }
        }
        // 已尝试所有其他数字发现无解即只有唯一解
    }
    return true;
}

//函数名称：Create_holes_optimized
//函数功能：在双数独上挖洞，同时确保有且仅有唯一解。
void Create_holes_optimized(int sudoku[9][9]) {
    srand(time(NULL));
    Prep_for_dfs(sudoku);
    int level = rand() % 9 + 22;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (Check_unique(i, j)) {
                int k = i / 3 * 3 + j / 3;
                rows[i][field[i][j]] = false;
                cols[j][field[i][j]] = false;
                blocks[k][field[i][j]] = false;
                field[i][j] = 0;
                level++;
                hole_amt++;
                if (level == 81) break;
            }
        }
    }
    for (int i = 0;i < 9;i++) {
        for (int j = 0;j < 9;j++) sudoku[i][j] = field[i][j];
    }
}

//函数名称：Check_create_holes_optimized
//函数功能：把两个数独重叠的那一部分信息更新好
void Check_create_holes_optimized() {
    int temp[3][3] = { 0 };
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            if (sudoku1[i + 6][j + 6] && sudoku2[i][j]) temp[i][j] = sudoku2[i][j];
            else if ((sudoku1[i + 6][j + 6] == 0 && sudoku2[i][j] != 0) || (sudoku1[i + 6][j + 6] != 0 && sudoku2[i][j] == 0)) {
                temp[i][j] = 0;
                hole_amt++;
            }
            else temp[i][j] = 0;
        }
    }
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            sudoku1[i + 6][j + 6] = temp[i][j];
            sudoku2[i][j] = temp[i][j];
        }
    }
}