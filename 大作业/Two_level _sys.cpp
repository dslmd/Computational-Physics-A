#include<iostream>
#include<complex>
#include<complex.h>
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

void TwoLevelSys()  //计算量子蒙卡结果的函数
{
    //波函数是|phi>=a|down>+b|up>
    float a0 = 0;   //下态的初始系数
    float b0 = 1;   //上态的初始系数
    complex<double> Omega = 5; //哈密顿量的厄密部分的演化速率
    complex<double> Gamma = 0.2;  //哈密顿量非厄密部分的耗散速率
    complex<double> delta_t = 0.03;    //每一步之间的时间间隔
    int M = 1000;   //单个粒子Monte Carlo进行的步数，此处固定为1000
    int N = 1000;   //总共模拟的粒子数
    int z = Seed();  //种子值

    //下面定义用于MC过程中判断的迭代量：前一次at1，bt1；后一次at2，bt2
    complex<double> at1(0,0);
    complex<double> at2(0,0);
    complex<double> bt1(0,0);
    complex<double> bt2(0,0);
    complex<double> img(0,1);   //定义单位虚数，便于后续计算

    //下面定义Monte Carlo方法下单个粒子的系数演化数组，每一步都被记录在了数组的每个元素里
    complex<double> at[1000]={0};
    complex<double> bt[1000]={0};

    //定义概率Pa=|a^2|，Pb=|b^2|，这个是我们最关心的
    float Pa[1000]={0};
    float Pb[1000]={0};

    //下面定义非厄密演化的耗散概率delta_p，和随机数，以及演化过程中的归一化因子
    complex<double> delta_p = 0;
    complex<double> rand = ((float)z / M_16807);  //使用Schrage随机数产生器来产生随机数
    complex<double> normfactor = 0;


    for (int j = 0; j < N; j++) //这个循环是对N个粒子取平均（这一步先求和，下面再除N）
    {
        at[0] += a0;
        bt[0] += b0;
        at1 = a0;
        bt1 = b0;
        for (int i = 1; i < M; i++) //这个循环是对单个粒子进行M步的Monte Carlo行走
        {
            z = Schrage_int(z);
            rand = ((float)z / M_16807);    //产生随机数
            delta_p = Gamma * delta_t * bt1 * bt1;  //计算delta_p
            if (real(delta_p) < real(rand)) //进行条件判断，如果成立，就进行幺正演化，如果不成立，就会有耗散项
            {
                at2 = at1 - bt1 * img * Omega * delta_t;
                bt2 = bt1 * (1.0 - Gamma*delta_t) - at1 * img * Omega * delta_t;
                normfactor = sqrt(abs(at2)*abs(at2)+abs(bt2)*abs(bt2));
                at2 = at2 / normfactor;
                bt2 = bt2 / normfactor;
            }
            else
            {
                at2 = 1;
                bt2 = 0;
            }
            at[i] += at2;
            bt[i] += bt2;
            at1 = at2;
            bt1 = bt2;   
        }
    }

    for (int i = 0; i < M; i++) //计算概率随时间变化
    {
        Pa[i] = (abs(at[i])/N)*(abs(at[i])/N);
        Pb[i] = (abs(bt[i])/N)*(abs(bt[i])/N);
    }
    

    //到此为止，aT和bT这俩数组，就是各阶段其概率分布了，接下来我们把它写入文件    
	FILE* fp = NULL; //文件指针
    fp = fopen("Results.txt", "w"); //打开文件
    for (int i = 0; i < M; i++)
    {
        fprintf(fp,"%f\n",Pb[i]);
    }
    fclose(fp); //关闭文件
}

int main()
{
    TwoLevelSys();  //调用TwoLevelSys函数
}