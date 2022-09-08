#ifndef _WORKSHOP_GLOBAL_H
#define _WORKSHOP_GLOBAL_H 1

#include <bits/stdc++.h>
// #include <iostream>
// #include <ctime>

#define TRUE 1
#define FALSE 0
#define OK 2
#define ERROR -1
#define ROW 9
#define COL 9
#define TIME_LIMIT 480000
#define sudokuVar 1460
using namespace std;
typedef int status;

typedef struct LinkNode
{
    struct LinkNode *next;
    int var;
} LinkNode;

typedef struct HeadNode
{
    struct HeadNode *next;
    LinkNode *head;
} HeadNode;

typedef struct CNF
{
    HeadNode *root;
    int VarNum = 0, ClauseNum = 0;
} CNF;

status readCNF(string, CNF **cnf);
status SaveCNF(string, CNF *);
void DestroyCNF(CNF **);
void TraverseCNF(CNF *);
void CopyCNF(CNF **dest, CNF *src);

status DPLL(CNF *, int *);
status FindEmptyClause(CNF *);
HeadNode *FindSingleClause_Pre(CNF *);
int StrategyMax2(CNF *);
int StrategyMax(CNF *);
int StrategyFirst(CNF *);
void Simplify(int target, CNF *cnf);
void RemoveClause_Suc(HeadNode *target, CNF *cnf);
void ReleaseLine(HeadNode *pHead);
void AddSingleClause(int, CNF *);

bool DFS(int f[][COL], bool r[][10], bool c[][10], bool b[][10]);
bool LasVegas(int n, int field[][COL]);
bool LasVegas2(int n, int field[][COL]);
bool CheckUnique(int x, int y, int f0[][COL], bool r0[][10], bool c0[][10], bool b0[][10]);
void GenerateTwoSudoku(int f1[][COL], int f2[][COL]);
void GenerateOneSudoku(int f1[][COL], int f2[][COL]);
void MakeSudokuCNF(int f1[][COL], int f2[][COL]);
void BasicClause(FILE *, int);
void FillSudoku(int f1[][COL], int f2[][COL]);
void Dig(int n, int f1[][COL], int f2[][COL]);

void menu(void);
void menu_SAT(void);
void Judge(status);
void printOneSudoku(int f[][COL]);
void printTwoSudoku(int f1[][COL], int f2[][COL]);

status SaveResult(string, int, int *, int, clock_t, clock_t);
int Check(string fileName, int *result);

int abs(int x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

#endif