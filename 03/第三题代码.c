/*在球坐标系(rho,theta,phi)下产生球面上均匀分布的随机坐标点，给出
其直接抽样方法。*/

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
#define Pi 3.1415926

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


void phi_RandN(int seed, int N)	//产生N个随机数,并写入文件
{
	double M = M_16807;

	//迭代量为z
	int z = seed;
	int i = 0;

	FILE* fp = NULL; // 文件指针

	fp = fopen("phi.txt", "w");

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		fprintf(fp, "%f \n", (2*Pi*((float)z / M)));
	}

	fclose(fp);		//关闭打开的文件

}

void theta_RandN(int seed, int N)	//产生N个随机数,并写入文件
{
	double M = M_16807;

	//迭代量为z
	int z = seed;
	int i = 0;

	FILE* fp = NULL; // 文件指针

	fp = fopen("theta.txt", "w");

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		fprintf(fp, "%f \n", acos(1-2*((float)z / M)));
	}

	fclose(fp);		//关闭打开的文件

}


int main()	//主函数，用于调用函数功能
{
//		phi_RandN(Seed(), 50000);		//这个是为了生成phi的随机数
		theta_RandN(Seed(), 50000);		//这个是为了生成theta的随机数
		// 注意两个函数不要同时运行，否则得出来的结果是有关联的，不是一个随机分布的球

}