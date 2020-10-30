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

//定义全局变量
int x[114]={0}, y[114]={0};
float p[114]={0};
float f[114]={0};

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
	return seed;
}

void intergral_cal_1(int seed,long int N)	//用产生的随机数计算第一个定积分
{
	double M = M_16807;
	//迭代量为z
	long int z = seed;
	long int i = 0;
	double rand_number = 0;
	double x = 0; //定义积分自变量
	double y = 0; //定义积分因变量
	double total = 0; //总量
	double aver = 0; //最后的平均值
	double intergral = 0; // 积分值

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		x = 2 * rand_number;
		y = sqrt(x+sqrt(x));
		total = total + y;
	}

	aver = total /N;
	intergral = aver * 2;

	printf("For N = %d of the first integral, the value is %f \n",N,intergral);
}


void intergral_cal_2(int seed, int N)	//用产生的随机数计算第2个定积分
{
	double M = M_16807;
	//迭代量为z
	int z = seed;
	int i = 0;
	double rand_number = 0;
	double x[5] = {0}; //定义积分自变量
	double y = 0; //定义积分因变量
	double total = 0; //总量
	double aver = 0; //最后的平均值
	double intergral = 0; // 积分值

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		x[0]=0.9*rand_number;
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		x[1]=0.8*rand_number;
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		x[2]=0.9*rand_number;
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		x[3]=2*rand_number;
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		x[4]=1.3*rand_number;

		
		y = 6-x[0]*x[0]-x[1]*x[1]-x[2]*x[2]-x[3]*x[3]-x[4]*x[4];

		total = total + y;
	}

	aver = total/N;
	intergral = aver*0.9*0.8*0.9*2*1.3;

	printf("For N = %d of the second integral, the value is %f \n",N,intergral);
}

void main(){
	for (int N = 100; N < 1000000000; N=N*10)
	{
		intergral_cal_1(Seed(), N);
		intergral_cal_2(Seed(), N);
	}
	
}