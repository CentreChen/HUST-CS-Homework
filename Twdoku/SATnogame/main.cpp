/*  to be solved
1. new 内存申请失败的异常机制检测

*/
#include "Global.h"
#include "Cnfparser.cpp"
#include "Solver.cpp"
#include "Sudoku.cpp"
#include "Display.cpp"
#include "Addition.h"

status flag;
CNF* cnf1 = nullptr;
CNF* cnf2 = nullptr;
clock_t StartTime,EndTime;
int sudoku1[ROW][COL], sudoku2[ROW][COL];
int answer1[ROW][COL], answer2[ROW][COL];

int main()
{
    int opt = 0;
    do{
        do{scanf("%d", &opt);} while(opt!=0 && opt!=1 && opt!=2 && opt!=3);
        if(opt == 1)
        {
            string fileName; cin >> fileName;
            flag = readCNF(fileName, &cnf1);    //read the file
            if(flag == ERROR) exit(-1);
            else printf("cnf文件中的变元数: %d     子句数: %d\n", cnf1->VarNum, cnf1->ClauseNum);

            int *result = (int*)malloc(sizeof(int)*(cnf1->VarNum+1));
            memset(result, 0, sizeof(int)*(cnf1->VarNum+1));
            StartTime = clock();
            flag = DPLL(cnf1, result);  //dpll
            EndTime = clock();
            Judge(flag);
            printf("%ld\tms\n", (EndTime-StartTime)*1000/CLOCKS_PER_SEC);
            SaveResult(fileName, flag, result, cnf1->VarNum, EndTime-StartTime);
            if(flag) Check(fileName, result);
            free(result);
            DestroyCNF(&cnf1);
        } 
        else if(opt == 2)
        {
            GenerateTwoSudoku(sudoku1, sudoku2);
            MakeSudokuCNF(sudoku1,sudoku2);

            string fileName = "sudoku.cnf"; 
            readCNF(fileName, &cnf2);
            int ans[1461] = {0};
            DPLL(cnf2, ans);
            SaveResult(fileName, 1, ans, 1460, 0);
            FillSudoku(answer1, answer2);
        }
        else if(opt == 3)
        {
            printTwoSudoku(answer1, answer2);
        }

    }while(opt);


    printf("thanks for using\n");
    // system("pause");
    return 0;
}
