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

void Lorentzian_selected_Guassian_RandN(int seed, int N)	//��Lorentz��ѡ��N��Gauss�͵������,��д���ļ�
{
	double M = M_16807;
	double uv_list[2] = { 0 }; //����uvֵ��uv_list[0]��u, uv_list[1]��v
	double x = 0, y = 0, z = 0;
	//������Ϊz
	int s = seed;
	int i = 0;
	int count = 0;// ������һ���ж��ٴΣ����ڼ���Ч��

	//�ļ�ָ��
	FILE* fp_x = NULL;


	fp_x = fopen("Lorentzian.txt", "w");

	for (i = 0; i < N; )
	{
		uv_list[0] = Schrage_int(s);
		uv_list[1] = Schrage_int(uv_list[0]);
		s = Schrage_int(uv_list[1]);

		//��Schrage_int��������
		uv_list[0] = ((float)uv_list[0] / M);
		uv_list[1] = ((float)uv_list[1] / M);

		//��x���[-1,1]�������
		x = 2 * uv_list[0] - 1;
		//��y���[0,1.3]����
		y = 1.3 * uv_list[1];


		if (y <= 1.213 / (1 + x * x * x * x))
		{
			count++;

			if (y <= exp(-0.5 * x * x))
			{
				fprintf(fp_x, "%f \n", x);
				i++;
			}

		}

	}
	printf("The efficiency of the selection is %f \n", (float)N / count);
	fclose(fp_x);		//�رմ򿪵��ļ�
}












int main()
{
	Lorentzian_selected_Guassian_RandN(Seed(), 50000);
}