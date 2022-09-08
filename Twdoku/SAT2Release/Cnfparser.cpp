#include "Global.h"

status readCNF(string fileName, CNF **pCNF)
{
    string HeadPath = ".\\testData\\";
    string path = HeadPath + fileName;
    FILE *fp = fopen(path.c_str(), "r");
    if (!fp)
    {
        printf("Can not find the file!\n");
        return ERROR;
    }
    char ch, buff[10000];
    fread(&ch, sizeof(char), 1, fp);
    while (ch != 'p')
    {
        fgets(buff, 10000, fp); // useless data
        fread(&ch, sizeof(char), 1, fp);
    }
    fread(buff, sizeof(char), 5, fp);
    CNF *cnf = new CNF;
    fscanf(fp, "%d", &cnf->VarNum); // p line
    fscanf(fp, "%d", &cnf->ClauseNum);
    cnf->root = new HeadNode;
    HeadNode *rear = cnf->root; //子句尾插
    int tmp;
    for (int i = 0; i < cnf->ClauseNum; i++)
    {
        LinkNode *head = new LinkNode;
        LinkNode *tail = head;
        int cnt = 0;
        fscanf(fp, "%d", &tmp);
        while (tmp)
        {
            if (abs(tmp) > cnf->VarNum)
            {
                printf("CNF have a literal that bigger than VarNum\n");
                exit(-1); // CNF is wrong
            }
            cnt++;
            tail->next = new LinkNode;
            tail->next->var = tmp;
            tail = tail->next;
            fscanf(fp, "%d", &tmp);
        }
        tail->next = nullptr;
        head->var = cnt; // head node's var store the num of literals
        rear->next = new HeadNode;
        rear->next->head = head;
        rear = rear->next;
    }
    rear->next = nullptr;
    fclose(fp);
    *pCNF = cnf;
    return OK;
}

void TraverseCNF(CNF *cnf)
{ // have not show the empty clause
    if (cnf == nullptr)
    {
        printf("CNF not found!\n");
        exit(-1);
    }
    HeadNode *pHead = cnf->root;
    while (pHead->next)
    {
        pHead = pHead->next;
        LinkNode *pLink = pHead->head;
        while (pLink->next)
        {
            pLink = pLink->next;
            printf("%d ", pLink->var);
        }
        printf("\n");
    }
}

void DestroyCNF(CNF **pCNF)
{
    CNF *cnf = *pCNF;
    if (cnf == nullptr)
    {
        printf("CNF not found!\n");
        exit(-1);
    }
    HeadNode *pHead = cnf->root;
    while (pHead->next)
    {
        HeadNode *tHead = pHead;
        pHead = pHead->next;
        delete (tHead);
        LinkNode *pLink = pHead->head;
        while (pLink->next)
        {
            LinkNode *tLink = pLink;
            pLink = pLink->next;
            delete (tLink);
        }
        delete (pLink);
    }
    delete (pHead);
    delete (*pCNF);
    *pCNF = nullptr;
}

status SaveCNF(string fileName, CNF *cnf)
{
    if (cnf == nullptr)
    {
        printf("CNF not found!\n");
        return ERROR;
    }
    string HeadPath = ".\\testData\\";
    string path = HeadPath + fileName;
    FILE *fp = fopen(path.c_str(), "w");
    if (!fp)
    {
        printf("File open error!\n");
        return ERROR;
    }
    fprintf(fp, "%s", "p cnf ");
    fprintf(fp, "%d ", cnf->VarNum);
    fprintf(fp, "%d\n", cnf->ClauseNum);

    HeadNode *pHead = cnf->root;
    while (pHead->next)
    {
        pHead = pHead->next;
        LinkNode *pLink = pHead->head;
        while (pLink->next)
        {
            pLink = pLink->next;
            fprintf(fp, "%d  ", pLink->var);
        }
        // fprintf(fp, "%d %d\n", 0, pHead->head->var);
        fprintf(fp, "%d\n", 0);
    }
    fclose(fp);
    return OK;
}

/*
void CopyCNF(CNF **dest, CNF *src)  //全尾插
{
    CNF *cnf = new CNF;
    cnf->VarNum = src->VarNum;
    cnf->ClauseNum = src->ClauseNum;
    cnf->root = new HeadNode;
    HeadNode *rear = cnf->root;
    HeadNode *srcHeadNode = src->root;
    while (srcHeadNode->next)
    {
        srcHeadNode = srcHeadNode->next;
        LinkNode *srcLinkNode = srcHeadNode->head;
        LinkNode *head = new LinkNode;
        LinkNode *tail = head;
        while (srcLinkNode->next)
        {
            srcLinkNode = srcLinkNode->next;
            tail->next = new LinkNode;
            tail->next->var = srcLinkNode->var;
            tail = tail->next;
        }
        tail->next = nullptr;
        head->var = srcHeadNode->head->var;
        rear->next = new HeadNode;
        rear->next->head = head;
        rear = rear->next;
    }
    rear->next = nullptr;
    *dest = cnf;
}
*/

void CopyCNF(CNF **dest, CNF *src) //子句头插
{
    CNF *cnf = new CNF;
    cnf->VarNum = src->VarNum;
    cnf->ClauseNum = src->ClauseNum;
    cnf->root = new HeadNode;
    cnf->root->next = nullptr;
    HeadNode *srcHeadNode = src->root;
    while (srcHeadNode->next)
    {
        srcHeadNode = srcHeadNode->next;
        LinkNode *srcLinkNode = srcHeadNode->head;
        LinkNode *head = new LinkNode;
        LinkNode *tail = head;
        while (srcLinkNode->next)
        {
            srcLinkNode = srcLinkNode->next;
            tail->next = new LinkNode;
            tail->next->var = srcLinkNode->var;
            tail = tail->next;
        }
        tail->next = nullptr;
        head->var = srcHeadNode->head->var;
        HeadNode *p = new HeadNode;
        p->head = head;
        p->next = cnf->root->next;
        cnf->root->next = p;
    }
    *dest = cnf;
}

/*
void CopyCNF(CNF **dest, CNF *src)  //文字头插
{
    CNF *cnf = new CNF;
    cnf->VarNum = src->VarNum;
    cnf->ClauseNum = src->ClauseNum;
    cnf->root = new HeadNode;
    HeadNode *rear = cnf->root;
    HeadNode *srcHeadNode = src->root;
    while (srcHeadNode->next)
    {
        srcHeadNode = srcHeadNode->next;
        LinkNode *srcLinkNode = srcHeadNode->head;
        LinkNode *head = new LinkNode;
        head->next = nullptr;
        while (srcLinkNode->next)
        {
            srcLinkNode = srcLinkNode->next;
            LinkNode *p = new LinkNode;
            p->var = srcLinkNode->var;
            p->next = head->next;
            head->next = p;
        }
        head->var = srcHeadNode->head->var;
        rear->next = new HeadNode;
        rear->next->head = head;
        rear = rear->next;
    }
    rear->next = nullptr;
    *dest = cnf;
}
*/
/*
void CopyCNF(CNF **dest, CNF *src)  //全头插
{
    CNF *cnf = new CNF;
    cnf->VarNum = src->VarNum;
    cnf->ClauseNum = src->ClauseNum;
    cnf->root = new HeadNode;
    cnf->root->next = nullptr;
    HeadNode *srcHeadNode = src->root;
    while (srcHeadNode->next)
    {
        srcHeadNode = srcHeadNode->next;
        LinkNode *srcLinkNode = srcHeadNode->head;
        LinkNode *head = new LinkNode;
        head->next = nullptr;
        while (srcLinkNode->next)
        {
            srcLinkNode = srcLinkNode->next;
            LinkNode *pL = new LinkNode;
            pL->var = srcLinkNode->var;
            pL->next = head->next;
            head->next = pL;
        }
        head->var = srcHeadNode->head->var;

        HeadNode* pH = new HeadNode;
        pH->head = head;
        pH->next = cnf->root->next;
        cnf->root->next = pH;
    }
    *dest = cnf;
}
*/