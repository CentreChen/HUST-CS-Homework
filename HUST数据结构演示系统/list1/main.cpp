/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "def.h"
#include "stu.h"
#include "addition.h"
#define N 255
#define LNE "该线性表不存在!"

//void menu(void);
//void judge(int flag); 

SqList L;
LISTS Lists;
char name[N];	//名字最长为N

int main(void){
	menu();
	L.elem = NULL;
	InitLists(Lists);
	int op=1;		
	while(op){
		status flag = INFEASIBLE;
		ElemType e;		int i=0, t=0;
		memset(name, 0, sizeof(name));
		printf("    请选择你的操作[0~24]: ");
		scanf("%d",&op);
	    switch(op){
			case 1:
				if(InitList(L)==OK)	printf("线性表创建成功！\n");
				else printf("线性表创建失败！(已存在)\n");
				getchar();
				break;
			case 2:
				if(DestroyList(L)==OK)	printf("线性表销毁成功！\n");
				else printf("线性表销毁失败！(不存在)\n");
				getchar();
				break;
			case 3:
				if(ClearList(L)==OK)	printf("线性表清空成功！\n");
				else printf("线性表清空失败！(不存在)\n");
				getchar();
				break;
			case 4:
				flag = ListEmpty(L); 
				if(flag==TRUE)		printf("空！\n");
				else if(flag==ERROR)printf("不为空！\n");
				else	printf(LNE);
				getchar();
				break;
			case 5:
				t = ListLength(L); 
				if(t==INFEASIBLE)	printf(LNE);
				else printf("当前线性表长度为 %d\n", t);
				getchar();
				break;
			case 6:
				printf("输入待访问元素序号： ");
				scanf("%d", &i);
				flag = GetElem(L, i, e);
				if(flag == OK)			printf("第%d个元素为 %d\n", i, e);
				else if(flag == ERROR)	printf("非法访问!(不存在该序号元素)\n");
				else printf(LNE);
				getchar();
				break;
			case 7:
				printf("输入目标元素： ");
				scanf("%d", &e);
				i = LocateElem(L, e);
				if(i == INFEASIBLE)		printf(LNE);
				else if(i == ERROR)	printf("不存在该元素！\n");
				else printf("元素 %d 的序号为 %d\n", e, i);  
				getchar();
				break;
			case 8:
				printf("输入目标元素： ");
				scanf("%d", &e);
				ElemType pre;
				flag = PriorElem(L, e, pre);
				if(flag == INFEASIBLE)	printf(LNE);
				else if(flag == ERROR)	printf("不存在该元素或该元素无前驱！\n");
				else printf("元素 %d 的前驱为 %d\n", e, pre);  
				getchar();
				break;
			case 9:
				printf("输入目标元素： ");
				scanf("%d", &e);
				ElemType next;
				flag = NextElem(L, e, next);
				if(flag == INFEASIBLE)	printf(LNE);
				else if(flag == ERROR)	printf("不存在该元素或该元素无后继！\n");
				else printf("元素 %d 的后继为 %d\n", e, next);     
				getchar();
				break;
			case 10:
				printf("输入位置（0表示插入到末尾）： ");	scanf("%d", &i); 
				printf("输入元素： ");	scanf("%d", &e);
				flag = ListInsert(L, i, e);
				if(flag == OK)	printf("插入成功！\n");
				else if(flag == ERROR) printf("非法的插入位置!\n");
				else printf(LNE);
				getchar();
				break;
			case 11:
				printf("输入待删除的位置： ");	scanf("%d", &i);
				flag = ListDelete(L, i, e);
				if(flag == OK)	printf("删除成功，被删除元素为 %d\n", e);
				else if(flag == ERROR) printf("该位置无元素！\n");
				else printf(LNE); 
				getchar();
				break;
			case 12:
				flag = ListTraverse(L);
				if(flag == OK)	printf("success!\n");
				else if(flag == ERROR) printf("线性表是空表！\n");
				else printf(LNE);
				getchar();
				break;
	/*---------------------附加题------------------------------*/
			case 13:
				if(L.elem == NULL)		printf(LNE);
				else if(L.length == 0)	printf("线性表是空表！\n");
				else printf("最大的连续子数组和为 %d\n", MaxSubArray(L));
				getchar();
				break; 
			case 14:
				if(L.elem == NULL)		printf(LNE);
				else if(L.length == 0)	printf("线性表是空表！\n");
				else{
					printf("输入期望的子数组和k: ");
					scanf("%d", &t);
					printf("和为 %d 的连续子数组有 %d 个\n", t, SubArrayNum(L,t));
				}
				getchar();
				break; 
			case 15:
				judge(sortList(L));
				getchar();
				break;
			case 16:
				printf("输入保存到的文件名： ");	//不支持空格 
				scanf("%s", name);
				flag = SaveList(L, name);
				judge(flag);
				getchar();
				break;
			case 17:
				printf("输入读取的文件名： ");	//不支持空格 
				scanf("%s", name);
				flag = LoadList(L, name);
				if(flag ==INFEASIBLE)	printf("表已存在，无法读取\n");
				else if (flag==ERROR)	printf("文件不存在\n");
				else	printf("成功"); 
				getchar();
				break;
			case 18:
				printf("输入新建的线性表名： ");
				scanf("%s", name);
				flag = AddList(Lists, name);
				judge(flag); 
				getchar();
				break;
			case 19:
				printf("输入待删除的线性表名： ");
				scanf("%s", name);
				flag = RemoveList(Lists, name);
				judge(flag); 
				getchar();
				break;
			case 20:
				printf("输入线性表名称： ");
				scanf("%s", name); 
				flag = SwitchList(Lists, L, name);
				judge(flag); 
				getchar();
				break;
			case 21:
				printf("输入线性表名称： ");
				scanf("%s", name); 
				flag = LocateList(Lists, name);
				if(flag == INFEASIBLE)	printf("不存在!\n");
				else	printf("%s 的位置是 %d\n", name, flag);
				getchar();
				break;
			case 22:
				flag = ListsTraverse(Lists);
				judge(flag);
				getchar();
				break;
			case 23:
				flag = GetName(Lists, L);
				judge(flag);
				getchar();
				break;
			case 24:
				printf("输入线性表名称： ");
				scanf("%s", name); 
				flag = UploadList(Lists, L, name);
				if(flag == OK)	printf("添加成功！\n");
				else if(flag == ERROR)	printf("添加失败！（已存在或管理表空间不足）\n");
				else printf(LNE);			
				getchar();
				break;
			case 0:
				break;	
			case 999:
				menu();
				break;	
			default:	//未定义指令，重启系统 
				system("cls");
				menu();
				break;
		}//end of switch
		printf("\n"); 
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()


