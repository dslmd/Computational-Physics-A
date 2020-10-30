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



void p1_sampling(int seed, int N)	//舍选抽样第一个分布N次,并存到抽样结果， 这里的N是总抽样次数
{
	double M = M_16807;
	int s1[10] = {0};		//定义抽样出来的频数，写入文件
    int s2[10] = {0};
	//迭代量为z
	int z = seed;
	int i = 0;
	double rand_number = 0;
    double x=0,y=0;
    double horizontal = 0;
    int total = 0; //定义取平均的个数
	FILE* fp = NULL; //文件指针


//下面是分别按照N=2、5、10（N在此函数里是total）抽样的代码

    total = 2;      //求total次数的平均
	fp = fopen("p1_2.txt", "w"); //打开文件
    for (int n = 0; n < N; n++)
    {
        x = 0;
        y = 0;
        horizontal = 0;         //用来储存横坐标平均值
        for (int i = 0; i < total; ) //用循环求total次数的平均
        {
            z = Schrage_int(z);
            x = ((float)z / M);
            z = Schrage_int(z);
            y = ((float)z / M);
            x = 2*x-1;
            y = y*3/4;
            if (y<=((1-x*x)*3/4))
            {
                horizontal += x;
                i++;
            }
        }
        horizontal = horizontal / total;
        fprintf(fp, "%f\n", horizontal); //写入文件
    }
	fclose(fp);		//关闭打开的文件




    total = 5;      //求total次数的平均
	fp = fopen("p1_5.txt", "w"); //打开文件
    for (int n = 0; n < N; n++)
    {
        x = 0;
        y = 0;
        horizontal = 0;         //用来储存横坐标平均值
        for (int i = 0; i < total; ) //用循环求total次数的平均
        {
            z = Schrage_int(z);
            x = ((float)z / M);
            z = Schrage_int(z);
            y = ((float)z / M);
            x = 2*x-1;
            y = y*3/4;
            if (y<=((1-x*x)*3/4)) 
            {
                horizontal += x;
                i++;
            }
        }
        horizontal = horizontal / total;
        fprintf(fp, "%f\n", horizontal); //写入文件
    }
	fclose(fp);		//关闭打开的文件



    total = 10;      //求total次数的平均
	fp = fopen("p1_10.txt", "w"); //打开文件
    for (int n = 0; n < N; n++)
    {
        x = 0;
        y = 0;
        horizontal = 0;         //用来储存横坐标平均值
        for (int i = 0; i < total; ) //用循环求total次数的平均
        {
            z = Schrage_int(z);
            x = ((float)z / M);
            z = Schrage_int(z);
            y = ((float)z / M);
            x = 2*x-1;
            y = y*3/4;
            if (y<=((1-x*x)*3/4)) 
            {
                horizontal += x;
                i++;
            }
        }
        horizontal = horizontal / total;
        fprintf(fp, "%f\n", horizontal); //写入文件
    }
	fclose(fp);		//关闭打开的文件
}


void p2_sampling(int seed, int N)	//舍选抽样第一个分布N次,并存到抽样结果， 这里的N是总抽样次数
{
	double M = M_16807;
	int s1[10] = {0};		//定义抽样出来的频数，写入文件
    int s2[10] = {0};
	//迭代量为z
	int z = seed;
	int i = 0;
	double rand_number = 0;
    double x=0,y=0;
    double horizontal = 0;
    int total = 0; //定义取平均的个数
	FILE* fp = NULL; //文件指针


//下面是分别按照N=2、5、10（N在此函数里是total）抽样的代码

    total = 2;      //求total次数的平均
	fp = fopen("p2_2.txt", "w"); //打开文件
    for (int n = 0; n < N; n++)
    {
        x = 0;
        y = 0;
        horizontal = 0;         //用来储存横坐标平均值
        for (int i = 0; i < total; ) //用循环求total次数的平均
        {
            z = Schrage_int(z);
            x = ((float)z / M);
            z = Schrage_int(z);
            y = ((float)z / M);
            x = 2*x-1;
            y = y*3/4;
            if (y<=(sqrt(1-abs(x))*3/4)) 
            {
                horizontal += x;
                i++;
            }
        }
        horizontal = horizontal / total;
        fprintf(fp, "%f\n", horizontal); //写入文件
    }
	fclose(fp);		//关闭打开的文件




    total = 5;      //求total次数的平均
	fp = fopen("p2_5.txt", "w"); //打开文件
    for (int n = 0; n < N; n++)
    {
        x = 0;
        y = 0;
        horizontal = 0;         //用来储存横坐标平均值
        for (int i = 0; i < total; ) //用循环求total次数的平均
        {
            z = Schrage_int(z);
            x = ((float)z / M);
            z = Schrage_int(z);
            y = ((float)z / M);
            x = 2*x-1;
            y = y*3/4;
            if (y<=(sqrt(1-abs(x))*3/4)) 
            {
                horizontal += x;
                i++;
            }
        }
        horizontal = horizontal / total;
        fprintf(fp, "%f\n", horizontal); //写入文件
    }
	fclose(fp);		//关闭打开的文件



    total = 10;      //求total次数的平均
	fp = fopen("p2_10.txt", "w"); //打开文件
    for (int n = 0; n < N; n++)
    {
        x = 0;
        y = 0;
        horizontal = 0;         //用来储存横坐标平均值
        for (int i = 0; i < total; ) //用循环求total次数的平均
        {
            z = Schrage_int(z);
            x = ((float)z / M);
            z = Schrage_int(z);
            y = ((float)z / M);
            x = 2*x-1;
            y = y*3/4;
            if (y<=(sqrt(1-abs(x))*3/4)) 
            {
                horizontal += x;
                i++;
            }
        }
        horizontal = horizontal / total;
        fprintf(fp, "%f\n", horizontal); //写入文件
    }
	fclose(fp);		//关闭打开的文件
}


void main()
{
    int N = 0;
//    N = 10000;    //产生10000个数据
    N = 50000;    //产生50000个数据
    p1_sampling(Seed(), N);
    p2_sampling(Seed(), N);
}