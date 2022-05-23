#include <string.h>
#include "def.h"

status InitList(LinkList &L)
// 1线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	status flag = INFEASIBLE;	//默认失败

	if(L){	//L存在 
		flag = INFEASIBLE;
	}
	else{
		L = (LNode*)malloc(sizeof(LNode));	//创建表头 
		L->next = NULL;	//初始化
		flag = OK;
	}
	
	return flag;	//单一出口
}

status DestroyList(LinkList &L)
// 2如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if(L == NULL){	//L不存在 
		return INFEASIBLE;
	}

	LinkList p = L;
	while(p){	//释放空间 
		LinkList t = p;
		p = p->next;
		free(t);
	}
	L = NULL;	//置为未初始化 
	return OK;
}

status ClearList(LinkList &L)
// 3如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	if(L == NULL){	//不存在
		return INFEASIBLE; 
	}
	
	LinkList p = L->next;	//从第一个数据元素节点开始 
	while(p){	//释放空间 
		LinkList t = p;
		p = p->next;
		free(t); 
	}
	L->next = NULL;	//恢复初始化状态 
	return OK;
}

status ListEmpty(LinkList L)
// 4如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	status flag = INFEASIBLE;
	if(L == NULL){	//L不存在
		flag = INFEASIBLE; 
	} 
    else{
		if(L->next == NULL){    //判空
			flag = TRUE;
		}
		else{
			flag = FALSE;
		}
	}
	return flag;	//减少出口
}

int ListLength(LinkList L)
// 5如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	if(L == NULL){	//L不存在 
		return INFEASIBLE;
	}
	
	int len = 0;
	LinkList p = L; 
	while(p->next){
		p = p->next;
		len++;
	} 
	return len;
}

status GetElem(LinkList L, int i, ElemType &e)
// 6如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	
	if(L == NULL){	//L不存在 
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//默认访问失败
	if(i >= 1){
		LinkList p = L->next;
		int cnt = 0;
		while(p && ++cnt < i){	//利用短路，先判空，再判断序号 
			p = p->next;
		}
		if(cnt == i){	//合法访问 
			e = p->data; 
			flag = OK; //获取成功 
		} 
	}
	return flag;
}

status LocateElem(LinkList L,ElemType e)
// 7如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
	if(L == NULL){	//L does not exist
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//默认未找到 
	LinkList p = L->next;
	int cnt = 0;	
	while(flag == ERROR && p){
		cnt++;		//当前元素序号
		if(p->data == e){
			flag = cnt;	//存在
		}
		p = p->next;
	}
	return flag;
}


status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 8如果线性表L存在，获取线性表L中第一个e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L == NULL){	//L不存在 
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//默认未找到 
	LinkList p = L->next;
	while(flag==ERROR && p && p->next){	//找到e或遍历结束时停止 
		if(p->next->data == e){
			pre = p->data;
			flag = OK;
		}
		p = p->next;
	}
	return flag;
}


status NextElem(LinkList L,ElemType e,ElemType &next)
// 9如果线性表L存在，获取线性表L第一个e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L == NULL){
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//默认未找到 
	LinkList p = L->next;
	while(p){
		if(p->data==e && p->next){	//有后继 
			next = p->next->data;
			flag = OK;
		}
		p = p->next; 
	}
	return flag;
}


status ListInsert(LinkList &L,int i,ElemType e)
// 10如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L == NULL){
		return INFEASIBLE;
	} 
	
	status flag = ERROR;	//默认插入失败
	LinkList p = L;
	int cnt = 0;
	while(flag==ERROR && p){
		cnt++;	//p->next 的序号, null也算
		if(cnt == i){
			LNode *s;
			s = (LNode*)malloc(sizeof(LNode));
			s->data = e;
			s->next = p->next;
			p->next = s;
            flag = OK;
		}
		p = p->next;
	}
	return flag;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 11如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL){  //L不存在
        return INFEASIBLE;
    }

    status flag = ERROR;
    LinkList p = L;
    int cnt = 0;
    while(flag==ERROR && p && p->next){  //短路防止 NULL->next
        cnt++;  //p->next的序号
        if(cnt == i){
            LinkList delet = p->next;
            p->next = delet->next;
            e = delet->data;
            free(delet);
            flag = OK;
        }
        p = p->next;
    }
    return flag;
}

status ListTraverse(LinkList L)
// 12如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)  //L不存在
        return INFEASIBLE;
	if(L->next == NULL)	//空表 
		return ERROR;
	
    LinkList p = L->next;   //从第一个元素开始
    while(p){   //p==NULL 停止
        if(p->next)
            printf("%d ", p->data);
        else
            printf("%d\n", p->data);  //末结点
        p = p->next;
    }
    return OK;
}

status reverseList(LinkList &L)
// 13初始条件是线性表L已存在；操作结果是将L翻转；
{
	if(L == NULL)	return INFEASIBLE;

	LinkList pre, p;
	pre = NULL;
	p = L->next;
	while(p){
		LinkList t = pre;
		pre = p;
		p = p->next;
		pre->next = t;		
	}
	L->next = pre;
	return OK;
}


status RemoveNthFromEnd(LinkList &L, int n)
// 14初始条件是线性表L已存在且非空, 操作结果是该链表中倒数第n个节点；
{
	if(L == NULL)	return INFEASIBLE;
	int len = ListLength(L); 
	if(len < n)	return ERROR;	//非法位置 
	
	int id = len + 1 - n;	//待删除节点的序号 
//	LinkList p = L;
//	int cnt = 0;	//当前结点序号 
//	while(cnt < id-1 && p->next){
//		p = p->next;
//		cnt++;
//	}
//	LinkList t = p->next; 
//	p->next = p->next->next;
//	free(t);
//	return OK;
	ElemType e;
	return ListDelete(L, id, e);
}


status sortList(LinkList L)
// 15初始条件是线性表L已存在；操作结果是将L由小到大排序 
{
	if(L == NULL)
		return INFEASIBLE;
	
	LinkList done = NULL;	//已排好序的部分 
	while(done != L->next){
		LinkList pre = L;
		LinkList p = L->next;
		for(; p->next!=done; pre=p,p=p->next)
			if(p->data > p->next->data){
				pre->next = p->next;
				p->next = p->next->next;
				pre->next->next = p;
				p = pre->next;	//交换后回退 
			}
		done = p;
	}
	return OK;
}


status SaveList(LinkList L,char FileName[])
// 16如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL){	//L存在 
        return INFEASIBLE;
    }

    FILE *fout;
    fout = fopen(FileName, "wb");
    if(fout==NULL || L->next==NULL)	return ERROR;
    
    LinkList p = L->next;
    while(p){   //遍历
    	fwrite(&(p->data), sizeof(ElemType), 1, fout);
        p = p->next;
    }
    fclose(fout);
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 17如果线性表L不存在或空，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L!=NULL && L->next!=NULL){	//L存在 
        return INFEASIBLE;
    }

    FILE *fin;
    fin = fopen(FileName, "rb");
    if(fin == NULL)	return ERROR;
	 
    if(L == NULL)
		L = (LNode*)malloc(sizeof(LNode));  //创建表头
    LinkList tail = L;  //尾指针
    int e;
    while(fread(&e, sizeof(ElemType), 1, fin)){ //e存储读入的data
        LNode *s;
        s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        tail->next = s;
        tail = s;
    }
    tail->next = NULL;
    fclose(fin);
    return OK;
}


status AddList(LISTS &Lists,char ListName[])
// 18只需要在Lists中增加一个名称为ListName的空线性表
{
	status flag = OK;
	LISTS p = Lists;
	while(flag==OK && p->next){	//找表尾，查重名 
		p = p->next;
		if(strcmp(p->name, ListName) == 0)
			flag = ERROR; 
	}
	
	if(flag == OK){
		LISTS s = (LsNode*)malloc(sizeof(LsNode));
		if(s == NULL)
			flag = ERROR;
		else{
			strcpy(s->name, ListName);
			s->L = NULL;
			flag = InitList(s->L);
			s->next = NULL; 
			
			if(flag == OK)
				p->next = s;
		}
	}
	
	return flag;
}

status RemoveList(LISTS &Lists,char ListName[])
// 19在Lists中删除一个名称为ListName的线性表
{
    status flag = ERROR;
    
    LISTS p = Lists;
    while(flag==ERROR && p->next){
    	if(strcmp(p->next->name, ListName) == 0){
    		LISTS t = p->next;
			p->next = p->next->next;
    		free(t);
    		flag = OK;
		}
		else
    		p = p->next;
	}
	return flag;
}

int LocateList(LISTS Lists,char ListName[])
// 20在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    LISTS p = Lists;
    int i = 0;
    while(p->next){
    	p = p->next;
		i++;
    	if(strcmp(p->name, ListName) == 0)
    		return i;
	}
	return 0;
}


/*   21~24号函数在 addition.h中   */ 

