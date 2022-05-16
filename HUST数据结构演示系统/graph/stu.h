#include <string.h>
#include <stdlib.h>
#include "def.h"
#define maxleng 1005
#include <stdio.h> 
#define debug printf("Debug\n");


int LocateVex(ALGraph G,KeyType u)
//3根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    int flag = -1;
	for(int i=0; flag==-1 && i<G.vexnum; i++){
		if(G.vertices[i].data.key == u)
			flag = i;
	}
	return flag;
}


status InsertVex(ALGraph &G,VertexType v)
//7在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    status flag = ERROR; 
	if(LocateVex(G,v.key) == -1){	//防止 key 重复 
		if(G.vexnum+1 <= MAX_VERTEX_NUM){	//防止顶点数溢出 
			int i = G.vexnum;
			G.vertices[i].data = v;
			G.vertices[i].firstarc = NULL;
			G.vexnum++;
			flag = OK; 
		}
	}
	return flag;
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//9在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
	status flag = ERROR;
	
	int iv = LocateVex(G, v);
	int iw = LocateVex(G, w);
	if(iv!=-1 && iw!=-1){
		flag = OK;
		ArcNode* p = G.vertices[iv].firstarc;
		while(flag==OK && p){
			if(p->adjvex == iw)
				flag = ERROR;
			p = p->nextarc;
		} 
		
		if(flag == OK){
			ArcNode* s1 = (ArcNode*)malloc(sizeof(ArcNode));
			s1->adjvex = iv;	s1->nextarc = NULL; 
			ArcNode* s2 = (ArcNode*)malloc(sizeof(ArcNode));
			s2->adjvex = iw;	s1->nextarc = NULL;
			
			if(iw != iv){
				s1->nextarc =  G.vertices[iw].firstarc;
				G.vertices[iw].firstarc = s1;
				s2->nextarc =  G.vertices[iv].firstarc;
				G.vertices[iv].firstarc = s2;
			}
			else{	//loop
				s1->nextarc =  G.vertices[iw].firstarc;
				G.vertices[iw].firstarc = s1;
				free(s2);	//释放多余空间 
			}
			G.arcnum++;	
		}
	}

	return flag;
}	


status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*1根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    status flag = OK;
	G.kind = UDG;	//初始化 
	G.vexnum = G.arcnum = 0;
    bool bw[maxleng];
    memset(bw, 0, sizeof(bw));
    
	int i = 0;
    while(flag==OK && V[i].key != -1){	//检测顶点 key（要求不重复且不溢出） 
    	if(bw[V[i].key] || i>=MAX_VERTEX_NUM)
			flag = ERROR;
		else bw[V[i].key] = 1;
		i++;
	}
	
	i = 0;
	while(flag==OK && VR[i][0] != -1){	//检测弧 key（要求顶点存在） 
		if(!bw[VR[i][0]] || !bw[VR[i][1]])
			flag = ERROR;
		i++;
	}
    
    if(flag == OK){
    	i = 0;
    	while(flag==OK && V[i].key != -1)	//建立顶点 
			flag = InsertVex(G, V[i++]); 
		if(G.vexnum == 0) flag = ERROR;	//无顶点 
		
		i = 0;
		while(flag==OK && VR[i][0] != -1){	//建立弧 
			flag = InsertArc(G, VR[i][0], VR[i][1]); 
			i++;
		}
	}
	return flag;
}

status DestroyGraph(ALGraph &G)
/*2销毁无向图G,删除G的全部顶点和边*/
{
	for(int i=0; i<G.vexnum; i++){
		ArcNode* p = G.vertices[i].firstarc;
		G.vertices[i].firstarc = NULL;
		while(p){
			ArcNode* t = p;
			p = p->nextarc;
			free(t);
		}
	}
	
	G.vexnum = 0;
	G.arcnum = 0;
	return OK;
}


status PutVex(ALGraph &G,KeyType u,VertexType value)
//4根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
	status flag = ERROR;
	if(LocateVex(G,value.key)==-1 || u==value.key){
		int i = LocateVex(G, u); 
		if(i != -1){
			G.vertices[i].data = value;
			flag = OK;			
		}
	}
	return flag;
}


int FirstAdjVex(ALGraph G,KeyType u)
//5根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
	int i = LocateVex(G, u);
	if(i != -1)
		return G.vertices[i].firstarc->adjvex;
	else
		return -1;
}



int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//6根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
	int ans = -1;	bool flag = 0;	 
	int i = LocateVex(G, v);
	if(i != -1){
		ArcNode* p = G.vertices[i].firstarc;
		while(!flag && p){	//查找 w 
			if(G.vertices[p->adjvex].data.key == w){
				flag = 1;
				if(p = p->nextarc)
					ans = p->adjvex;
			}
			else p = p->nextarc;
		}
	}
	
	return ans;
}


status Delete(ALGraph &G, int iu,int iv){	//删除 iu 中的 iv 
	status flag = ERROR;
	ArcNode* p = G.vertices[iu].firstarc;
	if(p && p->adjvex==iv){
		G.vertices[iu].firstarc = p->nextarc;
		free(p);
		flag = OK;
	}
	else if(p){
		while(flag==ERROR && p->nextarc){
			if(p->nextarc->adjvex == iv){
				ArcNode* t = p->nextarc;
				p->nextarc = p->nextarc->nextarc;
				free(t);
				flag = OK;
			}
			else p = p->nextarc;
		}		
	}
	return flag;
} 

status DeleteVex(ALGraph &G,KeyType v)
//8在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
	status flag = ERROR;
	
	int iv = LocateVex(G, v);
	if(iv != -1 && G.vexnum>1){
		ArcNode* p = G.vertices[iv].firstarc;
		while(p){
			Delete(G, p->adjvex, iv);	//删另一个顶点上的弧 
			
			ArcNode* t = p;		//删弧 
			p = p->nextarc;
			free(t); 
			G.arcnum--;
		}
		
		for(int i=iv; i<G.vexnum-1; i++)	//删顶点 
			G.vertices[i] = G.vertices[i+1];
		G.vexnum--;
		
		for(int i=0; i<G.vexnum; i++){	//重构下标 
			p = G.vertices[i].firstarc;
			while(p){
				if(p->adjvex > iv)
					p->adjvex--;
				p = p->nextarc;
			}
		}
		flag = OK;
	}
	
	return flag;
}




status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//10在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    status flag = ERROR;
    
    int iv = LocateVex(G, v);
    int iw = LocateVex(G, w);
	if(iv!=-1 && iw!=-1){
		ArcNode* p = G.vertices[iv].firstarc;
		int flag1 = Delete(G, iv, iw);
		int flag2 = Delete(G, iw, iv);
		if(flag1 && flag2){
			G.arcnum--;
			flag = OK;	
		} 
	
	} 
	return flag;
}



bool visited[maxleng];
void visit(VertexType v)
{
    printf(" %d %s\n",v.key,v.others);
}

void DFS(ALGraph G, void (*visit)(VertexType), int i)
{
	visit(G.vertices[i].data); 
	visited[i] = 1;
	ArcNode* p = G.vertices[i].firstarc;
	while(p){
		if(!visited[p->adjvex])
			DFS(G,visit,p->adjvex);
		p = p->nextarc;
	}
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//11对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	if(G.vexnum == 0) return ERROR;
	
	printf("-------------------------------------\n");
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<G.vexnum; i++){
		if(!visited[i]) DFS(G,visit,i);
	}
	printf("-------------------------------------\n");
	return OK;
}


status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//12对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	if(G.vexnum == 0) return ERROR;
	
	printf("-------------------------------------\n");
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<G.vexnum; i++){
		int Q[maxleng];
		memset(Q, -1, sizeof(Q));
		int head=0, tail=0;
		if(!visited[i]){
			visit(G.vertices[i].data);
			visited[i] = 1;
			Q[tail++] = i;
			
			while(head < tail){
				int t = Q[head++];
				ArcNode* p = G.vertices[t].firstarc;
				while(p){	//遍历相邻点 
					if(!visited[p->adjvex]){
						int iv = p->adjvex;
						visit(G.vertices[iv].data);
						visited[iv] = 1;
						Q[tail++] = iv;
						
					}
					p = p->nextarc; 
				}//遍历相邻点完毕 
			}	
		}//end of bfs
	}
	printf("-------------------------------------\n");
	return OK;
}

int* VerticesSetLessThanK(ALGraph G, KeyType v, int k)
//13初始条件是图G存在；操作结果是返回与顶点v距离小于k的顶点集合；
{
	int i = LocateVex(G, v);
	if(i == -1){	//目标不存在 
		return NULL; 
	}
	
	memset(visited, 0, sizeof(visited));
	int* Q = (int*)malloc(sizeof(int)*maxleng); //用动态数组存储
	memset(Q, -1, sizeof(Q));
	int head=0, tail=0;
	
//	visit(G.vertices[i].data);
	visited[i] = 1;
	Q[tail++] = i;
	
	int dis = 0;
	while(++dis<k && head<tail){
		int t = Q[head++];
		ArcNode* p = G.vertices[t].firstarc;
		while(p){	//遍历相邻点 
			if(!visited[p->adjvex]){
				int iv = p->adjvex;
//				visit(G.vertices[iv].data);
				visited[iv] = 1;
				Q[tail++] = iv;
			}
			p = p->nextarc; 
		}//遍历相邻点完毕 
	}
	Q[tail] = -1;	
	return Q;	//返回集合包含自身 
}


int ShortestPathLength(ALGraph G, KeyType v, KeyType w)
//14初始条件是图G存在；操作结果是返回顶点v与顶点w的最短路径的长度；
{
	int ans = -1;
	
	int iv = LocateVex(G,v);
	int iw = LocateVex(G,w);
	
	if(iv!=-1 && iw!=-1){
		if(iv == iw) ans = 0;
		else{
			memset(visited, 0, sizeof(visited));
			int* Q = (int*)malloc(sizeof(int)*maxleng);
			memset(Q, -1, sizeof(Q));
			int head=0, tail=0;
			
			visited[iv] = 1;
			Q[tail++] = iv;
					
			int dis = 0;
			while(ans==-1 && head<tail){
				++dis;
				int t = Q[head++];
				ArcNode* p = G.vertices[t].firstarc;
				while(p){	//遍历相邻点 
					if(p->adjvex == iw){
						ans = dis;
						break;
					}
					if(!visited[p->adjvex]){
						int iv = p->adjvex;
						visited[iv] = 1;
						Q[tail++] = iv;
					}
					p = p->nextarc; 
				}//遍历相邻点完毕 
			}
			free(Q);
		}
	}
	return ans;
}


int ConnectedComponentsNums(ALGraph G)
//15初始条件是图G存在；操作结果是返回图G的所有连通分量的个数； 
{
	int ans = 0;
	
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<G.vexnum; i++){
		int Q[maxleng];
		memset(Q, -1, sizeof(Q));
		int head=0, tail=0;
		if(!visited[i]){
			visited[i] = 1;
			Q[tail++] = i;
			
			while(head < tail){
				int t = Q[head++];
				ArcNode* p = G.vertices[t].firstarc;
				while(p){	//遍历相邻点 
					if(!visited[p->adjvex]){
						int iv = p->adjvex;
						visited[iv] = 1;
						Q[tail++] = iv;
						
					}
					p = p->nextarc; 
				}//遍历相邻点完毕 
			}	
			ans++; 
		}//end of bfs
	}
	
	return ans;
}


status SaveGraph(ALGraph G, char FileName[])
//16将图的数据写入到文件FileName中
{
	FILE* fp;
	fp = fopen(FileName, "wb");
	if(fp == NULL){
		printf("file not found\n");
		return ERROR;
	}
	
	fwrite(&G.vexnum, sizeof(int), 1, fp);
	fwrite(&G.arcnum, sizeof(int), 1, fp);
	fwrite(&G.kind, sizeof(int), 1, fp);
	
	int end = -1;
	for(int i=0; i<G.vexnum; i++){
		fwrite(&G.vertices[i].data, sizeof(VertexType), 1, fp);
		
		ArcNode* p = G.vertices[i].firstarc;
		while(p){
			fwrite(&p->adjvex, sizeof(int), 1, fp);
			p = p->nextarc;
		}
		fwrite(&end, sizeof(int), 1, fp);		
	}
	
	fclose(fp);
	return OK;
}
status LoadGraph(ALGraph &G, char FileName[])
//17读入文件FileName的图数据，创建图的邻接表
{
	FILE* fp;
	fp = fopen(FileName, "rb");
	if(fp == NULL){
		printf("file not found\n");
		return ERROR;
	}

	fread(&G.vexnum, sizeof(int), 1, fp);
	fread(&G.arcnum, sizeof(int), 1, fp);
	fread(&G.kind, sizeof(int), 1, fp);
	
	int t = 0;
	for(int i=0; i<G.vexnum; i++){
		ArcNode* tail = (ArcNode*)malloc(sizeof(ArcNode));	//临时创建空的头结点，方便尾插 
		tail->nextarc = NULL; 
		fread(&G.vertices[i].data, sizeof(VertexType), 1, fp);
		G.vertices[i].firstarc = tail;
		
		do{
			fread(&t, sizeof(int), 1, fp);
			if(t != -1){
				ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex = t;
				p->nextarc = NULL;				
				
				tail->nextarc = p;
				tail = p;
			}
		}while(t != -1);
		
		tail = G.vertices[i].firstarc;
		G.vertices[i].firstarc = tail->nextarc;
		free(tail);	//释放头结点 
	}
	fclose(fp);
	return OK;
}


status AddGraph(ALGraphs &Gs, char name[])
//18图的添加
{
	ALGraph *pG = (ALGraph*)malloc(sizeof(ALGraph));
	pG->vexnum = 0;
	pG->arcnum = 0;
	pG->kind = UDG;
	
	Gs.elem[Gs.length].G.vexnum = 0;
	Gs.elem[Gs.length].G.arcnum = 0;
	Gs.elem[Gs.length].G.kind = UDG;
	
	strcpy(Gs.elem[Gs.length].name, name);
	Gs.length++;
	
	return OK;
}

status RemoveGraph(ALGraphs &Gs, char name[])
//19图的移除 
{
	status flag = ERROR;
	
	for(int i=0; flag==ERROR && i<Gs.length; i++)
	{
		if(strcmp(Gs.elem[i].name,name)==0){
			DestroyGraph(Gs.elem[i].G);
			for(int j=i; j<Gs.length-1; j++)
				Gs.elem[j] = Gs.elem[j+1];
			Gs.length--;
			flag = OK; 
		}	
	}
	
	return flag;
}

status SwitchGraph(ALGraphs Gs, char name[], ALGraph &G)
//20 图的切换 
{
	status flag = ERROR;
	
	for(int i=0; flag==ERROR && i<Gs.length; i++)
	{
		if(strcmp(Gs.elem[i].name,name)==0){
			G = Gs.elem[i].G;
			flag = OK; 
		}	
	}
	
	return flag;
}

int LocateGraph(ALGraphs Gs, char name[])
//21图的查找 
{
	int ans = -1;
	for(int i=0; ans==-1 && i<Gs.length; i++)
		if(strcmp(Gs.elem[i].name,name)==0)
			ans = i;
	return ans;
	
}

status Upload(ALGraphs &Gs, char name[], ALGraph &G)
{
	int i = LocateGraph(Gs, name);
	if(i != -1){
		printf("更新……"); 
		Gs.elem[i].G = G;
	}
	else{
		printf("添加……"); 
		AddGraph(Gs, name);
		Gs.elem[Gs.length-1].G = G;
	}
	return OK;
}
