#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>


#define M_16807 2147483647 
#define A_16807 16807	
#define R_16807 2836
#define Q_16807 127773
#define min(a,b) ( ((a)>(b)) ? (b):(a) ) //定义最小值比较

int Schrage_int(int seed)	//schrage方法，输入一个种子值，即可输出一个对应整数
{
	if (seed < 0)
	{
		return -1;	//错误返回-1
	}

	int z = A_16807 * (seed % Q_16807) - R_16807 * (seed / Q_16807);	//计算Shrage

	if (z < 0)		//判断正负,从而决定如何输出
	{
		return z + M_16807;
	}
	else
	{
		return z;
	}
}


int Seed()	//ͨ搞出来一个种子值
{
	time_t rawtime;
	int seed;
	struct tm* info;	//获取
	time(&rawtime);
	info = localtime(&rawtime);	//当地时间
	info->tm_year = info->tm_year % 100;

	seed = info->tm_year + 70 * (info->tm_min + 12 * (info->tm_mday\
		+ 31 * (info->tm_hour + 23 * (info->tm_min + 59 * (info->tm_sec)))));	//计算种子
    
    printf("The seed is %d\n",seed);
	return seed;
}


void Metropolis_Hasting_sampling(int seed,float alpha, float beta, float gamma) //进行Metropolis Hasting抽样，保存抽样结果到Results.txt，并且把最后的积分结果printf到屏幕上
{
    double M = M_16807;//参数
	//迭代量为z
	int z = seed;//定义种子值
	double rand_number = 0;//定义随机数
    float x_prime = 0;//定义探索值
    int i = 0;//定义循环变量i
    float r = 0; //定义用来和随机变量比较的值

    //定义N次抽样点结果
    int N = 100000;
    int right = 0;//为了计算抽样效率
    float total = 0;//定义x的求和
    float temp = 1; //定义每一次的迭代变量，初始值为1
    float efficient = 0;

	FILE* fp = NULL; //文件指针
    fp = fopen("Results.txt", "a"); //打开文件

    
    for ( i = 0; i < N; i++)
    {
        z = Schrage_int(z);
        rand_number = ((float)z / M);
        x_prime = (-1) *gamma * log(rand_number);
        r = pow((x_prime/temp),(alpha-1))*exp((temp-x_prime)/beta)*exp((x_prime-temp)/gamma);
//        printf("The x_prime is %f\n",x_prime);
        if (rand_number < min(1,r))
        {
            temp = x_prime;
            right += 1;
        }
        else
        {
            temp = temp;
        }
        total += temp;
//        printf("%f\n",temp);
    }
//    printf("Total is %f",total);
    //下面的代码干两件事：1.把数据写入txt文件；2.计算积分
    total = total / N;
    efficient = ((float)right/N);
    fprintf(fp, "%f %f %f\n",gamma,total,efficient); //写入文件

	fclose(fp);		//关闭打开的文件
    
}

void main()
{
    float alpha = 2, beta = 1;
    float gamma = 0.1;
    for ( gamma = 0.1; gamma <= 20; gamma=gamma+0.1)
    {
        Metropolis_Hasting_sampling(Seed(),alpha,beta,gamma); 
    }
}