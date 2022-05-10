#include <string.h>
#include "def.h"
//#include "list.h"
void menu(void)
{
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("	1.  InitList	\t13. reverseList\n");
	printf("	2.  DestroyList \t14. RemoveNthFromEnd\n");
	printf("	3.  ClearList	\t15. sortList \n");
	printf("	4.  ListEmpty	\t16. SaveList\n");
	printf("	5.  ListLength	\t17. LoadList\n");
	printf("	6.  GetElem	    \t18. AddList\n");
	printf("	7.  LocateElem	\t19. RemoveList\n");
	printf("	8.  PriorElem	\t20. LocateList\n");
	printf("	9.  NextElem	\t21. SwitchList\n");
	printf("	10. ListInsert	\t22. ListsTraverse\n");
	printf("	11. ListDelete	\t23. GetName\n");
	printf("	12. ListTrabverse\t24. UploadList\n");
	printf("	0.  Exit	    \t999. menu\n");
	printf("-------------------------------------------------\n");
}


void judge(int flag)
{
	switch(flag)
	{
		case OK:
			printf("操作成功！");
			break;
		case ERROR:
			printf("操作失败！（非法参数，目标不存在等）");
			break; 
		case INFEASIBLE:
			printf("表不存在！");
			break;
		default:
			printf("未知错误！");
			break;
	}
}

void INIT(LISTS &Lists, LinkList &L)
{
	Lists = (LsNode*)malloc(sizeof(LsNode));
	Lists->L = NULL;
	strcpy(Lists->name, "LISTS_HEAD");
	Lists->next = NULL;
}

status SwitchList(LISTS Lists, LinkList &L, char ListName[])
// 21切换当前线性表为ListName 
{
	status flag = ERROR;
	LISTS p = Lists;
    while(flag==ERROR && p->next){
    	p = p->next;
    	if(strcmp(p->name, ListName) == 0){
    		L = p->L;
    		flag = OK;
		}
	}
	return flag;
}

status ListsTraverse(LISTS Lists)
// 22遍历所有线性表名称 
{
	if(Lists->next == NULL)
		return ERROR;
	
	LISTS p = Lists->next;
	int i = 1;
	printf("\n----------------- all lists -------------------\n");
	printf("%d\t%s", i, p->name);
    while(p->next){
    	p = p->next;
    	i++;
    	printf("\n%d\t%s", i, p->name);
	}
	printf("\n-------------------- end -----------------------\n");
	return OK;
}


status GetName(LISTS Lists, LinkList L, char *ListName)//
// 23查看当前线性表名称
{
	if(L == NULL)	return INFEASIBLE;
	
	status flag = ERROR;
	LISTS p = Lists;
    while(flag==ERROR && p->next){
    	p = p->next;
    	if(p->L == L){
			strcpy(ListName, p->name);
    		flag = OK;
		}
	}
	return flag;
}

status UploadList(LISTS &Lists, LinkList L, char ListName[])
// 24将当前表添加到管理表
{
	if(L == NULL)	return INFEASIBLE;
	status flag = OK;
	LISTS p = Lists;
	while(p->next){	//找表尾，查重名或重表 
		p = p->next;
		if(p->L==L || strcmp(p->name, ListName)==0)
			flag = ERROR; 
	}
	
	if(flag == OK){
		LISTS s = (LsNode*)malloc(sizeof(LsNode));
		if(s == NULL)
			flag = ERROR;
		else{
			strcpy(s->name, ListName);
			s->L = L;
			s->next = NULL; 
			
			if(flag == OK)
				p->next = s;
		}
	}
	
	return flag;
}
 

