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


void Metropolis_Hasting_sampling(int seed,float alpha, float beta, float gamma) //进行Metropolis Hasting抽样，保存抽样结果到Metropolis_Hasting_sampling.txt，并且把最后的积分结果printf到屏幕上
{
    double M = M_16807;//参数
	//迭代量为z
	int z = seed;//定义种子值
	double rand_number = ((float)z / M);//定义随机数
    float x_prime = 0;//定义探索值
    int i = 0;//定义循环变量i
    float r = 0; //定义用来和随机变量比较的值

    //定义N次抽样点结果
    int N = 100000;
    float x[100000]={0};
    x[0]=1;
//    printf("This first term x0 is exactly %f",x[0]); //验证x0有没有被初始化为1

	FILE* fp = NULL; //文件指针
    fp = fopen("Metropolis_Hasting_sampling.txt", "a"); //打开文件
    fprintf(fp, "alpha=%f,beta=%f,gamma=%f\n", alpha,beta,gamma); //写入文件
    
    for ( i = 0; i < N-1; i++)
    {
        z = Schrage_int(z);
        rand_number = ((float)z / M);
        x_prime = (-1) *gamma * log(rand_number);
        r = pow((x_prime/x[i]),(alpha-1))*exp((x[i]-x_prime)/beta)*exp((x_prime-x[i])/gamma);
        if (rand_number < min(1,r))
        {
            x[i+1]=x_prime;
        }
        else
        {
            x[i+1]=x[i];
        }
    }

    //下面的代码干两件事：1.把数据写入txt文件；2.计算积分
    float integral = 0;
    
    for ( i = 0; i < N; i++)
    {
        fprintf(fp, "%f\n", x[i]); //写入文件
        integral += (x[i]-alpha*beta)*(x[i]-alpha*beta);
    }

    integral = integral / N;
    printf("The integral is %f\n",integral);

	fclose(fp);		//关闭打开的文件
    
}

void main()
{
    float alpha = 2, beta = 4;
    float gamma = 1;
    for ( gamma = 1; gamma <= 7; gamma=gamma+1)
    {
        Metropolis_Hasting_sampling(Seed(),alpha,beta,gamma); 
    }
}