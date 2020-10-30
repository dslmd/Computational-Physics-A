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


void read_data() //创建一个用来读取data.txt文件中的数据(注意，开头已被删除)
{
	FILE* fp = fopen("data.txt", "r");
	int i = 0;
	while (fscanf(fp,"%d %d\n",x+i,y+i)!=EOF)
	{
		i++;
//		printf("%d %d\n",x[i-1],y[i-1]);	//测试有没有完成数据读取
	}
//	经测试，已完成数据读取，下面开始对y求和
	int sum = 0;
	for (int i = 0; i < 114; i++)
	{
		sum += y[i];
	}
//	printf("%d",sum); //测试sum对不对
//	经测试sum为396002，接下来对y进行归一化，然后给p
	for (int i = 0; i < 114; i++)
	{
		p[i]=(float)y[i]/sum;
//		printf("%f\n",p[i]);	//测试是否成功归一化
	}
//接下来计算F函数
	float sum_i = 0;	//求到i的和
	for (int i = 0; i < 114; i++)
	{
		sum_i += p[i];
		f[i] = sum_i;
	}
//	printf("%f",f[110]);	//测试f是否成功搞成累计函数
//	经测试，成功，该函数把全局变量f[114]搞成了累计函数
	fclose(fp); //关闭打开的文件
}


void direct_sampling(int seed, int N)	//直接抽样N次并存到抽样结果"direct_sampling.txt"
{
	double M = M_16807;
	int sampling_number[114] = {0};		//定义抽样出来的频数，写入文件

	//迭代量为z
	int z = seed;
	int i = 0;
	double rand_number = 0;

	FILE* fp = NULL; //文件指针

	fp = fopen("direct_sampling.txt", "w");

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		rand_number = ((float)z / M);
		for (int j = 0; j < 113; j++)	//查看随机数所在的区间，并分成两种情况讨论
		{
			if ( (rand_number >= f[j]) && (rand_number < f[j+1]) )
			{
				sampling_number[j+1]++;
			}
		}
		if (rand_number < f[0])
		{
//				printf("%f",rand_number);	//测试输出是否正确
				sampling_number[0]++;
		}
	}
	//最终输出的sampling_number[i]是直接抽样N次后x[i]的频数
	
	//下面以老师给的源文件格式，把直接抽样结果写入文件
	for (int i = 0; i < 114; i++)
	{
		fprintf(fp, "%d %d\n", x[i], sampling_number[i]);
	}
	fclose(fp);		//关闭打开的文件
}

void shexuan_sampling(int seed, int N)	//直接抽样N次并存到抽样结果"shexuan_sampling.txt"
{
	double M = M_16807;
	int sampling_number[114] = {0};		//定义抽样出来的频数，写入文件

	//迭代量为z
	int z = seed;
	int i = 0;
	double rand_number[2] = {0};

	FILE* fp = NULL; //文件指针

	fp = fopen("shexuan_sampling.txt", "w");

	int total = 0;

	for (i = 0; i < N; )
	{
		z = Schrage_int(z);
		rand_number[0] = ((float)z / M)*114+2900;	//这是随机数x
		z = Schrage_int(z);
		rand_number[1] = ((float)z / M);	//这是随机数p(x)
		//限制抽样范围
		if ((rand_number[0]<2990)&&(rand_number[1]>5673.0/396002))
		{
			continue;		//不符合就重新产生
		}
		if ((rand_number[0]>2990)&&(rand_number[1]>38000.0/396002))
		{
			continue;		//不符合就重新产生
		}
		//符合条件就继续
		total++;
		for (int j = 0; j < 113; j++)	//查看随机数所在的区间，并分成两种情况讨论
		{
			if ( (rand_number[0] >= x[j]) && (rand_number[0] < x[j+1]) )
			{
				if (rand_number[1] < p[j])
				{
					sampling_number[j]++;
					i++;
				}
				
			}
		}
		if (rand_number[0] >= x[113])
		{
				if (rand_number[1] < p[113])
				{
					sampling_number[113]++;
					i++;
				}
		}

	}
	//最终输出的sampling_number[i]是直接抽样N次后x[i]的频数
	printf("\nTotally the random number generator run %d times, the efficient is %f\n",total,(float)N/total);
	//下面以老师给的源文件格式，把直接抽样结果写入文件
	for (int i = 0; i < 114; i++)
	{
		fprintf(fp, "%d %d\n", x[i], sampling_number[i]);
	}
	fclose(fp);		//关闭打开的文件
}



void main() {
	read_data();
	direct_sampling(Seed(), 396002);	//按照原文件的总数抽样
	shexuan_sampling(Seed(), 396002);	//按照原文件的总数抽样
}