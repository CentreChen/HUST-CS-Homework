#include <string.h>
#include "def.h"

status InitList(SqList& L)
// 1线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L.elem){
        return INFEASIBLE;  //L已存在
    }
    else{   //构造
        L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.listsize = LIST_INIT_SIZE;
        L.length = 0;
    }

    return OK;
}


status DestroyList(SqList& L)
// 2如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if(L.elem == NULL)	return INFEASIBLE;
	
	memset(L.elem, 0, sizeof(L.elem));
    L.listsize = 0;
    L.length = 0;
    free(L.elem);
    L.elem = NULL;
    return OK;
}


status ClearList(SqList& L)
// 3如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L.elem == NULL)
        return INFEASIBLE;
    
    memset(L.elem, 0, sizeof(L.elem));
    L.length = 0;   //长度清零
    return OK;
}


status ListEmpty(SqList L)
// 4如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    status flag = TRUE; //初始化为表空

    if(L.elem == NULL){
        flag = INFEASIBLE;  //L不存在
    }
    else if(L.length){   //L不为空
        flag = FALSE;
    }
    else flag = TRUE; 

    return flag;
}


status ListLength(SqList L)
// 5如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L.elem == NULL){
        return INFEASIBLE;  //线性表L不存在
    } 
    else{   //返回长度
        return L.length;
    }
}

status GetElem(SqList L,int i,ElemType &e)
// 6如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    status flag = OK;   //初始化为获取第i个元素成功

    if(L.elem == NULL){
        flag = INFEASIBLE;
    }
    else{
        if(i<1 || i>L.length){
            flag = ERROR;   //i不合法
        }
        else{
            e = L.elem[i-1];    //保存
        }
    }

    return flag;
}


int LocateElem(SqList L, ElemType e)
// 7如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    int flag = ERROR;   //初始化为L存在但未找到e

    if(L.elem == NULL) //线性表L不存在
        flag = INFEASIBLE;
    else{
        int i;
        for(i=0; i<L.length && flag==ERROR; i++)
        {   //找到就停
            if(L.elem[i] == e){
                flag = i+1; //位置序号
            }
        }
    }

    return flag;
    /********** End **********/
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 8如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    status flag = ERROR;    //初始化为L存在但未找到e

    if(L.elem == NULL){     //L不存在
        flag = INFEASIBLE;
    }
    else{
        if(L.elem[0] == e){ //判断有无前驱
            flag = ERROR;
        }
        else{
            for(int i=1; i<L.length && flag==ERROR; i++)
            {   //一旦找到e停止查找
                if(L.elem[i] == e){
                    flag = OK;
                    pre = L.elem[i-1];  //前驱保存在pre中
                }
            }
        }
    }

    return flag;
}


status NextElem(SqList L,ElemType e,ElemType &next)
// 9如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    status flag = ERROR;    //默认L存在

    if(L.elem == NULL){
        flag = INFEASIBLE;  //L不存在
    }
    else{
        if(L.elem[L.length-1] == e){    //后继不存在
            flag = ERROR;
        }
        else{
            int i;
            for(i=0; i<L.length-1 && flag==ERROR; i++){   //找到为止
                if(L.elem[i] == e){
                    flag = OK;
                    next = L.elem[i+1];
                }
            }
        }
    }

    return flag;
}


status ListInsert(SqList &L, int i, ElemType e)
// 10如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    status flag;

    if(L.elem == NULL){
        flag = INFEASIBLE;  //L不存在
    }
    else{
        if(i<0 || i>L.length+1){    //非法插入
            flag = ERROR;
        }
        else{
            if(L.length >= L.listsize){ //空间不足，扩容
                L.elem = (ElemType*)realloc(L.elem ,sizeof(ElemType)*(L.listsize + LISTINCREMENT));
                L.listsize += LISTINCREMENT;
            }
			
			if(i == 0)	i = L.length+1; 
            for(int j=L.length; j>i-1; j--){  //第i个后的元素后移1位
                L.elem[j] = L.elem[j-1];
            }
            L.elem[i-1] = e;    //插入
            L.length++;
            flag = OK;
        }
    }
    return flag;
}



status ListDelete(SqList &L,int i,ElemType &e)
// 11如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem == NULL){
        return INFEASIBLE;  //L不存在
    }

    status flag;
    if(i<1 || i>L.length){  //非法删除
        flag = ERROR;
    }
    else{
        e = L.elem[i-1];
        int j;
        for(j=i-1; j<L.length-1; j++){
            L.elem[j] = L.elem[j+1];
        }
        L.length--;
        flag = OK;
    }

    return flag;
}


status ListTraverse(SqList L)
// 12如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem == NULL)
        return INFEASIBLE;
	if(L.length == 0)
		return ERROR;
		
	printf("\n----------- all elements -----------------------\n");
	for(int i=0; i<L.length; i++)
		printf("%d ",L.elem[i]);
	printf("\n------------------ end ------------------------\n");
    return OK;
}

int MaxSubArray(SqList L)
// 13初始条件是线性表L已存在且非空，找出一个具有最大和的连续子数组，返回该最大和 
{
	int sum_max = 0;
	int *T = (int*)malloc(sizeof(int)*L.length);
	T[0] = L.elem[0];
	for(int i=1; i<L.length; i++)	//计算前缀和 
		T[i] = T[i-1] + L.elem[i];
			
	for(int i=0; i<L.length; i++)	//遍历所有连续子数组 
	{
		if(T[i] > sum_max)	sum_max = T[i];
		for(int j=i+1; j<L.length; j++)
			if(T[j]-T[i] > sum_max)	
				sum_max = (T[j]-T[i]);
	}
	
	return sum_max; 
}

int SubArrayNum(SqList L, int k)
//14初始条件是线性表L已存在且非空, 操作结果是该数组中和为k的连续子数组的个数
{
	int cnt = 0;
	int *T = (int*)malloc(sizeof(int)*L.length);
	T[0] = L.elem[0];
	for(int i=1; i<L.length; i++)	//计算前缀和 
		T[i] = T[i-1] + L.elem[i];
			
	for(int i=0; i<L.length; i++)	//遍历所有连续子数组 
	{
		if(T[i] == k)	cnt++;
		for(int j=i+1; j<L.length; j++)
			if(T[j]-T[i] == k)	
				cnt++;
	}
		
	return cnt; 
}

status sortList(SqList &L)
//15初始条件是线性表L已存在；操作结果是将L由小到大排序；
{
	if(L.elem == NULL) return INFEASIBLE;
	
	int flag = 1;
	for(int i=0; flag && i<L.length-1; i++){
		flag = 0;
		for(int j=0; j+1<(L.length-i); j++)
			if(L.elem[j] > L.elem[j+1]){
				int t = L.elem[j];
				L.elem[j] = L.elem[j+1];
				L.elem[j+1] = t;
				flag = 1;
			}
	}
	return OK;
}

status  SaveList(SqList L, char FileName[])
// 16如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem == NULL)	return INFEASIBLE;
    FILE *fp;
    if((fp=fopen(FileName, "wb")) == NULL)
    	return ERROR;

	fwrite(&L.listsize, sizeof(int), 1, fp);	//写入数组大小 
	fwrite(&L.length, sizeof(int), 1, fp);	//写入长度 
    for(int i=0; i<L.length; i++)
        fwrite(L.elem+i, sizeof(ElemType), 1, fp);
    fclose(fp);
    return OK;
}

status  LoadList(SqList &L,char FileName[])
// 17如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if(L.length > 0)
        return INFEASIBLE;
        
    FILE *fp;
    if((fp=fopen(FileName, "rb")) == NULL)
    	return ERROR;

	fread(&L.listsize, sizeof(int), 1, fp);	//读入数组大小 
	fread(&L.length, sizeof(int), 1, fp);	//读入长度 
    if(L.elem == NULL)
		L.elem = (ElemType*)malloc(sizeof(ElemType)*L.listsize);
    for(int i=0; i<L.length; i++)
        fread(L.elem+i, sizeof(ElemType), 1, fp);
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 18只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    status flag = OK;
    int i = Lists.length;
    const int cntup = 10;
    int cnt = 0;
    while(((flag = InitList(Lists.elem[i].L)) != OK ) && cnt<cntup){
        Lists.elem[i].L.elem = NULL;
        cnt++;
    }
    if(flag == OK){
    	strcpy(Lists.elem[i].name, ListName);
   		Lists.length++;
	}
    return flag;
}

status RemoveList(LISTS &Lists,char ListName[])
// 19Lists中删除一个名称为ListName的线性表
{
    status flag = ERROR;

    for(int i=0; flag==ERROR && i<Lists.length; i++)
    {
        if(strcmp(Lists.elem[i].name,ListName) == 0)
        {
            for(; i<Lists.length-1; i++)
                Lists.elem[i] = Lists.elem[i+1];
            // flag = DestroyList(Lists.elem[i].L);
            flag = OK;
            Lists.length--;
        }
    }
    return flag;
}

status SwitchList(LISTS Lists, SqList &L, char ListName[])
// 20将当前线性表切换至ListName 
{
	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Lists.length; i++){
		if(strcmp(Lists.elem[i].name, ListName) == 0){
			flag = OK;
			L = Lists.elem[i].L;
		}
	}
	return flag;
}

status LocateList(LISTS Lists, char ListName[])
// 21查找ListName表的位置 
{
	status flag = INFEASIBLE;
	for(int i=0; flag==INFEASIBLE && i<Lists.length; i++){
		if(strcmp(Lists.elem[i].name, ListName) == 0){
			flag = i+1;
			break;
		}
	}
	return flag;
}

status ListsTraverse(LISTS Lists)
// 22遍历Lists, bw=1时遍历表的内容 
{
	if(Lists.length == 0)
		return ERROR;
	
	for(int i=0; i<Lists.length; i++){
		printf("%d\t%s", i+1, Lists.elem[i].name);
		printf("\n");
	}
	return OK;
}

status GetName(LISTS Lists, SqList L)
// 23当前表的名字 
{
	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Lists.length; i++){
		if(Lists.elem[i].L.elem == L.elem){
			flag = OK;
			printf("%s\n", Lists.elem[i].name);
		}
	}
	return flag;
}

status UploadList(LISTS &Lists, SqList L, char ListName[])
// 24把当前表添加到管理表
{
//	if(L.elem == NULL)
//		return INFEASIBLE; 
//	if(Lists.length+1 > Lists.listsize)
//		return ERROR;
//		
//	status flag = ERROR;
//	for(int i=0; flag==ERROR && i<Lists.length; i++){
//		if(Lists.elem[i].L.elem == L.elem){
//			return ERROR;
//		}
//	}
//	Lists.elem[Lists.length].L = L;
//	strcpy(Lists.elem[Lists.length].name, ListName);
//	Lists.length++;
//	return OK; 

	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Lists.length; i++){
		if(Lists.elem[i].L.elem == L.elem){
			Lists.elem[i].L = L;
			flag = OK;
		}
	}
	
	if(flag == ERROR){
		Lists.elem[Lists.length].L = L;
		strcpy(Lists.elem[Lists.length].name, ListName);
		Lists.length++;
		flag = OK;
	}
	
	return flag; 
}


