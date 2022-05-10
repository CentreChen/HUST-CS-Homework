
//第1关 Hello,World!
#include<stdio.h>
int main()
{
    /**********Begin**********/
    printf("Hello,World!\n");
    return 0;








	/**********End**********/
    return 0;
}



//第2关 两数之和
#include<stdio.h>
int main()
{
    /**********Begin**********/
    int a,b,ans;
    scanf("%d %d",&a,&b);
    ans=a+b;
    printf("%d",ans);







	/**********End**********/
    return 0;
}



//第3关 人机问候
#include<stdio.h>
int main()
{
    /**********Begin**********/
    char name[128];
    scanf("%s",&name);
    printf("Hello %s!\n",name);







	/**********End**********/
    return 0;
}


//第4关 整数的个位数字
#include<stdio.h>
int main()
{
    /**********Begin**********/
    int a;
    scanf("%d",&a);
    a%=10;
    printf("%d",a);





	/**********End**********/
    return 0;
}

