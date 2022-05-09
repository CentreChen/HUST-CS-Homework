#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "addition.h"
#define maxleng 10005



TElemType *pp = NULL; 
void Create(BiTree &root)
{
	if(pp->key == -1) return;

	if (pp->key == 0){
		pp++;
		root = NULL;
	}
	else{
		
		root = (BiTree)malloc(sizeof(BiTNode));//生成根结点
		root->data = *pp++;
		Create(root->lchild);//递归构造左子树
		Create(root->rchild); // ;递归构造右子树 递归构造右子树
	}
}

status CreateBiTree(BiTree &T, TElemType definition[])
/*1根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    bool bw[10005];
	memset(bw, 0, sizeof(bw)); 
    for(int i=0; definition[i].key!=-1; i++){
    	KeyType key = definition[i].key;
    	if(bw[key] == 0) bw[key]=1;
    	else if(key) return ERROR;	//Key重复 
	}
    
    pp = definition;
	Create(T);
	return OK;
}


status DestroyBiTree(BiTree &T)
//2销毁二叉树 
{
   if (T)
   {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
   }
   return OK;
}

status ClearBiTree(BiTree &T)
//3将二叉树设置成空，并删除所有结点，释放结点空间
{
	DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    T->data.key = 0;
    strcpy(T->data.others, "null");
    
	
	free(T); 
	T = NULL;
	return OK;
}

status BiTreeEmpty(BiTree T)
//4初始条件是二叉树T存在；操作结果是若T为空二叉树则返回TRUE，否则返回FALSE；
{
	if(T == NULL) return TRUE;
	else if(T->lchild==NULL && T->rchild==NULL && T->data.key==0)
		return TRUE;
	else return FALSE;
}

int BiTreeDepth(BiTree T)
//5求二叉树T的深度
{
	int ans = 0;
	if(T && BiTreeEmpty(T)==FALSE)
	{
		int Ldep = BiTreeDepth(T->lchild);
		int Rdep = BiTreeDepth(T->rchild);
		if (Ldep > Rdep) ans = Ldep+1;
		else ans = Rdep+1; 
	}
	return ans;
}


BiTNode* LocateNode(BiTree T,KeyType e)
//6查找结点(inorder)
{
	BiTree t = T; 
	BiTree st[maxleng];
	int top = 0;
	do{
		while(t){	//找最左节点 
			if(top == maxleng) exit(OVERFLOW);
			st[top++] = t;
			t = t->lchild;
		}
		if(top){
			t = st[--top];	//退栈 
			if(t->data.key == e)
				return t;
			t = t->rchild;
		}
	}while(top || t);
	return NULL;
}

status Assign(BiTree &T, KeyType e, TElemType value)
//7实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
	BiTree target = LocateNode(T, e);
	if(target){
		BiTree p = LocateNode(T, value.key);
		if(!p || p==target){	//防止Key重复 
			target->data = value;
			return OK;
		} 
	}
	return ERROR;
}


BiTNode* GetParent(BiTree T, KeyType e)
//实现获得双亲结点
{
    if(T->data.key == e) return NULL;	//根节点无双亲 
    
	BiTree t = T; 
	BiTree st[maxleng];
	int top = 0;
	do{		//中序 
		while(t){
			if(top == maxleng) exit(OVERFLOW);
			st[top++] = t;
			t = t->lchild;
		}
		if(top){
			t = st[--top];
			if(t->lchild && t->lchild->data.key==e)	//t是目标节点的双亲 
				return t;
			else if(t->rchild && t->rchild->data.key==e) 
				return t;
			t = t->rchild;
		}
	}while(top || t);
	
	return NULL;
}


BiTNode* GetSibling(BiTree T, KeyType e)
//8实现获得兄弟结点
{
    BiTree parent = GetParent(T, e);
	if(parent){
		if(parent->lchild && parent->lchild->data.key==e)	//t是目标节点的双亲 
			return parent->rchild;
		else if(parent->rchild && parent->rchild->data.key==e) 
			return parent->lchild;
	} 
	return NULL;
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//9插入结点。此题允许通过增加其它函数辅助实现本关任务
{
	int flag = ERROR;
	BiTree p = (BiTNode *)malloc(sizeof(BiTNode));	//创建待插入节点 
	p->data = c;
	p->lchild = p->rchild = NULL;
	
	if(LR == -1){	//作为根节点插入 
		p->rchild = T;
		T = p;
		flag = OK; 
	}
	else{
		if(LocateNode(T, c.key) == NULL){	//防止Key重复 
			BiTree target = LocateNode(T, e);
			if(target){	//可以插入 
				if(LR == 0){
					p->rchild = target->lchild;
					target->lchild = p;
				}
				else if(LR == 1){
					p->rchild = target->rchild; 
					target->rchild = p;
				}
				flag = OK;
			}
		}
	}
	if(flag == ERROR) free(p);	//插入失败,释放空间 
	return flag;
}


BiTree NewChild(BiTree target)
//返回用来替代被删除的节点的孩子节点 
{
	if(target->lchild){
		if(target->rchild){
			BiTree t = target->lchild;
			while(t->rchild){	//找最右节点 
				t = t->rchild;
			}
			t->rchild = target->rchild;
		}
		return target->lchild;
	} 
	else return target->rchild;
}

status DeleteNode(BiTree &T,KeyType e)
//10删除结点。此题允许通过增加其它函数辅助实现本关任务(非递归)
{
	status flag = ERROR;
	BiTree target=NULL, parent=NULL; 
	if(T->data.key == e){	//删除根节点 
		target = T;
		T = NewChild(target);
		free(target);
		flag = OK;
	}
	else if(parent = GetParent(T,e)){
		if(parent->lchild && parent->lchild->data.key==e){	//删除左孩子 
			target = parent->lchild; 
			parent->lchild = NewChild(target);
		}
		else if(parent->rchild && parent->rchild->data.key==e){	//删除右孩子 
			target = parent->rchild;
			parent->rchild = NewChild(target);			
		}
		free(target); 
		flag = OK;
	}
	return flag;
}


void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//11先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T){
		visit(T);
   		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//12中序遍历二叉树T
{
	BiTree t = T; 
	BiTree st[maxleng];
	int top = 0;
	do{
		while(t){	//找最左节点 
			if(top == maxleng) exit(OVERFLOW);
			st[top++] = t;
			t = t->lchild;
		}
		if(top){
			t = st[--top];	//退栈 
			visit(t);
			t = t->rchild;
		}
	}while(top || t);
	return OK;
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//13后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T){
    	PostOrderTraverse(T->lchild, visit); 
		PostOrderTraverse(T->rchild, visit); 
		visit(T);
	}
	return OK;
    /********** End **********/
}


status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//14按层遍历二叉树T
{
	BiTree Array[maxleng];
	int head=0, tail=0;
	
	Array[tail++] = T;
	while(tail > head){
		BiTree t = NULL; 
		if(t = Array[head]){
			visit(t);
			Array[tail++] = t->lchild;
			Array[tail++] = t->rchild;
		}
		head++;
	}
	return OK;
}

int MaxPathSum(BiTree T)
//15最大路径和, 初始条件是二叉树T存在；操作结果是返回根节点到叶子结点的最大路径和；
{
	int ans = 0;
	if(T){
		ans = T->data.key;
		int L = MaxPathSum(T->lchild);
		int R = MaxPathSum(T->rchild);
		
		if(L>R) ans += L;
		else ans += R;
	}
	return ans;
}


void GetWay(BiTree t, KeyType e, BiTree st[])
//后序遍历寻找路径，路径存在st数组中 
{
	BiTree pre = NULL;
	int top = 0; 
	bool flag = 1;
	
	do{
		while(t){
			st[top++] = t;
			if(t->data.key == e){
				st[top] = NULL;
				return ;
			} 
			t = t->lchild;
		}
		pre = NULL;	flag = 1;
		while(flag && top){
			t = st[top-1];
			if(t->rchild == pre){
				//print
				top--;
				pre = t;
			}
			else{
				t = t->rchild;
				flag = 0;
			}
		}
	}while(top);
	
}

BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
//16最近公共祖先, 初始条件是二叉树T存在；操作结果是该二叉树中e1节点和e2节点的最近公共祖先；
{
	BiTree st1[maxleng], st2[maxleng];
	GetWay(T, e1, st1);
	GetWay(T, e2, st2);
	
	int i = 0, j = 0;
	while(st1[i] && st2[j] && st1[i]==st2[j]){
		i++;
		j++;
	}
	
	return st1[i-1];
}


status InvertTree(BiTree &T)
//17翻转二叉树, 初始条件是线性表L已存在；操作结果是将T翻转，使其所有节点的左右节点互换；
{
	if(T){
		BiTree tmp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = tmp;
		InvertTree(T->lchild);
		InvertTree(T->rchild);
	}
	return OK;
}

status SaveBiTree(BiTree T, char FileName[])
//18将二叉树的结点数据写入到文件FileName中
{
    FILE* fp;
	if ((fp=fopen(FileName,"wb"))==NULL){
		printf("File open error!\n ");
		return ERROR;
	}
	
	BiTree st[maxleng];
	int top = 0;
	TElemType null0 = {0, "null"};
	st[top++] = T;
	while(top){
		BiTree p = st[--top];
		if(p) {
			fwrite(&p->data, sizeof(TElemType), 1, fp);
			st[top++] = p->rchild;
			st[top++] = p->lchild; 
		}
		else fwrite(&null0, sizeof(TElemType), 1, fp);	
	}
	TElemType end = {-1, "null"};
	fwrite(&end, sizeof(TElemType), 1, fp);
	fclose(fp);
	return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//19读入文件FileName的结点数据，创建二叉树
{
	TElemType definition[maxleng];
	FILE* fp;
	if ((fp=fopen(FileName,"rb"))==NULL){
		printf("File open error!\n ");
		return ERROR;
	}
	TElemType t;
	int cnt = 0;
	do{
		fread(&t, sizeof(TElemType), 1, fp);
		definition[cnt++] = t; 
	}while(t.key != -1);
	
	fclose(fp);
	return CreateBiTree(T, definition);
}



status SwitchTree(TREES Trees, BiTree &T, char TreeName[])
// 20将当前树切换至name 
{
	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Trees.length; i++){
		if(strcmp(Trees.elem[i].name, TreeName) == 0){
			flag = OK;
			T = Trees.elem[i].T;
		}
	}
	return flag;
}


status AddBiTree(TREES &Trees,char TreeName[])
// 21只需要在Trees中增加一个名称为TreeName的树
{
    status flag = ERROR;
    int i = Trees.length;
    
    BiTree t = (BiTree)malloc(sizeof(BiTNode));
	if(t){
		t->lchild = t->rchild = NULL;
		t->data.key = 0;
		flag = OK; 
	}
	
    if(flag == OK){
    	Trees.elem[i].T = t;
    	strcpy(Trees.elem[i].name, TreeName);
   		Trees.length++;
	}
    return flag;
}

status RemoveBiTree(TREES &Trees,char TreeName[])
// 22Lists中删除一个名称为TreeName的线性表
{
    status flag = ERROR;

    for(int i=0; flag==ERROR && i<Trees.length; i++)
    {
        if(strcmp(Trees.elem[i].name,TreeName) == 0)
        {
            for(; i<Trees.length-1; i++)
                Trees.elem[i] = Trees.elem[i+1];
            // flag = DestroyList(Trees.elem[i].L);
            flag = OK;
            Trees.length--;
        }
    }
    return flag;
}


status LocateBiTree(TREES Trees, char TreeName[])
// 23查找TreeName表的位置 
{
	status flag = INFEASIBLE;
	for(int i=0; flag==INFEASIBLE && i<Trees.length; i++){
		if(strcmp(Trees.elem[i].name, TreeName) == 0){
			flag = i+1;
			break;
		}
	}
	return flag;
}


status Upload(TREES &Trees, BiTree T, char TreeName[])
// 24切换当前树为TreeName 
{
	status flag = ERROR;
    int i = LocateBiTree(Trees, TreeName)-1;
    if(i == INFEASIBLE-1){
    	i = Trees.length++;
    	strcpy(Trees.elem[i].name, TreeName);
		flag = ERROR; 
	}
	else flag = OK; 
    
	Trees.elem[i].T = T;
//	strcpy(Trees.elem[i].name, TreeName);
//	Trees.length++;
    return flag;
}

	




