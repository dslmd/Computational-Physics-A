/* ：对于球面上均匀分布的随机坐标点，给出它们在（x, y）平面上投影的几
率分布函数。并由此验证Marsaglia抽样方法确为球面上均匀分布的随机抽样。*/

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

void Sphere_RandN_Marsaglia_xy(int seed, int N)	//产生N个球表面的，并将其xy值写入文件
{
	double M = M_16807;
	double uv_list[2] = { 0 }; //创建uv值，uv_list[0]是u, uv_list[1]是v
	double x = 0, y = 0, z = 0;
	//迭代量为z
	int s = seed;
	int i = 0;

	//文件指针
	FILE* fp_x = NULL;
	FILE* fp_y = NULL;
	FILE* fp_z = NULL;


	fp_x = fopen("x.txt", "w");
	fp_y = fopen("y.txt", "w");
	fp_z = fopen("z.txt", "w");

	for (i = 0; i < N; )
	{
		uv_list[0] = Schrage_int(s);
		uv_list[1] = Schrage_int(uv_list[0]);
		s = Schrage_int(uv_list[1]);

		//把Schrage_int变成随机数
		uv_list[0] = ((float)uv_list[0] / M);
		uv_list[1] = ((float)uv_list[1] / M);

		//把uv变成[-1,1]区间均匀
		uv_list[0] = 2 * uv_list[0] - 1;
		uv_list[1] = 2 * uv_list[1] - 1;

		if ((uv_list[0]*uv_list[0]+uv_list[1]*uv_list[1])<=1)
		{
			x = 2 * uv_list[0] * sqrt(1 - (uv_list[0] * uv_list[0] + uv_list[1] * uv_list[1]));
			y = 2 * uv_list[1] * sqrt(1 - (uv_list[0] * uv_list[0] + uv_list[1] * uv_list[1]));
			z = 1 - 2 * (uv_list[0] * uv_list[0] + uv_list[1] * uv_list[1]);
			fprintf(fp_x, "%f \n", x);
			fprintf(fp_y, "%f \n", y);
			fprintf(fp_z, "%f \n", z);
			i++;
		}

	}

	fclose(fp_x);		//关闭打开的文件
	fclose(fp_y);		//关闭打开的文件
	fclose(fp_z);
}



int main()	//主函数，用于调用函数功能
{
		Sphere_RandN_Marsaglia_xy(Seed(), 10000);		//这个是为了生成xy数据
}