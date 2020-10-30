/* ��Schrage������д������ӳ��������������������Ϊ�������ֵ
������ɵ��ƽ��ֲ�ͼ������<xk>���Ծ����ԣ�ȡ��ͬ������Nֵ������
ƫ����N�Ĺ�ϵ����C(l) ������2ά�����ԣ��ܵ���N > 107����*/
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

int Schrage_int(int seed)	//schrage����������һ������ֵ���������һ����Ӧ����
{
	if (seed < 0)
	{
		return -1;	//���󷵻�-1
	}

	int z = A_16807 * (seed % Q_16807) - R_16807 * (seed / Q_16807);	//����Shrage

	if (z < 0)		//�ж�����,�Ӷ�����������
	{
		return z + M_16807;
	}
	else
	{
		return z;
	}
}


void Write_RandN(int seed, int N)	//����N�������,��д���ļ�
{
	double M = M_16807;

	//������Ϊz
	int z = seed;
	int i = 0;

	FILE* fp = NULL; // �ļ�ָ��

	fp = fopen("data.txt", "w");

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		fprintf(fp,"%f \n", ((float)z/M));
	}

	fclose(fp);		//�رմ򿪵��ļ�

}

int Seed()	//ͨ������ʱ���������ֵ
{
	time_t rawtime;
	int seed;
	struct tm* info;	//��ȡ
	time(&rawtime);
	info = localtime(&rawtime);	//ת��Ϊ��ǰʱ����ʱ��
	info->tm_year = info->tm_year % 100;

	seed = info->tm_year + 70 * (info->tm_min + 12 * (info->tm_mday\
		+ 31 * (info->tm_hour + 23 * (info->tm_min + 59 * (info->tm_sec)))));	//��������
	return seed;
}



double Aver_RandN(int seed, int N, int k)	//����N�������,������x^kƽ��ֵ
{
	double M = M_16807;

	//������Ϊz
	int z = seed;
	int i = 0;
	float total = 0;
	float aver = 0;
	float temp = 0;

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		temp = ((float)z / M);
		temp = pow(temp, k);
		total += temp;
	}

	aver = total / N;

	return aver;
}


double CL(int l, int N)		 //����N����������������ڼ���C(L)
{
	double M = M_16807;
	int z = Seed();
	int i = 0;
	float total_linear = 0, total_squa = 0, total_dev = 0; //linear, squa, dev�ֱ�������Ժͣ�ƽ���ͣ���l�ĺ�
	float aver_linear = 0, aver_squa = 0, aver_dev = 0;		//linear, squa, dev�ֱ��������ƽ����ƽ��ƽ������l��ƽ��
	float temp[10] = {0};
	double CL = 0;

	for (i = 0; i < N+10; i++)
	{
		z = Schrage_int(z);
		for (int tm = 9; tm > 0; tm--)
		{
			temp[tm] = temp[tm - 1];
		}
		temp[0] = ((float)z / M);

		if (i > 9)
		{
			total_linear += temp[0];
			total_squa += temp[0]*temp[0];
			total_dev += temp[0] * temp[l];
		}
		
	}

	aver_linear = total_linear / N;
	aver_squa = total_squa / N;
	aver_dev = total_dev / N;

	CL = (aver_dev - pow(aver_linear,2)) / (aver_squa - pow(aver_linear,2));

	return CL;
}



int main()	//�����������ڵ��ú�������
{
//	Write_RandN(Seed(), 10000000);		//�����Ϊ���������ݣ�������֮��Ͳ�����

//	��������x^k���Ծ�����
/*	long int N = 0;
	for (N = 100; N < 10000000; N=N*10)
	{
		for (int k = 2; k < 8; k=k+2)
		{
			printf("When k is %d, N is %d, the average is %f \n",k,N, Aver_RandN(Seed(), N, k));
		}
	}*/

	long int N = 10000000;
	for (int l = 1; l < 8; l++)
	{
		printf("When l = %d, the C(L) is %f \n", l, CL(l, N));
	}
}