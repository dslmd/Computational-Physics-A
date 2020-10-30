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

void Lorentzian_selected_Guassian_RandN(int seed, int N)	//用Lorentz型选出N个Gauss型的随机数,并写入文件
{
	double M = M_16807;
	double uv_list[2] = { 0 }; //创建uv值，uv_list[0]是u, uv_list[1]是v
	double x = 0, y = 0, z = 0;
	//迭代量为z
	int s = seed;
	int i = 0;
	int count = 0;// 用来记一共有多少次，便于计算效率

	//文件指针
	FILE* fp_x = NULL;


	fp_x = fopen("Lorentzian.txt", "w");

	for (i = 0; i < N; )
	{
		uv_list[0] = Schrage_int(s);
		uv_list[1] = Schrage_int(uv_list[0]);
		s = Schrage_int(uv_list[1]);

		//把Schrage_int变成随机数
		uv_list[0] = ((float)uv_list[0] / M);
		uv_list[1] = ((float)uv_list[1] / M);

		//把x变成[-1,1]区间均匀
		x = 2 * uv_list[0] - 1;
		//把y变成[0,1.3]均匀
		y = 1.3 * uv_list[1];


		if (y <= 1.213 / (1 + x * x * x * x))
		{
			count++;

			if (y <= exp(-0.5 * x * x))
			{
				fprintf(fp_x, "%f \n", x);
				i++;
			}

		}

	}
	printf("The efficiency of the selection is %f \n", (float)N / count);
	fclose(fp_x);		//关闭打开的文件
}












int main()
{
	Lorentzian_selected_Guassian_RandN(Seed(), 50000);
}