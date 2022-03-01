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

class Solution
{
public:
    bool buddyStrings(string s, string goal)
    {
        if (s.size() != goal.size())
            return false;
        else if (s.size() == goal.size() == 0)
            return true;
        int x = 0, y = 0;
        int path[128] = {0};
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != goal[i])
                x++;
            else if (path[s[i]] == 1)
                y++;                                                              
            path[s[i]] = 1;
        }
        if (x == 2 || (x == 0 && y > 1))
            return true;
        return false;
    }
};

int main()
{
    Solution S;
    string s = "abcaa", s1 = "abcbb";
    cout << S.buddyStrings(s, s1);
}
