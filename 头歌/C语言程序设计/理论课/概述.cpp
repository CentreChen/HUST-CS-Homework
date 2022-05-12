//第1关 累加求和
#include<stdio.h>
int main()
{
	/**********  Begin  **********/
    int n,a,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		ans+=i;
	}
	printf("%d\n",ans);
    
	/**********  Begin  **********/
    return 0;
}


//第2关 正数和与平均值
#include<stdio.h>
int main()
{
	/**********  Begin  **********/
    int n=0,a,sum=0;
	double ave=0.0;
	for(int i=1;i<=10;i++){
		scanf("%d",&a);
		if(a>0){
			sum+=a;
			n++;
		}	
	}
	ave+=sum;
	if(n!=0)	ave=ave/n;
	printf("累加和:%d\n",sum);
	printf("平均值:%.1lf\n",ave);
	/**********  End  **********/
    return 0;
} 
