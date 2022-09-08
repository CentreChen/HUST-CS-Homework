#ifndef SUDOKU_H
#define SUDOKU_H
#include <bits/stdc++.h>
#define ROW 9
#define COL 9
#define TRUE 1
#define FALSE 0
#define blockID(x, y) ((x) / 3 * 3 + (y) / 3)
#define VAR(id, x, y, val) ((id)*729 + (x)*81 + (y)*9 + (val)) //转换成十进制并且加一
using namespace std;
typedef int status;







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

    while (n )   //随机挖洞，挖洞前检查唯一性
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
    while (!LasVegas(11, f1));   //生成左上数独终盘

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

}


#endif // SUDOKU_H
