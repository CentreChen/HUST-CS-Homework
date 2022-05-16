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
#define MAX_VERTEX_NUM 20  
#endif


#ifndef _ELEM_
#define _ELEM_ 
typedef int status;  
typedef int KeyType;   
typedef enum {DG,DN,UDG,UDN} GraphKind;  
typedef struct {  
	KeyType  key;  
	char others[20];  
} VertexType; //顶点类型定义
#endif


#ifndef _GRAPH_
#define _GRAPH_
typedef struct ArcNode {         //表结点类型定义  
    int adjvex;              //顶点位置编号   
    struct ArcNode  *nextarc;       //下一个表结点指针  
} ArcNode;  

typedef struct VNode{                //头结点及其数组类型定义  
    VertexType data;           //顶点信息  
    ArcNode *firstarc;           //指向第一条弧  
} VNode,AdjList[MAX_VERTEX_NUM];  

typedef  struct ALGraph{  //邻接表的类型定义  
    AdjList vertices;          //头结点数组  
    int vexnum,arcnum;         //顶点数、弧数  
    GraphKind  kind;        //图的类型  
} ALGraph;
#endif


#ifndef _GRAPHS_
#define _GRAPHS_
#define GRAPHS_INIT_SIZE 20
typedef struct GsNode{
	struct{
		char name[30];
		ALGraph G;	
	}elem[GRAPHS_INIT_SIZE];
	int length;
	int listsize;
}ALGraphs; 
#endif



#endif
