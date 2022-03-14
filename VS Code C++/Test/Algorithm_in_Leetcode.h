#ifndef ALGORITHM_IN_LEETCODE
#define ALGORITHM_IN_LEETCODE

#include <algorithm>
#include <regex>
#include <climits>
#include <sstream>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    //Morris遍历法（中序遍历），能够将空间较少到 O(1);
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        TreeNode *predecessor = nullptr;

        while(root != nullptr){
            if(root->left){
                predecessor = root->left;
                //找到左子树最右的叶子结点（不重复）
                while(predecessor->right && predecessor != root){
                    predecessor = predecessor->right;
                }
                //使该叶子结点右指针指向根节点
                if(!predecessor->right){
                    predecessor->right = root;
                    root = root->left;
                }
                //说明没有左子树，我们断开链接
                else{
                    res.push_back(root->val);
                    predecessor->right = nullptr;
                    root = root->right;
                }
            }
            //若没有左孩子，直接访问右孩子
            else{
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }

    //给你中序遍历和后序遍历的vector，构造二叉树
    unordered_map<int, int> pos;
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        for(int i = 0; i < n; ++i) pos[inorder[i]] = i;//记录中序遍历每个节点的位置
        return build(inorder, postorder, 0, n-1, 0, postorder.size() - 1);
    }

    TreeNode* build(vector<int>& inorder, vector<int>& postorder, 
                    int il, int ir, int pl, int pr)
    {
        if(pl > pr) return nullptr;
        auto root = new TreeNode(postorder[pr]);
        int k = pos[root->val];
        root->left = build(inorder, postorder, il, k-1, pl, pl+k-1-il);
        root->right = build(inorder, postorder, k+1, ir, pl+k-il, pr-1);
        return root;
    }

private:

};


#endif