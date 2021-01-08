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

void SchodingerEq(double energy)    //计算波函数，并将波函数的迭代点写入"wavefunc.txt"
{
    int i = 0;

    //定义phi和y，一共10500点，10500在区域内，500在区域外
    double phi[10500]={0};
    double y[10500]={0};
    double f = 0;
    double h = 0.0001;
    y[0]=0;
    y[1]=0.1;

    //接下来是区域内的点，无量纲化，见报告，有f=energy
    f = energy;
    phi[0] = y[0]/(1-h*h*f/12);
    phi[1] = y[1]/(1-h*h*f/12);

    for ( i = 1; i < 9999; i++)
    {
        y[i+1]=2*y[i]-y[i-1]+h*h*f*phi[i];
        phi[i+1] = y[i+1]/(1-h*h*f/12);
    }

    //接下来是区域外的点，应该趋于负无穷，取-570000000
    f = -570000000;
    for ( i = 9999; i < 10499; i++)
    {
        y[i+1]=2*y[i]-y[i-1]+h*h*f*phi[i];
        phi[i+1] = y[i+1]/(1-h*h*f/12);
    }

    //写入到"wavefunc.txt"中
    FILE* fp = NULL; //文件指针
    fp = fopen("wavefunc.txt", "w"); //打开文件
    for (i = 0; i < 10500; i++)
    {
        fprintf(fp,"%f\n",phi[i]);
    }
    fclose(fp);
}


int main()
{
    SchodingerEq(-246.74);
}