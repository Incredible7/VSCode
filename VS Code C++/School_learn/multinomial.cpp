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
				derivative[i - 1] = i;
		return;
	}

	//求解同余方程
	int Root(vector<int> equation, int p)
	{
		for (int i = 0; i < p; i++)
		{
			int sum = 0;
			for (int j = 0; j < 5; j++)
				sum += equation[j] * pow(i, j);
			if (sum % p == 0)
				return i;
		}
		return p + 1;//若无解则返回一个比模p大一的数
	}

	//检验解是否存在
	void check()
	{
	}

	//private:
		//由于多项式只需要存储而不需要外部调用，所以使用private属性
	vector<int> multinomial;
	vector<int> derivative;
};

int main()
{
	calculate C;
	C.enter();
}