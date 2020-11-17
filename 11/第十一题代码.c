#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


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
    
    printf("The seed is %d\n",seed);
	return seed;
}



float d1(int seed, int N)	//计算1维行走自回归分布，返回值是几率
{
	double M = M_16807;
    //每个点用这么多次取平均
    int n = 100000;
	//迭代量为z
	int z = seed;
	int i = 0,j = 0;
	double rand_number = ((float)z/M);

    int total=0;    //用来记录返回原点的个数
    for (j = 0; j < n; j++)     //随机行走模拟
    {
        int a = 0;//定义随机行走变量
        for ( i = 0; i < N; i++)
        {
            z = Schrage_int(z);
            rand_number = ((float)z/M);
            if (rand_number<=0.5)
            {
                a += 1;
            }
            else
            {
                a -= 1;
            }    
        }
        if (a == 0)
        {
            total += 1;
        }
    }
    return ((float)total/n);
}



float d2(int seed, int N)	//计算2维行走自回归分布，返回值是几率
{
	double M = M_16807;
    //每个点用这么多次取平均
    int n = 100000;
	//迭代量为z
	int z = seed;
	int i = 0,j = 0;
	double rand_number = ((float)z/M);

    int total=0;    //用来记录返回原点的个数
    for (j = 0; j < n; j++)     //随机行走模拟
    {
        int a = 0,b = 0;//定义随机行走变量
        for ( i = 0; i < N; i++)
        {
            z = Schrage_int(z);
            rand_number = ((float)z/M);
            switch (((int)(rand_number*4)))
            {
            case 0:
                a += 1;
                break;
            case 1:
                a -= 1;
                break;
            case 2:
                b += 1;
                break;
            case 3:
                b -= 1;
                break;
            default:
                break;
            }
        }
        if (a == 0 && b == 0)
        {
            total += 1;
        }
    }
    return ((float)total/n);
}

double d3(int seed, int N)	//计算3维行走自回归分布，返回值是几率
{
	double M = M_16807;
    //每个点用这么多次取平均
    int n = 100000;
	//迭代量为z
	int z = seed;
	int i = 0,j = 0;
	double rand_number = ((float)z/M);

    int total=0;    //用来记录返回原点的个数
    for (j = 0; j < n; j++)     //随机行走模拟
    {
        int a = 0,b = 0, c = 0;//定义随机行走变量
        for ( i = 0; i < N; i++)
        {
            z = Schrage_int(z);
            rand_number = ((float)z/M);
            switch (((int)(rand_number*6)))
            {
            case 0:
                a += 1;
                break;
            case 1:
                a -= 1;
                break;
            case 2:
                b += 1;
                break;
            case 3:
                b -= 1;
                break;
            case 4:
                c += 1;
                break;
            case 5:
                c -= 1;
                break;
            default:
                break;
            }
        }
        if (a == 0 && b == 0 && c == 0)
        {
            total += 1;
        }
    }
    return ((float)total/n);
}

int main()
{
    int N = 0;
    N = 5000;    //产生50000个数据
    FILE* fp = NULL; //文件指针
	fp = fopen("1d_RW_return.txt", "w"); //打开文件
//	fp = fopen("2d_RW_return.txt", "w"); //打开文件
//	fp = fopen("3d_RW_return.txt", "w"); //打开文件

    for (int k = 0; k <= N; k=k+50)
    {
        fprintf(fp,"%d\t%f\n",k,d1(Seed(),k));
//        fprintf(fp,"%d\t%f\n",k,d2(Seed(),k));
//        fprintf(fp,"%d\t%lf\n",k,d3(Seed(),k));
    }
    
	fclose(fp);		//关闭打开的文件
}