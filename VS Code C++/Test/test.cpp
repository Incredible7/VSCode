#include <algorithm>
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

class Solution {
public:
    string convert(string s, int numRows)
    {
        if (s.size() <= 2)
            return s;
        int flag = 1;
        int len = 0;
        vector<string> a;
        a.resize(numRows);
        for (int i = 0; len < s.size(); i -= flag, len++) {
            if (len % (numRows - 1) == 0) //当进行所要求数字的循环时，flag倒置
                flag = -flag;
            a[i] += s[len];
        }
        string str;
        for (int j = 0; j < numRows; j++)
            str += a[j];
        return str;
    }
};

int main()
{
    string s = "PAYPALISHIRING";
    Solution S;
    cout << S.convert(s, 3);
}
