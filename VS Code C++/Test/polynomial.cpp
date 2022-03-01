#include <algorithm>
#include <sstream>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*函数实现：
	1、输入函数，使用vector存储多项式。键值为次数，值为系数。
	2、计算函数，计算多项同余式的解。
	3、求解逆元函数。
*/

class calculate
{
public:
	calculate()
	{
		multinomial.resize(50, 0);
		derivative.resize(50, 0);
	}
	//输入函数
	void enter()
	{
		cout << "Please enter the polynomial expression, one term at a time.\nFirst the number of powers, then the coefficient, separated by Spaces." << endl;
		string str;
		istringstream read;
		int a = 0, b = 0, c = 1;
		getline(cin, str);
		do
		{
			str.clear();
			cout << "Please enter:";
			getline(cin, str);
			read.str(str);
			read >> a >> b;
			read.clear();
			multinomial[a] = b;
			cout << "Do you want to continue? 0. NO 1. Yes";
			cin >> c;
			getline(cin, str);
		} while (c);

		//求导函数
		for (int i = 1; i < multinomial.size(); i++)
			if (multinomial[i])
				derivative[i - 1] = i * multinomial[i];
		return;
	}

	//求解第一次同余方程
	int Root_1(vector<int> equation, int p)
	{
		for (int i = 0; i < p; i++)
		{
			int sum = 0;
			for (int j = 0; j < equation.size(); j++)
				sum += equation[j] * pow(i, j);
			if (sum % p == 0)
				return i;
		}
		return p + 1; //若无解则返回一个比模p大一的数
	}

	//求解之后的同余方程
	int Root_2(vector<int> equation, int x, int p, int a)
	{
		for (int i = x; i < pow(p, a); i += pow(p,a-1))
		{
			int sum = 0;
			for (int j = 0; j < equation.size(); j++)
				sum += equation[j] * pow(i, j);
			if (sum % (int)pow(p,a) == 0)
				return i;
		}
		return pow(p, a) + 1; //若无解则返回一个比模p大一的数
	}

	//求解最大公因数
	int gcd_1(int a, int b) { return b == 0 ? a : gcd_1(b, a % b); }

	//求解函数
	int Calculate(int p, int a)
	{
		enter();
		int x = 0, sum = 0;
		for (int i = 1; i <= a; i++)
		{
			if (i == 1)
			{
				x = Root_1(multinomial, p);
				if (x == p + 1) //若第一次求解同余式方程无解则直接返回
					return INT_MAX;
				for (int j = 0; j < derivative.size(); j++)
					sum += derivative[j] * pow(x, j);
				if (gcd_1(sum, p) != 1)
					return INT_MAX;
			}
			else
				x = Root_2(multinomial, x, p, i);
		}
		return x; 
	}

private:
	//由于多项式只需要存储而不需要外部调用，所以使用private属性
	vector<int> multinomial;
	vector<int> derivative;
};

int main()
{
	calculate C;
	int p, a;
	cout << "Please enter the number p and it's power:";
	cin >> p >> a;
	cout << C.Calculate(p, a);
}
