#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <climits>
#include <iostream>

typedef struct Chrom
{
    short int bit[6]; //一共6bit来对染色体进行编码，其中1位是符号位，取值范围-64~+64
    int fit;          //适应值
    double rfit;      //相对的fit值，即所占的百分比
    double cfit;      //积累概率
} chrom;

//定义会用到的几个函数
void *population_init(chrom popcurrent[4]); //进行种群初始化
int x(chrom popcurrent);
inline int y(int x) { return -(x * x) + 5; }
void *selection(chrom popcurrent[4]);                //选择操作
void *select_new(chrom popcurrent[4]);               //基于概率分布
void *crossover(chrom popnext[4]);                   //交叉操作
void *mutation(chrom popnext[4]);                    //突变
double r8_uniform_ab(double a, double b, int &seed); //生成a~b之间均匀分布的数字
chrom popcurrent[4], popnext[4];                     //初始种群规模和更新后种群规模

int main()
{
    int num; //迭代次数
    int i, j, l, Max, k;
    Max = 0; //函数最大值

    std::cout << "Welcome to the Genetic Algorithm!\n";
    std::cout << "The Algorithm is based on the function y = -x^2 + 5 to find the maximum value of the function.\n";
enter:
    std::cout << "\nPlease enter the number of iterations: ";
    std::cin >> num;
    if (num < 1)
        goto enter; //判断输入的迭代次数是否为负或零
    srand(time(0));
    population_init(popcurrent); //随机产生初始种群
    // x的取值范围是-32~+31
    Max = popcurrent[0].fit; // Max初始化

    for (i = 0; i < num; ++i)
    {
        std::cout << "Iretation_Time: " << i << "\n";
        for (j = 0; j < 4; ++j)
        {
            popnext[j] = popcurrent[j]; //更新种群
        }
        selection(popnext); //挑选优秀个体
        crossover(popnext); //交叉得到新个体
        mutation(popnext);  //变异得到新个体
        for (j = 0; j < 4; ++j)
        {
            popcurrent[j] = popnext[j]; //种群更替
        }
    } //等待迭代终止
    //对于真正的随机数需要注意的是取较大的迭代次数
    for (l = 0; l < 3; ++l)
    {
        if (popcurrent[l].fit > Max)
        {
            Max = popcurrent[l].fit;
            k = x(popcurrent[l]); //此时的value即为所求的x值
        }
    }

    std::cout << "\nThe max value of function is " << Max << " when x is equal to " << k << "\n";
    std::cout << "\nPress any key to end!";
    _flushall(); //清除所有缓冲区
    getche();   //从控制台取字符，不以回车为结束
}

void *population_init(chrom popcurrent[4])
{
    int i, j, value1;
    int random;
    double sum = 0;
    for (j = 0; j < 4; ++j)
    { //从第一个染色体到第四个染色体
        for (i = 0; i < 6; ++i)
        {                        //从第一个基因位到第六个基因位
            random = rand();     //产生一个随机值
            random = random % 2; //随机产生0、1
            popcurrent[j].bit[i] = random;
        }

        value1 = x(popcurrent[j]);     //将二进制转换为十进制，得到一个整数值
        popcurrent[j].fit = y(value1); //计算染色体的适应度值
        sum += popcurrent[j].fit;
        printf("\n popcurrent[%d]=%d%d%d%d%d%d  value=%d  fitness = %d", j, popcurrent[j].bit[5], popcurrent[j].bit[4], popcurrent[j].bit[3], popcurrent[j].bit[2], popcurrent[j].bit[1], popcurrent[j].bit[0], value1, popcurrent[j].fit);
        //输出整条染色体的编码情况
    }
    //计算适应值的百分比，该参数是在用轮盘赌选择法时需要的
    for (j = 0; j < 4; ++j)
    {
        popcurrent[j].rfit = popcurrent[j].fit / sum;
        popcurrent[j].cfit = 0; //初始化
    }
    return (0);
}

int x(chrom popcurrent) // 函数：将二进制换算为十进制；
{                       //此处的染色体长度为，其中个表示符号位

    int z;
    z = (popcurrent.bit[0] * 1) + (popcurrent.bit[1] * 2) + (popcurrent.bit[2] * 4) + (popcurrent.bit[3] * 8) + (popcurrent.bit[4] * 16);

    if (popcurrent.bit[5] == 1) // 考虑到符号；
    {
        z = z * (-1);
    }

    return (z);
}

void *select_new(chrom popnext[4]) //计算概率
{
    int i, j, men;
    double p, sum = 0.0;
    //种群的总适应数
    for (men = 0; men < 4; ++men)
    {
        sum += popnext[men].fit;
    }
    //计算个体的相对适应度
    for (men = 0; men < 4; ++men)
    {
        popnext[men].rfit = popnext[men].fit / sum;
    }
    //计算累计概率
    popcurrent[0].cfit = popcurrent[0].rfit;
    for (men = 1; men < 4; ++men)
    {
        popnext[men].cfit = popnext[men - 1].cfit + popnext[men].rfit;
    }
    for (i = 0; i < 4; ++i)
    {
        //通过函数生成0~1之间均匀分布的数字
        p = rand() % 10;
        p = p / 10;
        if (p < popnext[0].cfit)
            popcurrent[i] = popnext[0];
        else
            for (j = 0; j < 4; ++j)
            {
                if (popnext[j].cfit <= p && p < popnext[j + 1].cfit)
                    popcurrent[i] = popcurrent[j + 1];
            }
    }

    //重写旧种群
    for (i = 0; i < 4; ++i)
    {
        popnext[i] = popcurrent[i];
    }
    return(0);
}

void *selection(chrom popnext[4]) //函数：选择个体
{
    int i, j;
    chrom temp; // 中间变量
    //因此此处设计的是个个体，所以参数是
    for (i = 0; i < 3; i++) // 根据个体适应度来排序；（冒泡法）
    {
        for (j = 0; j < 3 - i; j++)
        {
            if (popnext[j + 1].fit > popnext[j].fit)
            {
                temp = popnext[j + 1];
                popnext[j + 1] = popnext[j];
                popnext[j] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        printf("\nSorting:popnext[%d] fitness=%d", i, popnext[i].fit);
        printf("\n");
    }
    _flushall(); /* 清除所有缓冲区 */
    return (0);
}

double r8_uniform_ab(double a, double b, int &seed)
{
    int k;
    double value;
    if (seed == 0)
    {
        std::cerr << "\n";
        std::cerr << "R8_UNIFORM_AB - Fatal error!\n";
        std::cerr << "  Input value of SEED = 0.\n";
        exit(1);
    }

    k = seed / 127773;
    seed = 16807 * (seed - k * 127773) - k * 2836;
    if (seed < 0)
    {
        seed += INT_MAX;
    }
    value = (double)(seed)*4.656612875e-10;
    value = a + (b - a) * value;
    return value;
}

void *crossover(chrom popnext[4])
{
    int random, i;
    // srand(time(0))
    random = rand();           //随机产生交叉点
    random = (random % 5) + 1; //交叉点控制在0~5之间
    for (i = 0; i < random; ++i)
    {
        popnext[2].bit[i] = popnext[0].bit[1];
        popnext[3].bit[i] = popnext[1].bit[i];
    }
    for (i = random; i < 6; ++i)
    { //交叉交叉点以外的位
        popnext[2].bit[i] = popnext[1].bit[i];
        popnext[3].bit[i] = popnext[0].bit[i];
    }
    for (i = 0; i < 4; ++i)
    {
        popnext[i].fit = y(x(popnext[i])); //为新个体计算适应度
    }
    for (i = 0; i < 4; i++)
    {
        printf("\nCrossOver popnext[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i, popnext[i].bit[5], popnext[i].bit[4], popnext[i].bit[3], popnext[i].bit[2], popnext[i].bit[1], popnext[i].bit[0], x(popnext[i]), popnext[i].fit);
        // 输出新个体；
    }
    return (0);
}

void *mutation(chrom popnext[4])
{
    int random;
    int row, col, value;
    // srand(time(0));
    random = rand() % 50; //随机产生到之间的数
    //变异操作遵从概率进行，一般值较小
    if (random == 25) // random==25的概率只有2%，即变异率为2%
    {
        col = rand() % 6; //随机产生要变异的基因位号
        row = rand() % 4; //随机产生要变异的染色体号

        if (popnext[row].bit[col] == 0)
            popnext[row].bit[col] = 1;
        else if (popnext[row].bit[col] == 1)
            popnext[row].bit[col] = 0;
        popnext[row].fit = y(x(popnext[row]));
        value = x(popnext[row]);
        printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   fitness=%d", row,col ,popnext[ row].bit [5],popnext[ row].bit [4],popnext[ row].bit [3],popnext[ row].bit [2],popnext[ row].bit [1],popnext[ row].bit [0],value, popnext[row ].fit);
 
		// 输出变异后的新个体；
	}                                          
 
	return(0);
}