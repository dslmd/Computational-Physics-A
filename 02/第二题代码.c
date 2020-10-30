/* 用16807产生器测试随机数序列中满足关系 x_n-1 < x_n < x_n+1
的比重。讨论Fibonacci延迟产生器中出现这种关系的比重。*/
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


void Write_RandN(int seed, int N)	//产生N个随机数,并写入文件，这里仅仅是为了代码完整性搬运过来
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
		fprintf(fp, "%f \n", ((float)z / M));
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





double Schrage_16807_ratio(long int N)		 //产生N个随机数，并且计算满足题意的比例，然后把这个比例返回
{
	double M = M_16807;
	int z = Seed();
	int i = 0;
	float temp[10] = { 0 };
	long int number=0;  //用于计满足题目的个数

	for (i = 0; i < N + 10; i++)
	{
		z = Schrage_int(z);
		for (int tm = 9; tm > 0; tm--)
		{
			temp[tm] = temp[tm - 1];
		}
		temp[0] = ((float)z / M);

		if (i > 9)
		{
			if (temp[0]<temp[1] && temp[1]<temp[2])
			{
				number++;
			}
		}

	}

		return ((float)number / N);
}



double lagged_fib_generater_ratio(int N, int p, int q)	//通过Fibonacci延迟产生器来产生随机数，并在子程序中直接算出题中要求的ratio

{
	int z = Seed();//迭代量
	//先产生50个In
	int In[50] = { 0 };
	int number = 0;//用于记录满足的个数
	for (int i = 0; i < 50; i++)
	{
		z = Schrage_int(z);
		In[i] = z;
	}
	

	for (int i = 0; i < N; i++)
	{
		int I = In[49-p]-In[49-q];	//计算fib

		if (I < 0)		//判断正负,从而决定如何输出
		{
			I = I + 4294967290;
		}
		
		for (int k = 49; k > 0; k--)
		{
			In[k] = In[k - 1];
		}

		In[0] = I;

		if (In[0]<In[1] && In[1]<In[2])
		{
			number++;
		}


	}
	return ((float)number / N);

}






void print_16807_ratio()	//这个是为了生成满足题意的比例, 然后print
{
	printf("For 16807 random number generator: \n");
	long int N = 10;
	double d = 0, r = 0;
	for (N = 10; N < 1000000000; N = N * 10)
	{
		r = Schrage_16807_ratio(N);
		d = r - 1.0 / 6;
		printf(" When N is %ld, the ratio is %f, the deviation with 1/6 is %f\n", N, r, d);
	}
}


void print_fib_ratio()	//这个是为了生成Fibonacci产生器，以及带载减法产生器的随机数，并计算满足题意的比例, 然后print
{
	printf("For 带载减法产生器[p,q]=[22,43]: \n");
	long int N = 10;
	double d = 0, r = 0;
	for (N = 10; N < 1000000000; N = N * 10)
	{
		r = lagged_fib_generater_ratio(N, 22, 43);
		d = r - 1.0 / 6;
		printf(" When N is %ld, the ratio is %f, the deviation with 1/6 is %f\n", N, r, d);
	}
	
	printf("For fib random number generator with [p,q]=[2,10]: \n");
	for (N = 10; N < 1000000000; N = N * 10)
	{
		r = lagged_fib_generater_ratio(N, 2, 10);
		d = r - 1.0 / 6;
		printf(" When N is %ld, the ratio is %f, the deviation with 1/6 is %f\n", N, r, d);
	}

}


int main()	//主函数，用于调用函数功能
{
	//	Write_RandN(Seed(), 1000);		//这个是为了生成数据，生成完之后就不用啦
		print_16807_ratio();
		print_fib_ratio();
}