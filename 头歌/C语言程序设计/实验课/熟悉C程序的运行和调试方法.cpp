//第1关 完全平方数
#include<math.h>  /* 数学函数库的头文件 */
#include<stdio.h>

int main()
{
	long x,y;
	for(int i=1;i<100000;i++) 
	{
	    x=sqrt(i+100);   /* sqrt是求平方根的函数 */ 
		y=sqrt(i+268);
		if((x*x==i+100) && (y*y==i+268))
			printf("\n%d",i);
	}
	return 0;
}


//第2关 字符数和行数
 #include<stdio.h>
int main(void)
{
    char c, numchar, numline;
    numchar = 0;
    numline = 0;
   // printf("输入若干行文本，行首输入Ctrl+z结束。\n");
    while((c = getchar()) != EOF){
        numchar++;
        if(c == '\n')
            numline++;
    }
    printf("字符数:%d,", numchar);
    printf("行数:%d", numline);
    return 0;
}


//第3关 第几天
#include<stdio.h>
int main()
{
    int day,month,year,sum=0,leap=0;
	int mdays[12]={0,31,28,31,30,31,30,31,31,30,31,30};

		scanf("%d%d%d",&year,&month,&day);

		if( year%400==0 || (year%4==0 && year%100!=0))
			if( month > 2 )
				leap=1;

		for(int i=1; i<month; i++)
			sum+=mdays[i];

		sum+=day;
		sum+=leap;
		
		printf("It is the %dth day.", sum);
		return 0;
}



//第4关 完数
#include<stdio.h>

int IF(int x){
	
	int t,sum=0;
	
	t = x/2;
	while(t){
		if( !(x % t) )
			sum+=t;
		t--;
	}
	if(sum == x)	return 1;
	return 0;
}

int main()
{
	
    for(int i=1; i <= 1000; i++)
        if(IF(i))
            printf("%d\n", i);
    return 0;
}


//第5关 最大的数字
 #include<stdio.h>
 int main()
 {
     int count, max, x, t;
   
     scanf("%d", &x);
     count = max = 0;
     while(x)
     {
         t = x % 10;
         if(t == 0)
            count++;
         if(t > max)
            max = t;
         x = x/10;
     }
     printf("该数有%d个零,最大数字是%d\n", count, max);
     return 0;
 }


 //第6关 反转字符串
 #include<stdio.h>

int strLength(char s[])
{
	int i=0;
	while(s[i++]);
	i--;
	return i; 	
}

void strReverse(char s[])
{
	int i=0, j=strLength(s)-1;
	for(; i<j; i++,j--)  /* 从两头遍历s */
	{
	    char t;
		t=s[i]; 
	    s[i]=s[j]; 
	    s[j]=t; 
    }
}

int main() 
{
	char s[1000];
	scanf("%s",s);
	printf("串%s的长度为:%d\n",s,strLength(s));
	strReverse(s);  
	printf("反转后:%s",s);
	return 0;
}

