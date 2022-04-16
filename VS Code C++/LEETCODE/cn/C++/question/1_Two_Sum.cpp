// @algorithm @lc id=1 lang=cpp 
// @title two-sum


#include <iostream>
#include <vector>
#include <string>
#include "algm/algm.h"
using namespace std;
// @test([2,7,11,15],9)=[0,1]
// @test([3,2,4],6)=[1,2]
// @test([3,3],6)=[0,1]
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); i++)
        {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end())
                return {it->second, i};
            hashtable[nums[i]] = i;
        }
        return {};
    }
};