#ifndef _STU_384_
#define _STU_384_


#ifndef _VALUE_
#define _VALUE_
#define TRUE 1  
#define FALSE 0  
#define OK 1  
#define ERROR 0  
#define INFEASIBLE -1  
#define OVERFLOW -2
#endif

#ifndef _ELEM_
#define _ELEM_ 
typedef int status;  
typedef int ElemType; //数据元素类型定义
#endif


#ifndef _LIST_
#define _LIST_
#define LIST_INIT_SIZE 100  
#define LISTINCREMENT  10  
typedef struct LNode{  //单链表（链式结构）结点的定义  
	ElemType data;  
	struct LNode *next;  
}LNode,*LinkList;  
#endif

#ifndef _LISTS_
#define _LISTS_
typedef struct LsNode{  //线性表的管理表定义（链式） 
	char name[255];
	LinkList L;
	struct LsNode *next; 
}LsNode,*LISTS;
#endif 


#endif
