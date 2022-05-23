/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "stu.h"
#include "addition.h"
#define N 255
#define LNE "该线性表不存在！"

//void menu(void);
//void judge(int flag); 

LinkList L = NULL;
LISTS Lists = NULL;
char name[N];	//名字最长为N

int main(void){
	INIT(Lists, L);
	menu();
	int op=1;
	
			
	while(op){
		status flag = INFEASIBLE;
		ElemType e;		int t=0;
		memset(name, 0, sizeof(name));
		printf("    请选择你的操作[0~24]: ");
		scanf("%d", &op);
		
	    switch(op){
			case 1:
				flag = InitList(L);
				if(flag == OK)	printf("初始化成功！");
				else	printf("初始化失败！（表已存在）");
				break;
			case 2:
				flag = DestroyList(L);
				judge(flag);
				break;
			case 3:
				flag = ClearList(L);
				judge(flag);
				break;
			case 4:
				flag = ListEmpty(L);
				if(flag == TRUE)	printf("空！");
				else if(flag == FALSE)	printf("非空！");
				else printf(LNE);
				break;
			case 5:
				t = ListLength(L);
				if(t == INFEASIBLE)	printf(LNE);
				else	printf("线性表长度为 %d", t);
				break;
			case 6:
				printf("输入元素序号： ");
				scanf("%d", &t);
				flag = 	GetElem(L, t, e);
				if(flag == OK)	printf("第%d个元素是 %d", t, e);
				else if(flag == ERROR)	printf("该序号不存在！");
				else printf(LNE); 
				break;
			case 7:
				printf("输入目标元素： ");
				scanf("%d", &e);
				flag = LocateElem(L, e);
				if(flag == INFEASIBLE)	printf(LNE);
				else if(flag == ERROR)	printf("该元素不存在！");
				else printf("元素%d的序号是 %d", e, flag);
				break;
			case 8:
				printf("输入目标元素： ");
				scanf("%d", &e);
				ElemType pre;
				flag = PriorElem(L, e, pre);
				if(flag == OK)	printf("元素%d的前驱是 %d", e, pre);
				else if(flag == ERROR)	printf("该元素不存在或无前驱！");
				else printf(LNE);
				break;
			case 9:
				printf("输入目标元素： ");
				scanf("%d", &e);
				ElemType next;
				flag = NextElem(L, e, next);
				if(flag == OK)	printf("元素%d的后继是 %d", e, next);
				else if(flag == ERROR)	printf("该元素不存在或无后继！");
				else printf(LNE);
				break;
			case 10:
				printf("输入位置： ");	scanf("%d", &t); 
				printf("输入元素： ");	scanf("%d", &e);
				flag = ListInsert(L, t, e);
				judge(flag);
				break;
			case 11:
				printf("输入位置： ");	scanf("%d", &t); 
				flag = ListDelete(L, t, e);
				if(flag == OK)	printf("删除 %d 成功", e);
				else if(flag == ERROR)	printf("该序号不存在！");
				else printf(LNE);
				break;
			case 12:
				flag = ListTraverse(L);
				if(flag == OK)	printf("遍历完毕！");
				else if(flag == ERROR) printf("空表！");
				else printf(LNE); 
				break; 
				
	/*----------------------------附加题-----------------------------*/	
			case 13:
				flag = reverseList(L);
				judge(flag);
				break;
			case 14:
				printf("输入倒数序号： ");
				scanf("%d", &t);
				flag = RemoveNthFromEnd(L, t);
				judge(flag);
				break;
			case 15:
				flag = sortList(L);
				judge(flag);
				break;
			case 16:
				printf("输入存储文件： ");
				scanf("%s", name); 
				flag = SaveList(L, name);
				if(flag == OK)	printf("保存成功！");
				else if(flag == ERROR)	printf("表为空！");
				else printf(LNE); 
				break;
			case 17:
				printf("输入读取文件： ");
				scanf("%s", name);
				flag = LoadList(L, name);
				if(flag == OK)	printf("读取成功！");
				else if(flag == ERROR)	printf("读取错误！（文件不存在）");
				else printf("线性表已存在且不为空！"); 
				break;
			case 18:
				printf("输入新建线性表名称： ");
				scanf("%s", name);
				flag = AddList(Lists, name);
				if(flag == OK)	printf("新建成功！");
				else	printf("新建失败！（重名、空间不足等）");
				break;
			case 19:
				printf("输入删除线性表名称： ");
				scanf("%s", name);
				flag = RemoveList(Lists, name);
				judge(flag);
				break;
			case 20:
				printf("输入查找线性表名称： ");
				scanf("%s", name);
				t = LocateList(Lists, name);
				if(t == 0)	printf("未找到！");
				else	printf("线性表 %s 的序号是 %d", name, t); 
				break;
			case 21:
				printf("输入目标线性表的名称： ");
				scanf("%s", name);
				flag = SwitchList(Lists, L, name);
				judge(flag);
				break;
			case 22:
				flag = ListsTraverse(Lists);
				if(flag == ERROR)	printf("无线性表！"); 
				break;
			case 23:
				flag = GetName(Lists, L, name);
				if(flag == OK)	printf("当前线性表为 %s", name); 
				else if(flag == ERROR)	printf("不在管理表中！");
				else printf(LNE);
				break;
			case 24:
				printf("输入线性表名称： ");
				scanf("%s", name);
				flag = UploadList(Lists, L, name);
				if(flag == OK)	printf("添加成功！");
				else if(flag == ERROR)printf("添加失败！（已在管理表中或重名）");
				else printf(LNE);
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
		printf("\n\n"); 
	}//end of while
	
	
	printf("欢迎下次再使用本系统！\n");
}//end of main()


