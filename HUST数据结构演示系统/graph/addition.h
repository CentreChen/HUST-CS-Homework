#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "stu.h"
#define N 10005
#define tip "请输入目标key："
#define g(t) (G.vertices[t].data) 


void menu(void)
{
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-----------------------------------------------------\n");
	printf("	1. CreateCraph \t\t13. VerticesSetLessThanK\n");
	printf("	2. DestroyGraph\t\t14. ShortestPathLength\n");
	printf("	3. LocateVex	\t15. ConnectedComponentsNums \n");
	printf("	4. PutVex 	\t16. SaveGraph\n");
	printf("	5. FirstAdjVex	\t17. LoadGraph\n");
	printf("	6. NextAdjVex   \t18. AddGraph\n");
	printf("	7. InsertVex	\t19. RemoveGraph\n");
	printf("	8. DeleteVex	\t20. SwitchGraph\n");
	printf("	9. InsertArc	\t21. LocateGraph\n");
	printf("	10.DeleteArc	\t22. Upload\n");
	printf("	11.DFSTraverse\t\n");
	printf("	12.BFSTraverse\t\n");
	printf("	0.  Exit	    \t999. menu\n");
	printf("-----------------------------------------------------\n");
}


void judge(int flag)
{
	switch(flag)
	{
		case OK:
			printf("操作成功！");
			break;
		case ERROR:
			printf("操作失败！（key重复，目标不存在等）");
			break; 
		case INFEASIBLE:
			printf("图不存在！");
			break;
		default:
			printf("未知错误！");
			break;
	}
}
//
//void INIT(ALGraphs &Gs){
//	
//	
//	Gs.elem[0].G = (ALGraph*)malloc(sizeof(ALGraph));
//	strcpy(Gs.elem[0].name, "origin");
//	Gs.length++; 
//}


void print(VertexType data)
{
	printf("key = %d    others = %s\n", data.key, data.others);
}

void option_Graph(ALGraphs &Gs)
{
	menu();
	char name[N];	//名字最长为N
	Gs.listsize = GRAPHS_INIT_SIZE;
	Gs.length = 0;
	AddGraph(Gs, "origin");
	ALGraph G = Gs.elem[0].G;
	
	int op=1;
	while(op){
		status flag = INFEASIBLE;
		memset(name, 0, sizeof(name));
		KeyType e = -1;
		int t = -1;
		
		printf("    请选择你的操作[0~24]: ");
		scanf("%d", &op);
	    switch(op){
			case 1:{
				printf("请输入顶点、弧的数据：\n") ;
				VertexType V[30];
				KeyType VR[100][2];
				int i = 0;
				do {
				    scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i = 0;
				do {
				    scanf("%d%d",&VR[i][0],&VR[i][1]);
				} while(VR[i++][0]!=-1);
				flag = CreateCraph(G, V, VR);
				judge(flag);
				break;
			}
			
			case 2:
				flag = DestroyGraph(G);
				judge(flag);
				break;
			
			case 3:
				printf(tip);	scanf("%d", &e);
				t = LocateVex(G, e);
				if(t != -1){
					printf("位序为：%d\n", t);
					print(g(t)); 
				}
				else printf("目标不存在！"); 
				break;
			
			
			case 4:{
				VertexType value; 
				printf(tip);	scanf("%d", &e);
				printf("新key："); scanf("%d", &value.key);
				printf("新others："); scanf("%s", value.others); 
				flag = PutVex(G, e, value);
				judge(flag);
				break;
			}
			
			case 5:
				printf(tip);	scanf("%d", &e);
				t = FirstAdjVex(G, e);
				if(t == -1)	printf("目标顶点不存在或无第一邻接点！");
				else {
					printf("第一邻接点位序：%d\n", t);
					print(g(t));
				}
				break;
			

			case 6:{
				printf(tip);	scanf("%d", &e);
				KeyType w;
				printf("输入相对顶点："); scanf("%d", &w); 
				t = NextAdjVex(G, e, w);
				if(t == -1)	printf("目标顶点不存在或无下一邻接点！");
				else {
					printf("下一邻接点位序：%d\n", t);
					print(g(t));
				}
				break;
			}
				
			case 7:{
				VertexType v;
				printf(tip); scanf("%d", &v.key);
				printf("输入others："); scanf("%s", v.others); 
				flag = InsertVex(G,v);
				judge(flag);
				break;
			}
				
			case 8:
				printf(tip); scanf("%d", &e);
				flag = DeleteVex(G,e);
				judge(flag);
				break;
			
			
			case 9:{
				KeyType v,w;
				printf("输入弧的一端："); scanf("%d", &v);
				printf("输入弧另一端："); scanf("%d", &w); 
				flag = InsertArc(G,v, w);
				judge(flag);
				break;
			}
			
			case 10:{
				KeyType v,w;
				printf("输入弧的一端："); scanf("%d", &v);
				printf("输入弧另一端："); scanf("%d", &w); 
				flag = DeleteArc(G,v, w);
				judge(flag);
				break;
			}
			
			case 11:
				printf("深度优先搜索遍历结果如下：\n"); 
				flag = DFSTraverse(G, visit);
				judge(flag);
				break;
			case 12:
				printf("广度优先搜索遍历结果如下：\n"); 
				flag = BFSTraverse(G, visit);
				judge(flag);
				break;
				
	/*----------------------------附加题-----------------------------*/	
			
			case 13:{
				printf(tip); scanf("%d", &e);
				printf("输入距离上限："); scanf("%d", &t);
				int *ans = VerticesSetLessThanK(G, e, t);
				if(ans == NULL) printf("目标不存在");
				else if(ans[1] == -1) printf("无距离小于k的点");
				else{
					int i;
					for(i=1; ans[i]!=-1; i++)
						print(g(ans[i]));
					printf("一共有 %d 个点", i-1);
					free(ans);
				}
				break;
			}
		
			case 14:{
				KeyType v, w;
				printf("key1："); scanf("%d", &v); 
				printf("key2："); scanf("%d", &w);
				int dis = ShortestPathLength(G, v, w);
				if(dis == -1)
					printf("v或w不存在，或无路径！"); 
				else
					printf("最短路径的长度是 %d", dis);
				break;
			}
			
			
			case 15:
				t = ConnectedComponentsNums(G);
				printf("连通分量的个数是 %d", t); 
				break;
			
			case 16:
				printf("输入存储文件： ");
				scanf("%s", name); 
				flag = SaveGraph(G, name);
				if(flag == OK)	printf("保存成功！");
				else if(flag == ERROR)	printf("保存失败！");
				else printf("UNKNOWN ERROR!");
				break;
			case 17:
				printf("输入读取文件： ");
				scanf("%s", name);
				flag = LoadGraph(G, name);
				if(flag == OK)	printf("读取成功！");
				else if(flag == ERROR)	printf("读取错误！（文件不存在等）");
				else printf("UNKNOWN ERROR!"); 
				break;
			
			
			case 18:{
				printf("输入新建图名：");
				scanf("%s", name);
				flag = AddGraph(Gs, name);
				judge(flag);
				break;
			}
			
			case 19:{
				printf("输入删除图名：");
				scanf("%s", name);
				flag = RemoveGraph(Gs, name);
				judge(flag);
				break;
			}
			
			case 20:{
				printf("输入切换图名：");
				scanf("%s", name);
				flag = SwitchGraph(Gs, name, G);
				judge(flag);
				break;
			}
			
			case 21:{
				printf("输入查找图名：");
				scanf("%s", name);
				t = LocateGraph(Gs, name);
				if(t == -1) printf("未找到");
				else printf("图 %s 的序号为 %d", name, t+1); //从1开始 
				break;
			}
			
			case 22:{
				printf("输入上传图名：");
				scanf("%s", name);
				flag = Upload(Gs, name, G);
				judge(flag);
				break;
			} 


			case 0:
				printf("欢迎下次再使用本系统！");
				break;
			case 999:
				menu();
				break;	
			default:	//未定义指令，刷新系统界面 
				system("cls");
				menu();
				break;
		}//end of switch
		printf("\n\n");
	}//end of while
}

