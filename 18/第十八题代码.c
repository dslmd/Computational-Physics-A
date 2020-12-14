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
    
    printf("The seed is %d\n",seed);
	return seed;
}



void DLA()      //DLA模拟，生成"point.txt"文件，其行就是x轴，列就是y轴
{
    double M = M_16807;//参数
	int z = Seed();//初始化迭代量z，是种子值
    float rand = 0; //初始化随机数
    int rand_int = 0;   //用来产生随机整数
    int DLA_lattice[601][601]={0};  //定义DLA的格子，取奇数是为了找中心点方便，此时中心点是DLA_lattice[300][300]
    DLA_lattice[300][300] = 1;  //原点有个种子
    int xt = 0, yt = 0; //游走量
    int n = 0; //用来记录已经模拟出来的点的个数

	FILE* fp = NULL; //文件指针
    fp = fopen("point.txt", "w"); //打开文件

    //下面是循环找DLA点，n是成功点数
    while ( n<10000 )
    {
        //随机产生初值部分
        z = Schrage_int(z);//Schrage随机数产生器
        rand = ((float)z / M)*4;  //产生(0,4)之间的随机数
        rand_int = floor(rand); //有四个取值0，1，2，3各1/4几率
        z = Schrage_int(z);//Schrage随机数产生器
        rand = ((float)z / M)*4;  //产生(0,4)之间的随机数
        switch (rand_int)
        {
            case 0:
                xt = 50;
                yt = floor(rand*125)+50;
                break;
            case 1:
                yt = 550;
                xt = floor(rand*125)+50;
                break;
            case 2:
                yt = 50;
                xt = floor(rand*125)+50;
                break;
            case 3:
                xt = 550;
                yt = floor(rand*125)+50;
                break;
            default:
                break;
        }
//        printf("The initial [x,y] = [%d,%d]\n",xt,yt);
        
        //随机游走部分
        while (1)
        {
            z = Schrage_int(z);//Schrage随机数产生器
            rand = ((float)z / M)*4;  //产生(0,4)之间的随机数
            rand_int = floor(rand); //有四个取值0，1，2，3各1/4几率
            switch (rand_int)
            {
                case 0:
                    xt = xt-1;
                    yt = yt;
                    break;
                case 1:
                    xt = xt+1;
                    yt = yt;
                    break;
                case 2:
                    yt = yt+1;
                    xt = xt;
                    break;
                case 3:
                    yt = yt-1;
                    xt = xt;
                    break;
                default:
                    break;
            }
            //如果到边界了，跳出
            if ((xt==0)||(xt==600)||(yt==0)||(yt==600))
            {
                break;
            }
            //如果碰到点了，则生长，并且跳出
            if ( (DLA_lattice[xt+1][yt]||DLA_lattice[xt-1][yt]||DLA_lattice[xt][yt+1]||DLA_lattice[xt][yt-1]) == 1 )
            {
                n++;
                DLA_lattice[xt][yt]=1;
                break;
            }  
        }
    }

    //写入文件
    int i=0,j=0;
    for ( i = 0; i < 601; i++)
    {
        for ( j = 0; j < 601; j++)
        {
            fprintf(fp,"%d ",DLA_lattice[i][j]);
        }
        fprintf(fp,"\n");
    }

    fclose(fp);//关闭文件
}


void BoxCounting()  //盒计数法测量分形维数
{
	FILE* fp = NULL; //文件指针
    fp = fopen("point.txt", "r"); //打开文件
    int DLA_lattice[601][601]={0};
    for ( int i = 0; i < 601; i++)
    {
        for ( int j = 0; j < 601; j++)
        {
            fscanf(fp,"%d ",&DLA_lattice[i][j]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);

    printf("This is BoxCounting method\n");
    int i = 0, j = 0, k = 0, m = 0, n = 0;
    int v[9]={2,4,6,10,15,20,40,100,200};//记录分的块数
    int N=600;
    int number = 0; //用来记录分块内有点的分块数
    int sum = 0;//用来看矩阵块是不是为0

    //对于下面的这个for循环：i是对v值循环，jknm四个变量的作用是是对第j行、第k列的盒子进行第m行n列的求和，并计算所有有点的（即number>0）的盒子数
    for (i=0; i < 9; i++)
    {
        N = 600/v[i];
        number = 0;
        for ( j = 0; j < v[i]; j++)
        {
            for ( k = 0; k < v[i]; k++)
            {
                sum = 0;
                for ( m = 0; m < N; m++)
                {
                    for ( n = 0; n < N; n++)
                    {
                        sum+=DLA_lattice[j*N+m][k*N+n];
                    }
                    
                }
                if (sum>0)
                {
                    number++;//计数
                }
            }
            
        }
        printf("For v = %d, number = %d, D = %f\n",v[i],number,log(number)/log(v[i]));
    }
    
}


void Sandbox()  //利用Sandbox法来计算分形维数
{
    FILE* fp = NULL; //文件指针
    fp = fopen("point.txt", "r"); //打开文件
    int DLA_lattice[601][601]={0};
    for ( int i = 0; i < 601; i++)
    {
        for ( int j = 0; j < 601; j++)
        {
            fscanf(fp,"%d ",&DLA_lattice[i][j]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);

    printf("This is Sandbox method\n");
    
    //计算边长20，40，……，200的矩形内的点的个数
    for (int r = 10; r <= 100; r=r+10)
    {
        int number = 0;//用来计数
        for (int m = 300-r; m <= 300+r ; m++)
        {
            for (int n = 300-r; n < 300+r; n++)
            {
                if (DLA_lattice[m][n]==1)
                {
                    number++;//计数
                }
            }
        }
        printf("For r = %d, number = %d, D = %f\n",2*r,number,log(number)/log(2*r));
    }
    
}

int main()
{
    DLA();//生成"point.txt"文件
    BoxCounting();//利用盒计数法来计算分形维数
    Sandbox();//利用Sandbox方法计算分形维数
}
