#include "Global.h"
#define blockID(x, y) ((x) / 3 * 3 + (y) / 3)
#define VAR(id, x, y, val) ((id)*729 + (x)*81 + (y)*9 + (val)) //转换成十进制并且加一

bool DFS(int f[][COL], bool r[][10], bool c[][10], bool b[][10])    
{
    for (int i = 0; i < 9; i++)     //枚举求解
        for (int j = 0; j < 9; j++)
            if (f[i][j] == 0)
            {
                int k = blockID(i, j);
                for (int n = 1; n <= 9; n++)
                { // try the 1~9
                    if (!r[i][n] && !c[j][n] && !b[k][n])
                    {
                        f[i][j] = n;
                        r[i][n] = c[j][n] = b[k][n] = 1;
                        if (DFS(f, r, c, b))
                            return true;
                        f[i][j] = 0; // backtrack
                        r[i][n] = c[j][n] = b[k][n] = 0;
                    }
                }
                return false;
            }
    return true;
}

bool LasVegas(int n, int field[][COL])
{ //拉斯维加斯算法
    srand((unsigned)time(nullptr));
    bool row[ROW][10], col[COL][10], block[9][10];
    for (int i = 0; i < 9; i++) // memset
        for (int j = 0; j < 9; j++)
        {
            field[i][j] = 0;
            row[i][j + 1] = col[i][j + 1] = block[i][j + 1] = 0;
        }

    while (n > 0)   //随机填入n个数字
    { 
        int i = rand() % 9, j = rand() % 9;
        if (field[i][j] == 0)
        {
            int k = blockID(i, j);
            int val = rand() % 9 + 1;
            if (!row[i][val] && !col[j][val] && !block[k][val])
            {
                field[i][j] = val;
                row[i][val] = col[j][val] = block[k][val] = 1;
                n--;
            }
        }
    }
    return DFS(field, row, col, block); //dfs求解
}

bool LasVegas2(int n, int field[][COL])
{ //拉斯维加斯算法
    srand((unsigned)time(nullptr));
    bool row[ROW][10], col[COL][10], block[9][10];
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(block, 0, sizeof(block));
    for (int i = 0; i < 3; i++) // memset， 标记已存在的数字
        for (int j = 0; j < 3; j++)
        {
            int t = field[i][j];
            int k = blockID(i, j);
            row[i][t] = col[j][t] = block[0][t] = 1;
        }
    n -= 9;
    while (n > 0)
    { // fill n digits randomly
        int i = rand() % 9, j = rand() % 9;
        if (field[i][j] == 0)
        {
            int k = blockID(i, j);
            int val = rand() % 9 + 1;
            if (!row[i][val] && !col[j][val] && !block[k][val])
            {
                field[i][j] = val;
                row[i][val] = col[j][val] = block[k][val] = 1;
                n--;
            }
        }
    }
    return DFS(field, row, col, block);
}

bool CheckUnique(int x, int y, int f0[][COL], bool r0[][10], bool c0[][10], bool b0[][10])
{
    // if(x==0 && y==0) return true;
    // printf("x = %d\ty = %d\n", x, y);
    if (f0[x][y] == 0)
        return false;
    int f[9][9];
    bool r[ROW][10], c[COL][10], b[9][10];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            f[i][j] = f0[i][j];
            r[i][j + 1] = r0[i][j + 1];
            c[i][j + 1] = c0[i][j + 1];
            b[i][j + 1] = b0[i][j + 1];
        }
    }
    int k = blockID(x, y);
    int target = f0[x][y]; // suppose to dig the target
    r[x][target] = c[y][target] = b[k][target] = 0;
    for (int n = 1; n <= 9; n++)    //假设挖去，遍历填入其他数字检查是否可解
    { // try the 1~9
        if (!r[x][n] && !c[y][n] && !b[k][n] && n != target)
        {
            f[x][y] = n;
            r[x][n] = c[y][n] = b[k][n] = 1;
            if (DFS(f, r, c, b))
                return false; // found another answer, so not unique
            f[x][y] = 0;      // backtrack
            r[x][n] = c[y][n] = b[k][n] = 0;
        }
    }
    return true;
}

void Dig(int n, int f1[][COL], int f2[][COL])
{
    bool r1[ROW][10], c1[COL][10], b1[9][10];
    bool r2[ROW][10], c2[COL][10], b2[9][10];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            r1[i][j + 1] = c1[i][j + 1] = b1[i][j + 1] = 1;
            r2[i][j + 1] = c2[i][j + 1] = b2[i][j + 1] = 1;
        }
    }

    srand((unsigned)time(nullptr));
    while (n)   //随机挖洞，挖洞前检查唯一性
    {
        int x = rand() % 9;
        int y = rand() % 9;
        int k = blockID(x, y);
        int id = rand() % 2 + 1;
        int flag = 1;
        if (id == 1)
        {
            if (k == 8)
                flag = CheckUnique(x, y, f1, r1, c1, b1) && CheckUnique(x - 6, y - 6, f2, r2, c2, b2);
            else
                flag = CheckUnique(x, y, f1, r1, c1, b1);
            if (flag)
            {
                int t = f1[x][y];
                f1[x][y] = 0;
                r1[x][t] = c1[x][t] = b1[x][t] = 0;
                n--;
                if (k == 8)
                {
                    int t = f2[x - 6][y - 6];
                    f2[x - 6][y - 6] = 0;
                    r2[x - 6][t] = c2[x - 6][t] = b2[x - 6][t] = 0;
                }
            }
        }
        else if (id == 2)
        {
            if (k == 0)
                flag = CheckUnique(x + 6, y + 6, f1, r1, c1, b1) && CheckUnique(x, y, f2, r2, c2, b2);
            else
                flag = CheckUnique(x, y, f2, r2, c2, b2);
            if (flag)
            {
                int t = f2[x][y];
                f2[x][y] = 0;
                r2[x][t] = c2[x][t] = b2[x][t] = 0;
                n--;
                if (k == 0)
                {
                    int t = f1[x + 6][y + 6];
                    f1[x + 6][y + 6] = 0;
                    r1[x + 6][t] = c1[x + 6][t] = b1[x + 6][t] = 0;
                }
            }
        }
    }
}

void GenerateTwoSudoku(int f1[][COL], int f2[][COL])
{
    while (!LasVegas(11, f1))   //生成左上数独终盘
        ;
    int fVice[9][9];
    memset(fVice, 0, sizeof(fVice));
    do
    {
        memset(fVice, 0, sizeof(fVice));
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                fVice[i][j] = f1[i + 6][j + 6];
    } while (!LasVegas2(11, fVice));    //生成右下数独终盘
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            f2[i][j] = fVice[i][j];

    // printTwoSudoku(f1, f2);
    printf("input the hole nums you want:\t");
    int holeNums;
    scanf("%d", &holeNums);
    Dig(holeNums, f1, f2);  //生成游戏格局

    printTwoSudoku(f1, f2); //打印游戏棋盘
}

// void GenerateOneSudoku(int f[][COL]){
//     while(!LasVegas(11, f));
//     printOneSudoku(f);
// }

void MakeSudokuCNF(int f1[][COL], int f2[][COL])
{
    string HeadPath = ".\\testData\\";
    string fileName = "sudoku.cnf";
    string path = HeadPath + fileName;
    FILE *fp = fopen(path.c_str(), "w");
    if (!fp)
    {
        printf("File open error!\n");
        exit(-1);
    }

    int singleClauseNums = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (f1[i][j])
                singleClauseNums++;
            if (f2[i][j])
                singleClauseNums++;
        }

    fprintf(fp, "%s", "p cnf ");
    fprintf(fp, "%d ", 1460);
    fprintf(fp, "%d\n", 24138 + singleClauseNums);

    for (int i = 0; i < 9; i++) // single clause  //九进制
        for (int j = 0; j < 9; j++)
        {
            if (f1[i][j])
            {
                int var = VAR(0, i, j, f1[i][j]);
                fprintf(fp, "%d  0\n", var);
            }
            if (f2[i][j])
            {
                int var = VAR(1, i, j, f2[i][j]);
                fprintf(fp, "%d  0\n", var);
            }
        }

    BasicClause(fp, 0);
    BasicClause(fp, 1);

    for (int i = 0; i < 3; i++)     //重叠部分限制
        for (int j = 0; j < 3; j++)
        {
            for (int n = 1; n <= 9; n++)
            {
                int var1 = VAR(0, i + 6, j + 6, n), var2 = VAR(1, i, j, n);
                fprintf(fp, "%d %d 0\n", -var1, var2);
                fprintf(fp, "%d %d 0\n", var1, -var2);
            }
        }
    fclose(fp);
    printf("Make CNF successfully!\n");
}

void BasicClause(FILE *fp, int id)
{

    for (int i = 0; i < 9; i++) //单元格
        for (int j = 0; j < 9; j++)
        {
            for (int n = 1; n <= 9; n++)
            { // f1[i][j] = n;
                int var = VAR(id, i, j, n);
                fprintf(fp, "%d  ", var);
            }
            fprintf(fp, "0\n");
            for (int n = 1; n < 9; n++)
            {
                for (int m = n + 1; m <= 9; m++)
                {
                    int var1 = VAR(id, i, j, n), var2 = VAR(id, i, j, m);
                    fprintf(fp, "%d %d 0\n", -var1, -var2);
                }
            }
        }

    for (int i = 0; i < 9; i++)
    { // row
        for (int n = 1; n <= 9; n++)
        {
            for (int j = 0; j < 9; j++)
            { 
                int var = VAR(id, i, j, n);
                fprintf(fp, "%d  ", var);
            }
            fprintf(fp, "0\n");
            for (int j1 = 0; j1 < 8; j1++)
            {
                for (int j2 = j1 + 1; j2 < 9; j2++)
                {
                    int var1 = VAR(id, i, j1, n), var2 = VAR(id, i, j2, n);
                    fprintf(fp, "%d %d 0\n", -var1, -var2);
                }
            }
        }
    }

    for (int j = 0; j < 9; j++)
    { // col
        for (int n = 1; n <= 9; n++)
        {
            for (int i = 0; i < 9; i++)
            { 
                int var = VAR(id, i, j, n);
                fprintf(fp, "%d  ", var);
            }
            fprintf(fp, "0\n");
            for (int i1 = 0; i1 < 8; i1++)
            {
                for (int i2 = i1 + 1; i2 < 9; i2++)
                {
                    int var1 = VAR(id, i1, j, n), var2 = VAR(id, i2, j, n);
                    fprintf(fp, "%d %d 0\n", -var1, -var2);
                }
            }
        }
    }

    for (int k = 0; k < 9; k++)
    { // block
        int i0 = k / 3 * 3, j0 = k % 3 * 3;
        for (int n = 1; n <= 9; n++)
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                    {
                        int var = VAR(id, i0 + i, j0 + j, n);
                        fprintf(fp, "%d ", var);
                    }
                }
            fprintf(fp, "0\n");
        }

        for (int n = 1; n <= 9; n++)
        {
            for (int ij1 = 0; ij1 < 8; ij1++)
            {
                for (int ij2 = ij1 + 1; ij2 < 9; ij2++)
                {
                    int i1 = ij1 / 3, j1 = ij1 % 3;
                    int i2 = ij2 / 3, j2 = ij2 % 3;
                    int var1 = VAR(id, i0 + i1, j0 + j1, n), var2 = VAR(id, i0 + i2, j0 + j2, n);
                    fprintf(fp, "%d %d 0\n", -var1, -var2);
                }
            }
        }
    }
}

void FillSudoku(int f1[][COL], int f2[][COL])
{
    string HeadPath = ".\\testData\\";
    string fileName = "sudoku.res";
    string path = HeadPath + fileName;
    FILE *fp = fopen(path.c_str(), "r");
    if (!fp)
    {
        printf("Can not find the sudoku CNF file!\n");
        exit(-1);
    }
    char ch, buff[10000];
    fread(&ch, sizeof(char), 1, fp);
    while (ch != 'v')
    {
        fgets(buff, 10000, fp); // useless data
        fread(&ch, sizeof(char), 1, fp);
    }
    int ans[1462] = {0}, cnt = 0;
    for (int i = 1; i <= 1460; i++)
    {
        int t = 0;
        fscanf(fp, "%d", &t);
        if (t > 0)
            ans[cnt++] = t;
    }
    fclose(fp);

    // printTwoSudoku(f1,f2);
    for (int i = 0; i < cnt; i++)   
    {
        int t = ans[i] - 1; //解码填充
        int id = t / 729;
        t %= 729;
        int x = t / 81;
        t %= 81;
        int y = t / 9;
        t %= 9;
        int n = t + 1;
        if (id == 0)
            f1[x][y] = n;
        else if (id == 1)
            f2[x][y] = n;
    }
    // printTwoSudoku(f1, f2);
}

status CheckSudoku(int f1[][COL], int f2[][COL], int ans1[][COL], int ans2[][COL]){
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++){
            if(f1[i][j] != ans1[i][j]) return FALSE;
            else if(blockID(i,j)>0 && f2[i][j] != ans2[i][j]) return FALSE;
        }
    return TRUE;
}