//第1关 两整数高低字节组合成一个新整数
   (k&0xFF00)>>8|(p<<8);


//第2关 将整数向右循环移动n位
 /********** 使用int变量x,n，在下面写出满足任务要求的表达式**********/
 /**********Begin**********/
 {
  unsigned int MASK=0xffffffff,mask1,mask2;
	mask1= MASK >> n;
	mask2= ~mask1;
	x= (x>> n & mask1) | ( x<< (32-n) & mask2);
 }
 /**********End**********/
 
 
 //第3关 翻转指定范围内的二进制位
  /********** 使用int变量x,p和n，在下面写出满足任务要求的表达式**********/
 /**********Begin**********/
{
    unsigned MASK=0xffffffff, mask;
	
	mask=( (MASK>> (p-n+1)) << (32-n)) >> (31-p);
	x ^= mask;
}
 /**********End**********/
 
 
 //第4关 求三个数中最大值
  /**********使用int变量a, b, c，在下面写出满足任务要求的表达式**********/
 /**********Begin**********/
{
    (a>b) ? (a>c ? a : c) : (b>c ? b : c);
}
 /**********End**********/
 
 
//第5关 被3整除且个位数字为5
 /**********使用unsigned int变量a，在下面写出满足任务要求的表达式**********/
 /**********Begin**********/
{
    (a%3) ? 0 : ( (a%10 == 5) ? 1 : 0);
}
 /**********End**********/
 
 
 //第6关 输出对应年份的各月名称及天数
 #include <stdio.h>

int main() {
	/**********Begin**********/
	int n;
	scanf("%d",&n);
	printf("Jan: 31\n");
	if(n%400==0 || (n%4==0 && n%100)){
		printf("Feb: 29\n");
	}
	else printf("Feb: 28\n");
	printf("Mar: 31\n");
	printf("Apr: 30\n");
	printf("May: 31\n");
	printf("Jun: 30\n");
	printf("Jul: 31\n");
	printf("Aug: 31\n");
	printf("Sep: 30\n");
	printf("Oct: 31\n");
	printf("Nov: 30\n");
	printf("Dec: 31");


	/**********End**********/
	return 0;
}
