/* ��16807��������������������������ϵ x_n-1 < x_n < x_n+1
�ı��ء�����Fibonacci�ӳٲ������г������ֹ�ϵ�ı��ء�*/
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


void Write_RandN(int seed, int N)	//����N�������,��д���ļ������������Ϊ�˴��������԰��˹���
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
		fprintf(fp, "%f \n", ((float)z / M));
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





double Schrage_16807_ratio(long int N)		 //����N������������Ҽ�����������ı�����Ȼ��������������
{
	double M = M_16807;
	int z = Seed();
	int i = 0;
	float temp[10] = { 0 };
	long int number=0;  //���ڼ�������Ŀ�ĸ���

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



double lagged_fib_generater_ratio(int N, int p, int q)	//ͨ��Fibonacci�ӳٲ�����������������������ӳ�����ֱ���������Ҫ���ratio

{
	int z = Seed();//������
	//�Ȳ���50��In
	int In[50] = { 0 };
	int number = 0;//���ڼ�¼����ĸ���
	for (int i = 0; i < 50; i++)
	{
		z = Schrage_int(z);
		In[i] = z;
	}
	

	for (int i = 0; i < N; i++)
	{
		int I = In[49-p]-In[49-q];	//����fib

		if (I < 0)		//�ж�����,�Ӷ�����������
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






void print_16807_ratio()	//�����Ϊ��������������ı���, Ȼ��print
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


void print_fib_ratio()	//�����Ϊ������Fibonacci���������Լ����ؼ��������������������������������ı���, Ȼ��print
{
	printf("For ���ؼ���������[p,q]=[22,43]: \n");
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


int main()	//�����������ڵ��ú�������
{
	//	Write_RandN(Seed(), 1000);		//�����Ϊ���������ݣ�������֮��Ͳ�����
		print_16807_ratio();
		print_fib_ratio();
}