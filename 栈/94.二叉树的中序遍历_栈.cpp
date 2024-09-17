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
#include<stack>
using namespace std;
/**/struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 }; 
 
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        //如果采用非递归的方法来写左中右，用栈来储存需要返回来用的数据
        vector<int> result;
        stack<TreeNode*> node_stack;
        TreeNode * node = root;
        while(!node_stack.empty() || node != NULL){
            if(node != NULL){
                node_stack.push(node);
                node = node->left;
            }
            else{
                TreeNode * stack_top = node_stack.top();
                node_stack.pop();  // 弹出当前节点
                result.push_back(stack_top->val);
                node = stack_top->right;
            }

        }
        return result;
    }
};
// @lc code=end

