#include "def.h"
#include "stu.h"
#define N 10005
#define tip "输入目标key："

//1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null

BiTree T = NULL;
TREES Trees;
TElemType definition[N];
char name[N];	//名字最长为N
int now = 0;

int main(void){
	menu();
	InitTrees(Trees);
	int op=1;
	while(op){
		status flag = INFEASIBLE;
		KeyType e = 0;	TElemType value;
		memset(name, 0, sizeof(name));
		printf("    请选择你的操作[0~24]: ");
		scanf("%d", &op);
		
	    switch(op){
			case 1:
				int i; i=0;
				if(T) printf("树已存在");
				else{
					printf("请输入带空树的前序遍历序列：\n");
					do{
						scanf("%d%s",&definition[i].key,definition[i].others);
					} while (definition[i++].key!=-1);
					judge( CreateBiTree(T, definition) );
				} 
				break;
			case 2:
				if(T) flag = DestroyBiTree(T);
				judge(flag);
				break;
			case 3:
				if(T) flag = ClearBiTree(T);
				judge(flag);
				break;
			case 4:
				flag = BiTreeEmpty(T);
				if(flag == TRUE)		printf("空！");
				else if(flag == FALSE)	printf("非空！");
				else printf("树不存在！"); 
				break;
			case 5:
				int t;
				t = BiTreeDepth(T);
				printf("树的深度为 %d", t);
				break;
			case 6:
				printf(tip);	scanf("%d", &e);
				BiTNode* obj;
				obj = LocateNode(T, e);
				if(obj){
					printf("值如下：\n");
					print(obj); 
				}
				else	printf("目标不存在！"); 
				break;
			case 7:
				printf(tip);	scanf("%d", &e);
				printf("新key："); scanf("%d", &value.key);
				printf("新others："); scanf("%s", value.others); 
				judge( Assign(T, e, value) );
				break;
			case 8:
				printf(tip);	scanf("%d", &e);
				BiTNode* brother;
				brother = GetSibling(T, e);
				if(brother == NULL)	printf("该元素不存在或无兄弟！");
				else {
					printf("兄弟值如下：\n");
					print(brother);
				}
				break;
			case 9:
				printf(tip);	scanf("%d", &e);
				int LR;
				printf("插入位置（0左 1右 -1根）："); 	scanf("%d", &LR); 
				printf("请输入要插入的节点值\n");
				printf("key："); scanf("%d",&value.key);
				printf("others："); scanf("%s", value.others); 
				flag = InsertNode(T, e, LR, value);
				judge(flag); 
				break;
			case 10:
				if(T){
					printf(tip); scanf("%d", &e); 
					flag = DeleteNode(T,e);
				}
				judge(flag);
				break;
			case 11:
				printf("先序遍历结果如下\n"); 
				flag = PreOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
			case 12:
				printf("中序遍历结果如下\n"); 
				flag = InOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
			case 13:
				printf("后序遍历结果如下\n"); 
				flag = PostOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
			case 14:
				printf("层序遍历结果如下\n"); 
				flag = LevelOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
				
	/*----------------------------附加题-----------------------------*/	
			case 15:
				int ans;
				ans = MaxPathSum(T);
				printf("最大路径和：%d", MaxPathSum(T));
				break;
			case 16:
				KeyType e1, e2;
				printf("输入两个目标key: \n");
				printf("key1："); scanf("%d", &e1);
				printf("key2："); scanf("%d", &e2);
				BiTNode* ancestor;
				ancestor = LowestCommonAncestor(T, e1,e2);
				printf("最近公共祖先值为：\n");
				print(ancestor);			 
				break;
			case 17:
				flag = InvertTree(T);
				judge(flag);
				break;
			
			case 18:
				printf("输入存储文件： ");
				scanf("%s", name); 
				flag = SaveBiTree(T, name);
				if(flag == OK)	printf("保存成功！");
				else if(flag == ERROR)	printf("保存失败！");
				else printf("Unknow Error!");
				break;
			case 19:
				printf("输入读取文件： ");
				scanf("%s", name);
				flag = LoadBiTree(T, name);
				if(flag == OK)	printf("读取成功！");
				else if(flag == ERROR)	printf("读取错误！（文件不存在）");
				else printf("Unknow Error!"); 
				break;
			
			case 20:
				printf("输入树名称： ");
				scanf("%s", name); 
				flag = SwitchTree(Trees, T, name);
				judge(flag);
				if(flag==OK) now = LocateBiTree(Trees, name);
				break;
			case 21:
				printf("输入新建的树名： ");
				scanf("%s", name);
				flag = AddBiTree(Trees, name);
				judge(flag); 
				break;
			case 22:
				printf("输入待删除的树名： ");
				scanf("%s", name);
				flag = RemoveBiTree(Trees, name);
				judge(flag); 
				break;
			
			case 23:
				printf("输入树名称： ");
				scanf("%s", name); 
				flag = LocateBiTree(Trees, name);
				if(flag == INFEASIBLE)	printf("不存在!\n");
				else	printf("%s 的位置是 %d\n", name, flag);
				break;
			case 24:
				printf("输入树名称： ");
				scanf("%s", name); 
				flag = Upload(Trees, T, name);
				if(flag == OK) printf("更新成功");
				else if(flag == ERROR) printf("新增成功"); 
				break;
			case 0:
				printf("欢迎下次再使用本系统！");
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
	
	
}//end of main()


