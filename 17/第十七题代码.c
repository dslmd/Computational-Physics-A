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
#define _USE_MATH_DEFINES
#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)>(b)) ? (b):(a) )


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
    
//    printf("The seed is %d\n",seed);
	return seed;
}

//展示数组
void display(float array[], int maxlen)
{
    int i;
 
    for(i = 0; i < maxlen; i++)
    {
        printf("%-3f ", array[i]);
    }
    printf("\n");
 
    return ;
}


//快排算法
void QuickSort(float *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        float k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }
 
            if(i < j)
            {
                arr[i++] = arr[j];
            }
 
            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }
 
            if(i < j)
            {
                arr[j--] = arr[i];
            }
        }
 
        arr[i] = k;
 
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}


void diedai(float lambda) //在lambda值的时候求不动点，并且在quicksort之后，计算不同lambda值的时候的分叉个数
{
    double M = M_16807;//参数
	//迭代量为z
	int z = Seed();//定义种子值
	FILE* fp = NULL; //文件指针
    fp = fopen("diedai.txt", "a"); //打开文件
    int i = 0, j = 0;//定义循环量
    float x[100]={0};
    int number = 0;

    fprintf(fp, "%f ",lambda); //写入文件

    for (int j = 0; j < 5; j++) //避免初值影响，每个lambda取5*20个
    {
        z = Schrage_int(z);
        float x0 = ((float)z / M)*8-4;//定义初始值
        float x_temp = x0;//定义迭代量

        //先热化10000步
        for (int i = 0; i < 1000; i++)
        {
            x_temp = lambda*sin(M_PI*x_temp);
        }

        //再写入20步进入文件
        for (int i = 0; i < 20; i++)
        {
            x_temp = lambda*sin(M_PI*x_temp);
            x[i+j*20]=x_temp;
            fprintf(fp, "%f ",x_temp); //写入文件
        }
    }
    fprintf(fp,"\n");
	fclose(fp);		//关闭打开的文件

    //接下来是判断此时的lambda是不是分叉点，如果是，则print出来此时的lambda
//    display(x,100);
    QuickSort(x, 0, 99);
//    display(x, 100);
    
	FILE* fpl = NULL; //文件指针
    fpl = fopen("lambda.txt", "a"); //打开文件

    for (j = 0; j < 99; j++)
    {
        if ((x[j+1]-x[j])<0.00001)
        {
            number++;
//            printf("%d",number);
        }
    }
    if (number >= 100-1)//改变number的值来看分叉的数量
    {
        fprintf(fpl,"%f\n",lambda);
    }

	fclose(fpl);		//关闭打开的文件
}


int main(int argc, char const *argv[])
{
//计算PI是多少，然后丢进宏定义
//    printf("%lf",acos(-1));
    float lambda = 0;
    for (lambda = -2; lambda < 2; lambda=lambda+0.001)
    {
        diedai(lambda);
    }

//    diedai(2);
}
