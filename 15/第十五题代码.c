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


void Metropolis_xy(int seed,float sigma_x, float sigma_y, float step_length, float beta) //进行Metropolis抽样，保存抽样结果到"x.txt"和"y.txt"
{
    double M = M_16807;//参数
	//迭代量为z
	int z = seed;//定义种子值
	double rand_number = 0;//定义随机数
    float try = 0;//定义探索值
    int i = 0;//定义循环变量i

    //定义N次抽样点结果
    int N = 1000;
    int right_x = 0;
    int right_y = 0;
    float total = 0;//定义x的求和
    float temp_x = 1; //定义每一次的迭代变量x，初始值为1
    float temp_y = 1;  //定义每一次的迭代变量y，初始值为1


	FILE* fpx = NULL; //文件指针
    fpx = fopen("x.txt", "w"); //打开文件
    FILE* fpy = NULL; //文件指针
    fpy = fopen("y.txt", "w"); //打开文件

    for ( i = 0; i < N; i++)
    {
        //对x抽样
        z = Schrage_int(z);
        rand_number = ((float)z / M); 
        try = (rand_number-0.5)*step_length + temp_x;
        z = Schrage_int(z); //再生成一个随机数
        rand_number = ((float)z / M); 
        if (rand_number < (exp(beta/2/sigma_x/sigma_x*(temp_x*temp_x-try*try))))
        {
            temp_x = try;
            right_x += 1;
        }
        else
        {
            temp_x = temp_x;
        }
        fprintf(fpx, "%f\n",temp_x); //写入文件

        //对y抽样
        z = Schrage_int(z);
        rand_number = ((float)z / M); 
        try = (rand_number-0.5)*step_length + temp_y;
        z = Schrage_int(z); //再生成一个随机数
        rand_number = ((float)z / M); 
        if (rand_number < (exp(beta/2/sigma_y/sigma_y*(temp_y*temp_y-try*try))))
        {
            temp_y = try;
            right_y += 1;
        }
        else
        {
            temp_y = temp_y;
        }
        fprintf(fpy, "%f\n",temp_y); //写入文件

    }

	fclose(fpx);		//关闭打开的文件
    fclose(fpy);
    printf("The efficient for x is %f\n",(float)right_x/N);
    printf("The efficient for y is %f",(float)right_y/N);
    
}

int main(int argc, char const *argv[])
{
    Metropolis_xy(Seed(), 1, 1, 2,  1);
    return 0;
}
