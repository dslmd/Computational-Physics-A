#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>


#define M_16807 2147483647 
#define A_16807 16807	
#define R_16807 2836
#define Q_16807 127773



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



void direction_sampling(int seed)	//抽出小角度近似的取向随机行走，并记录theta和phi值，存储到"phi.txt"和"theta.txt"这两个文件里。
{
	double M = M_16807;

	double theta[10][1000] = {0},phi[10][1000]={0}; //定义抽出来的theta和phi

	//随机数迭代量为z
	int z = seed;
	int i = 0,j = 0;//定义求和标志量
	double rand_number = 0;
	FILE* fp_phi = NULL; //文件指针
	FILE* fp_theta = NULL; //文件指针

	fp_phi = fopen("phi.txt", "w"); //打开文件
	fp_theta = fopen("theta.txt", "w"); //打开文件
	
	for (int i = 0; i < 10; i++)
	{
		double a = 0, b = 0; //作为横坐标和纵坐标
		for (int j = 0; j < 1000; j++)
		{
			z = Schrage_int(z);
			rand_number = ((float)z / M);
			printf("%f\n",rand_number);
			if (rand_number>=0 && rand_number<=0.25)
			{
				a += 0.0001;
			}
			else if (rand_number>0.25 && rand_number<=0.5)
			{
				a -= 0.0001;
			}
			else if (rand_number>0.5 && rand_number<=0.75)
			{
				b += 0.0001;
			}
			else if (rand_number>0.75 && rand_number<=1.0)
			{
				b -= 0.0001;
			}

			//theta如下
			theta[i][j]=sqrt(a*a+b*b);
			//下面把phi搞出来
			if (b>0.0)
			{
				phi[i][j]=acos(a/sqrt(a*a+b*b));
			}
			else if (b==0.0 && a>=0.0)
			{
				phi[i][j]=0;
			}
			else if (b==0.0 && a<0.0)
			{
				phi[i][j]=3.1415926;
			}
			else if (b<0.0)
			{
				phi[i][j]=-1*acos(a/sqrt(a*a+b*b));
			}
			fprintf(fp_theta, "%lf\n", theta[i][j]); //写入文件
			fprintf(fp_phi, "%lf\n", phi[i][j]); //写入文件
		}
		
	}
	//现在得到了10次，每次1000步的取向模拟的结果，关闭文件

	fclose(fp_theta);		//关闭打开的文件
	fclose(fp_phi);		//关闭打开的文件
}



void main()
{
    direction_sampling(Seed());
}