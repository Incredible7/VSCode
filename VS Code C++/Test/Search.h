#include <string>
#include <vector>
#include "BinTree.h"
using namespace std;

const int KEY = 15;

struct HashTable
{
    int key; //跳转表
    int value;
    HashTable *next;
    HashTable *nextlevel;
};

//二分查找
int Bin_Search(vector<int> nums, int value, int low, int high)
{
    int mid = (low + high) / 2;
    if (nums[mid] == value)
        return mid;
    else if (nums[mid] > value)
        return Bin_Search(nums, value, low, mid - 1);
    else
        return Bin_Search(nums, value, mid + 1, high);
}

//哈希跳转表查找
HashTable *HashSearch(HashTable *H, int value)
{
    HashTable *p = H;
    while (value % KEY != p->key)
        p = p->next;
    while (p->value != value)
        p = p->nextlevel;
    return p;
}

// KMP算法
void getNext(string t, vector<int>& next) {
    int i = 0, j = -1;
    next.resize(t.size());
    next[0] = -1;
    while (i < t.size() - 1) {
        if (j == -1 || t[i] == t[j]) {
            next[++i] = ++j;
        } else {
            j = next[j];
        }
    }
}

int KMP_Match(string s, string t, int pos) {
    int i = pos, j = 0;
    vector<int> next;
    getNext(t, next);
    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
        if (j == -1) {
            j++;
            i++;
        }
    }
    return j >= t.size() ? i - t.size() : -1;
}
