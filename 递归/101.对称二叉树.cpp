/*
 * @lc app=leetcode.cn id=101 lang=cpp
 *
 * [101] 对称二叉树
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
/**/  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  }; 

#include<vector>
using namespace std;
class Solution {
public:
vector<int> val_left_right_mid;
vector<int> val_right_left_mid;
// -100 <= Node.val <= 100, 我们把空子节点用250表示
    void left_right_mid(TreeNode* node){
        if(node == NULL){
            val_left_right_mid.push_back(250);
            return;
        }
        else{
            left_right_mid(node->left);
            left_right_mid(node->right);
            val_left_right_mid.push_back(node->val);
        }
    }
    void right_left_mid(TreeNode* node){
        if(node == NULL){
            val_right_left_mid.push_back(250);
            return;
        }
        else{
            right_left_mid(node->right);
            right_left_mid(node->left);
            val_right_left_mid.push_back(node->val);
        }
    }
    bool isSymmetric(TreeNode* root) {
        // 考虑广搜遍历？对于某个节点，先对其层序遍历，然后检查这层是否是对称的？[最后放弃了这个思路]
        // 考虑“类似后序遍历”的思路
        //以左右中、右左中的顺序分别遍历 如果相同那么就对称，不相同就不对称，把空节点的val用250表示
        left_right_mid(root);
        right_left_mid(root);
        //if(val_left_right_mid.size() != val_right_left_mid.size()) return false;
        int l = val_left_right_mid.size();
        for(int i = 0; i < l; i++){
            if(val_left_right_mid[i] != val_right_left_mid[i])
                return false;
        }
        return true;
    }
};
// @lc code=end

