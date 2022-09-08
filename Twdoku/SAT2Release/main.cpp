/*  to be solved
1. new 内存申请失败的异常机制检测

*/
#include "Global.h"
#include "Cnfparser.cpp"
#include "DPLLSolver.cpp"
#include "Sudoku.cpp"
#include "Display.cpp"
#include "Addition.h"

status flag;
CNF *cnf1 = nullptr;
CNF *cnf2 = nullptr;
clock_t StartTime, EndTime;
int sudoku1[ROW][COL], sudoku2[ROW][COL];
int answer1[ROW][COL], answer2[ROW][COL];

int main()
{
    int opt = 0;
    do{
        menu();
        do{scanf("%d", &opt);} while (opt != 0 && opt != 1 && opt != 2 && opt != 3);
        if (opt == 1)
        {
            menu_SAT();
            string fileName;
            int opt1; scanf("%d", &opt1);
            while(opt1){
                menu_SAT();
                switch (opt1)
                {
                case 1:{
                    printf("\nInput the fileName: ");
                    cin >> fileName;
                    flag = readCNF(fileName, &cnf1); // read the file
                    if (flag == ERROR)
                        exit(-1);
                    else
                        printf("cnf文件中的变元数: %d     子句数: %d\n", cnf1->VarNum, cnf1->ClauseNum);
                    system("pause");
                    break;
                }
                case 2:{
                    TraverseCNF(cnf1);
                    system("pause");
                    break;
                }
                case 3:{
                    printf("\nInput the fileName: ");
                    cin >> fileName;
                    flag = SaveCNF(fileName, cnf1); // read the file
                    Judge(flag);
                    system("pause");
                    break;
                }
                case 4:{
                    int *result = (int *)malloc(sizeof(int) * (cnf1->VarNum + 1));
                    memset(result, 0, sizeof(int) * (cnf1->VarNum + 1));
                    StartTime = clock();
                    flag = DPLL(cnf1, result); // dpll
                    EndTime = clock();
                    Judge(flag);
                    printf("------------%ld  ms\n", (EndTime - StartTime) * 1000 / CLOCKS_PER_SEC);
                    SaveResult(fileName, flag, result, cnf1->VarNum, EndTime - StartTime);
                    if (flag)
                        Check(fileName, result);
                    free(result);
                    system("pause");
                    break;
                }
                default:
                    break;
                }
                menu_SAT();
                scanf("%d", &opt1);
            }
            DestroyCNF(&cnf1);
        }
        else if (opt == 2)
        {
            GenerateTwoSudoku(sudoku1, sudoku2);    //生成数独
            MakeSudokuCNF(sudoku1, sudoku2);

            string fileName = "sudoku.cnf"; //后台生成答案
            readCNF(fileName, &cnf2);
            int ans[1461] = {0};
            DPLL(cnf2, ans);
            SaveResult(fileName, 1, ans, 1460, 0);
            FillSudoku(answer1, answer2);

            printf("Game begin!\n");    //游戏环节
            StartTime = clock();
            int id, x,y, n;
            printf("input example : id x y n\n");
            printf("Yours'  input : ");
            scanf("%d %d %d %d", &id, &x, &y, &n);
            while(n>=1 && n<=9){
                if(x>=0 && x<9 && y>=0 && y<9){
                    if(id==0){
                        if(answer1[x-1][y-1] == n){
                            printf("Good! you are right!\n");
                            sudoku1[x-1][y-1] = n;
                            printTwoSudoku(sudoku1,sudoku2);
                        }
                        else printf("Sorry, please try again.\n");
                    }
                    else if(id==1){
                        if(answer2[x-1][y-1] == n){
                            printf("Good! you are right!\n");
                            sudoku2[x-1][y-1] = n;
                            printTwoSudoku(sudoku1,sudoku2);
                        }
                        else printf("Sorry, please try again.\n");
                    }
                }
                else printf("Invalid input! Please try again.\n");
                scanf("%d %d %d %d", &id, &x, &y, &n);
            }
            EndTime = clock();
            printf("Game end!\nThe time used : %d s\n", (EndTime-StartTime)/1000);
            system("pause");
        }
        else if (opt == 3)
        {
            Judge(CheckSudoku(sudoku1,sudoku2,answer1,answer2));    //比对答案
            printf("The following is answer.\n");
            printTwoSudoku(answer1, answer2);
            system("pause");
        }

    } while (opt);

    printf("thanks for using\n");
    // system("pause");
    return 0;
}
