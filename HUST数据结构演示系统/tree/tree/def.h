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
typedef int KeyType;
typedef struct {  
	KeyType  key;  
	char others[20];
} TElemType; //二叉树结点类型定义
#endif

#ifndef _TREE_
#define _TREE_
typedef struct BiTNode{    //二叉链表结点的定义  
	TElemType data;  
	struct BiTNode *lchild,*rchild;  
} BiTNode, *BiTree; 
#endif

#ifndef _TREES_
#define _TREES_
#define TREES_INIT_SIZE 100
typedef struct TsNode{  //线性表的管理表定义（顺序表） 
	struct{
		char name[30];
		BiTree T;	
	}elem[TREES_INIT_SIZE];
	int length;
	int treesize;
}TREES;
#endif 


#endif
