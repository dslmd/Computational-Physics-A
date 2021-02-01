#include<iostream>
#include <time.h>

//经典的16807随机数产生器
#define M_16807 2147483647 
#define A_16807 16807	
#define R_16807 2836
#define Q_16807 127773

using namespace std;


int Schrage_int(int seed)	//定义Schrage迭代产生随机数的方法，输入一个种子值，即可输出一个对应整数
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

void DampingField()  //计算量子蒙卡结果的函数
{
    //波函数是|phi>=|n0>
    int n0 = 100;
 
    int n = 0;  //定义迭代量n
    float Gamma = 0.005;  //哈密顿量非厄密部分的耗散速率
    float delta_t = 0.1;    //每一步之间的时间间隔
    int M = 10000;   //单个粒子Monte Carlo进行的步数，此处固定为10000
    int K = 1000;   //总共模拟的粒子数
    int z = Seed();  //种子值
    float N[10000] = {0}; //用来记录各个时刻腔内的光子数


    //下面定义非厄密演化的耗散概率delta_p，和随机数，以及演化过程中的归一化因子
    float delta_p = 0;
    float rand = ((float)z / M_16807);  //使用Schrage随机数产生器来产生随机数


    for (int j = 0; j < K; j++) //这个循环是对K个粒子取平均（这一步先求和，下面再除N）
    {
        n = n0; //将迭代量初始化
        N[0] += n;  //让数组记录下初始的N值

        for (int i = 1; i < M; i++) //这个循环是对单个粒子进行M步的Monte Carlo行走
        {

            z = Schrage_int(z);
            rand = ((float)z / M_16807);    //产生随机数
            delta_p = Gamma * delta_t * n;  //计算delta_p
            if (delta_p < rand) //进行条件判断，如果成立，就进行幺正演化，如果不成立，就会有耗散项
            {
                n = n;
            }
            else
            {
                n = n - 1;
            }
            if ( n < 0 ) //这一项保证腔内光子数只能为正
            {
                n = 0;
            }
            N[i] += n;
        }
    }

    for (int i = 0; i < M; i++) //对K个M步粒子取平均
    {
        N[i] = ((float)N[i]/K);
    }
    

    //到此为止，N[i]这个数组，就是各阶段腔内光子数分布了，接下来我们把它写入文件    
	FILE* fp = NULL; //文件指针
    fp = fopen("Results.txt", "w"); //打开文件
    for (int i = 0; i < M; i++)
    {
        fprintf(fp,"%f\n",N[i]);
    }
    fclose(fp); //关闭文件
}

int main()
{
    DampingField();  //调用TwoLevelSys函数
}