#include "def.h"
void menu(void)
{
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1.  InitList		13. MaxSubArray\n");
	printf("    	  2.  DestroyList	14. SubArrayNum\n");
	printf("    	  3.  ClearList		15. sortList \n");
	printf("    	  4.  ListEmpty		16. SaveList\n");
	printf("    	  5.  ListLength	17. LoadList\n");
	printf("    	  6.  GetElem		18. AddList\n");
	printf("    	  7.  LocateElem	19. RemoveList\n");
	printf("    	  8.  PriorElem		20. SwitchList\n");
	printf("    	  9.  NextElem		21. LocateList\n");
	printf("    	  10. ListInsert	22. ListsTraverse\n");
	printf("    	  11. ListDelete	23. GetName\n");
	printf("    	  12. ListTrabverse	24. UploadList\n");
	printf("    	  0.  Exit		999. menu\n");
	printf("-------------------------------------------------\n");
}

void judge(int flag)
{
	switch(flag){
		case OK:
			printf("操作成功！\n");
			break;
		case ERROR:
			printf("非法参数！（目标不存在）\n");
			break;
		case INFEASIBLE:
			printf("表不存在！\n");
			break; 
		default:
		 	printf("UNKNOWN WRONG!\n");
		 	break;
	}
}

void InitLists(LISTS &Lists)
{
	Lists.length = 0;
	Lists.listsize = LISTS_INIT_SIZE;
}
