#include "Global.h"

status DPLL(CNF *cnf, int *result)
{
    if (cnf == NULL)
    {
        printf("CNF not found!\n");
        return ERROR;
    }
    if (cnf->ClauseNum == 0)
        return TRUE;

    HeadNode *singleClause_Pre = FindSingleClause_Pre(cnf);
    while (singleClause_Pre != nullptr)     //单规则传递
    { 
        int single = singleClause_Pre->next->head->next->var;
        if (single > 0)
            result[single] = 1;
        else if (single < 0)
            result[-single] = 0;
        RemoveClause_Suc(singleClause_Pre, cnf);
        Simplify(single, cnf);
        if (cnf->root->next == nullptr)
            return TRUE; // no Clause
        else if (FindEmptyClause(cnf))
            return FALSE; // Empty Clause can not be satisfied
        singleClause_Pre = FindSingleClause_Pre(cnf);
    }

    int target = StrategyMax2(cnf);     //变元策略
    // int target = StrategyMax(cnf);
    // int target = StrategyFirst(cnf);
    if (target == 0)
    {
        printf("target == 0\n");
        exit(-1);
    }
    CNF *cnfVice = nullptr;
    CopyCNF(&cnfVice, cnf);     //存档
    AddSingleClause(target, cnfVice);
    int flag = DPLL(cnfVice, result);
    DestroyCNF(&cnfVice);
    if (flag == TRUE)
        return TRUE;
    else      //策略失败，读档再来
    {
        AddSingleClause(-target, cnf);
        return DPLL(cnf, result);
    }
    // printf("你来了不该来的地方\n");
    return FALSE;
}

int StrategyMax(CNF *cnf)   //找频度最高的
{
    int maxNum = 0, pMaxNum;
    int *Num = (int *)malloc(sizeof(int) * (cnf->VarNum + 1));
    memset(Num, 0, sizeof(int) * (cnf->VarNum + 1));
    HeadNode *pHead = cnf->root;
    while (pHead->next)
    {
        pHead = pHead->next;
        LinkNode *pLink = pHead->head;
        while (pLink->next)
        {
            pLink = pLink->next;
            int t = abs(pLink->var);
            if (++Num[t] > maxNum)
            {
                maxNum = Num[t];
                pMaxNum = t;
            }
        }
    }
    free(Num);
    return pMaxNum;
}

int StrategyMax2(CNF *cnf)  //综合
{
    int maxNum = 0, pMaxNum = -1, VarNum = cnf->VarNum;
    int *Num = (int *)malloc(sizeof(int) * (2 * VarNum + 5));
    memset(Num, 0, sizeof(int) * (2 * VarNum + 5));
    HeadNode *pHead = cnf->root;
    while (pHead->next) //统计短子句文字频度
    {
        pHead = pHead->next;
        LinkNode *pLink = pHead->head;
        if (pLink->var == 2)
        {
            while (pLink->next)
            {
                pLink = pLink->next;
                int t = pLink->var;
                if (t < 0)
                    t = abs(t) + VarNum;
                if (++Num[t] > maxNum)
                {
                    maxNum = Num[t];
                    pMaxNum = t;
                }
            }
        }
    }
    free(Num);
    if (pMaxNum == -1 || pMaxNum == 0)  //无优解，开始暴力
        pMaxNum = StrategyFirst(cnf);   
    else if (pMaxNum > VarNum)
        pMaxNum = -(pMaxNum - VarNum);
    return pMaxNum;
}

int StrategyFirst(CNF *cnf) //暴力，找第一个子句的第一个文字
{
    HeadNode *pHead = cnf->root->next;
    if (pHead)
    {
        LinkNode *pLink = pHead->head;
        return pLink->next->var;
    }
    else
        return 0;
}

void Simplify(int target, CNF *cnf)
{ // simplify cnf with single Clause rule
    HeadNode *pHead = cnf->root;
    HeadNode *pHead_pre = pHead;
    while (pHead->next)
    {
        pHead_pre = pHead;
        pHead = pHead->next;
        LinkNode *pLink = pHead->head;
        LinkNode *pLink_pre = pLink;
        while (pLink->next)
        {
            pLink_pre = pLink;
            pLink = pLink->next;
            if (pLink->var == target)
            {
                RemoveClause_Suc(pHead_pre, cnf); // remove the clause
                pHead = pHead_pre;
                break;
            }
            else if (pLink->var == -target) //remove the literal
            {
                pLink_pre->next = pLink->next;
                delete (pLink);
                pLink = pLink_pre;
                pHead->head->var--;
            }
        }
    }
}

status FindEmptyClause(CNF *cnf)
{
    HeadNode *pHead = cnf->root;
    while (pHead->next)
    {
        pHead = pHead->next;
        if (pHead->head->var == 0)
            return TRUE;
    }
    return FALSE;
}

HeadNode *FindSingleClause_Pre(CNF *cnf)
{
    HeadNode *pHead = cnf->root;
    HeadNode *pre = pHead;
    while (pHead->next)
    {
        pre = pHead;
        pHead = pHead->next;
        if (pHead->head->var == 1)
            return pre;
    }
    return nullptr;
}

void RemoveClause_Suc(HeadNode *pHead, CNF *cnf)
{ // remove the successor Node of pHead
    cnf->ClauseNum--;
    HeadNode *target = pHead->next;
    ReleaseLine(target);
    pHead->next = target->next;
    delete (target);
}

void ReleaseLine(HeadNode *pHead)
{ //删除该行
    LinkNode *pLink = pHead->head;
    while (pLink->next)
    {
        LinkNode *t = pLink;
        pLink = pLink->next;
        delete (t);
    }
    delete (pLink);
}

void AddSingleClause(int target, CNF *cnf)
{
    cnf->ClauseNum++;
    LinkNode *head = new LinkNode;
    head->var = 1;
    head->next = new LinkNode;
    head->next->var = target;
    head->next->next = nullptr;
    HeadNode *pHead = new HeadNode;
    pHead->head = head;
    pHead->next = cnf->root->next;
    cnf->root->next = pHead;
}