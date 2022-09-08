#include "Global.h"



status SaveResult(string fileName, int flag, int* result, int VarNum, clock_t time){
    int p = strlen(fileName.c_str()) - 3;
    fileName[p++] = 'r'; fileName[p++] = 'e'; fileName[p++] = 's';
    string HeadPath = ".\\testData\\";
    string path = HeadPath + fileName;
    FILE* fp = fopen(path.c_str(), "w");
    if(!fp){
        printf("File open error!\n");
        return ERROR;
    }
    long t = (long)(t*1000/CLOCKS_PER_SEC);
    if(flag && time>TIME_LIMIT) flag = -1;

    fprintf(fp, "s %d\n", flag);
    if(flag){
        fprintf(fp, "v");
        for(int i=1; i<=VarNum; i++){
            if(result[i] == 1) fprintf(fp, " %d", i);
            else if(result[i]==0) fprintf(fp, " %d", -i);
            else {
                printf("result error!\n");
                exit(-1);
            }
        }fprintf(fp, "\n");
    }
    fprintf(fp, "t %ld", time);
    fclose(fp);
    return OK;
}


int Check(string fileName, int* result){
    int ret = 1;
    CNF* cnf = nullptr;
    readCNF(fileName, &cnf);
    HeadNode* pHead = cnf->root;
    int cntClause = 0;
    while(pHead->next){
        pHead = pHead->next;
        cntClause++;
        LinkNode* pLink = pHead->head;
        int flag = 0;
        while(!flag && pLink->next){
            pLink = pLink->next;
            int tmp = pLink->var;
            if((tmp>0 && result[tmp]==1) || (tmp<0 && result[-tmp]==0))
                flag = 1;
            
        }
        if(!flag){
            ret = 0;
            printf("wrong clause id : %d\n", cntClause);
        }
    }
    if(ret == 1){
        printf("Check yes!\n");
    }
    else printf("Check no!\n");
    return ret;
}