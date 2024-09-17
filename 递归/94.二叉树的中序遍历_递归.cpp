/*
 * @lc app=leetcode.cn id=94 lang=cpp
 *
 * [94] 二叉树的中序遍历
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include<vector>
#include<iostream>
using namespace std;
/**/ struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 }; 

class Solution {
public:
    vector<int> result;
    void zhongxubianli(vector<int> & result, TreeNode* node){
        if(node != NULL){
            //左节点
            zhongxubianli(result, node->left);
            // mid
            result.push_back(node->val);
            // right
            zhongxubianli(result, node->right);
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        // 某序遍历：何时访问中间节点
        // 中序遍历：左中右
        // 简单的递归写法：
        zhongxubianli(result, root);
        return result;
    }
};
// @lc code=end

