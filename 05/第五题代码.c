/* �����������Ͼ��ȷֲ����������㣬���������ڣ�x, y��ƽ����ͶӰ�ļ�
�ʷֲ����������ɴ���֤Marsaglia��������ȷΪ�����Ͼ��ȷֲ������������*/

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

void Sphere_RandN_Marsaglia_xy(int seed, int N)	//����N�������ģ�������xyֵд���ļ�
{
	double M = M_16807;
	double uv_list[2] = { 0 }; //����uvֵ��uv_list[0]��u, uv_list[1]��v
	double x = 0, y = 0, z = 0;
	//������Ϊz
	int s = seed;
	int i = 0;

	//�ļ�ָ��
	FILE* fp_x = NULL;
	FILE* fp_y = NULL;
	FILE* fp_z = NULL;


	fp_x = fopen("x.txt", "w");
	fp_y = fopen("y.txt", "w");
	fp_z = fopen("z.txt", "w");

	for (i = 0; i < N; )
	{
		uv_list[0] = Schrage_int(s);
		uv_list[1] = Schrage_int(uv_list[0]);
		s = Schrage_int(uv_list[1]);

		//��Schrage_int��������
		uv_list[0] = ((float)uv_list[0] / M);
		uv_list[1] = ((float)uv_list[1] / M);

		//��uv���[-1,1]�������
		uv_list[0] = 2 * uv_list[0] - 1;
		uv_list[1] = 2 * uv_list[1] - 1;

		if ((uv_list[0]*uv_list[0]+uv_list[1]*uv_list[1])<=1)
		{
			x = 2 * uv_list[0] * sqrt(1 - (uv_list[0] * uv_list[0] + uv_list[1] * uv_list[1]));
			y = 2 * uv_list[1] * sqrt(1 - (uv_list[0] * uv_list[0] + uv_list[1] * uv_list[1]));
			z = 1 - 2 * (uv_list[0] * uv_list[0] + uv_list[1] * uv_list[1]);
			fprintf(fp_x, "%f \n", x);
			fprintf(fp_y, "%f \n", y);
			fprintf(fp_z, "%f \n", z);
			i++;
		}

	}

	fclose(fp_x);		//�رմ򿪵��ļ�
	fclose(fp_y);		//�رմ򿪵��ļ�
	fclose(fp_z);
}



int main()	//�����������ڵ��ú�������
{
		Sphere_RandN_Marsaglia_xy(Seed(), 10000);		//�����Ϊ������xy����
}