/* 用Schrage方法编写随机数子程序，用连续两个随机数作为点的坐标值
绘出若干点的平面分布图。再用<xk>测试均匀性（取不同量级的N值，讨论
偏差与N的关系）、C(l) 测试其2维独立性（总点数N > 107）。*/
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
#define FILE_NAME "data.txt" 

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


void Write_RandN(int seed, int N)	//产生N个随机数,并写入文件
{
	double M = M_16807;

	//迭代量为z
	int z = seed;
	int i = 0;

	FILE* fp = NULL; // 文件指针

	fp = fopen("data.txt", "w");

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		fprintf(fp,"%f \n", ((float)z/M));
	}

	fclose(fp);		//关闭打开的文件

}

int Seed()	//通过现在时间计算种子值
{
	time_t rawtime;
	int seed;
	struct tm* info;	//获取
	time(&rawtime);
	info = localtime(&rawtime);	//转化为当前时区的时间
	info->tm_year = info->tm_year % 100;

	seed = info->tm_year + 70 * (info->tm_min + 12 * (info->tm_mday\
		+ 31 * (info->tm_hour + 23 * (info->tm_min + 59 * (info->tm_sec)))));	//计算种子
	return seed;
}



double Aver_RandN(int seed, int N, int k)	//产生N个随机数,并计算x^k平均值
{
	double M = M_16807;

	//迭代量为z
	int z = seed;
	int i = 0;
	float total = 0;
	float aver = 0;
	float temp = 0;

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		temp = ((float)z / M);
		temp = pow(temp, k);
		total += temp;
	}

	aver = total / N;

	return aver;
}


double CL(int l, int N)		 //产生N个随机数，并且用于计算C(L)
{
	double M = M_16807;
	int z = Seed();
	int i = 0;
	float total_linear = 0, total_squa = 0, total_dev = 0; //linear, squa, dev分别代表线性和，平方和，差l的和
	float aver_linear = 0, aver_squa = 0, aver_dev = 0;		//linear, squa, dev分别代表线性平均，平方平均，差l的平均
	float temp[10] = {0};
	double CL = 0;

	for (i = 0; i < N+10; i++)
	{
		z = Schrage_int(z);
		for (int tm = 9; tm > 0; tm--)
		{
			temp[tm] = temp[tm - 1];
		}
		temp[0] = ((float)z / M);

		if (i > 9)
		{
			total_linear += temp[0];
			total_squa += temp[0]*temp[0];
			total_dev += temp[0] * temp[l];
		}
		
	}

	aver_linear = total_linear / N;
	aver_squa = total_squa / N;
	aver_dev = total_dev / N;

	CL = (aver_dev - pow(aver_linear,2)) / (aver_squa - pow(aver_linear,2));

	return CL;
}



int main()	//主函数，用于调用函数功能
{
//	Write_RandN(Seed(), 10000000);		//这个是为了生成数据，生成完之后就不用啦

//	下面是用x^k测试均匀性
/*	long int N = 0;
	for (N = 100; N < 10000000; N=N*10)
	{
		for (int k = 2; k < 8; k=k+2)
		{
			printf("When k is %d, N is %d, the average is %f \n",k,N, Aver_RandN(Seed(), N, k));
		}
	}*/

	long int N = 10000000;
	for (int l = 1; l < 8; l++)
	{
		printf("When l = %d, the C(L) is %f \n", l, CL(l, N));
	}
}