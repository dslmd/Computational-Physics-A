/*��pdf���������ϵʽXXX���˴���ȥ�������ҵ����е�һ�ֺ������������ʲ���������������*/

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
#define Pi 3.1415926

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


void x_RandN(int seed, int N)	//����N�������,��д���ļ�
{
	double M = M_16807;

	//������Ϊz
	int z = seed;
	int i = 0;

	FILE* fp = NULL; // �ļ�ָ��

	fp = fopen("random.txt", "w");

	for (i = 0; i < N; i++)
	{
		z = Schrage_int(z);
		fprintf(fp, "%f \n", (tan(Pi * (((float)z / M) - 1.0 / 2))) );
	}

	fclose(fp);		//�رմ򿪵��ļ�

}



int main()	//�����������ڵ��ú�������
{
	x_RandN(Seed(), 10000);		//�����Ϊ������x�������

}