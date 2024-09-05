/*
 * @lc app=leetcode.cn id=301 lang=cpp
 *
 * [301] 删除无效的括号
 */

// @lc code=start
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<unordered_set>
using namespace std;
class Solution {
public:
    bool is_valid_string(string s){
        int l0 = s.length();
        int sum = 0;
        for(int i = 0; i < l0; i++){
            if(s[i] == '(') sum+=1;
            if(s[i] == ')') sum-=1;
            if(sum < 0) return false;
        }
        if(sum == 0) return true;
        else return false;
    }
    void found_son(string s, unordered_set<string> & maybe_answer_strings){
        int l = s.length();
        //cout<<"l "<<l<<endl;
        if(l == 1){ // 剩下1个，并且还没被认证成为“有效”并且还要找后代，只可能是括号不可能是单字母
            maybe_answer_strings.insert("");
            return;
        }
        // 注意substr是左闭右开区间
        if (s[0] =='(' || s[0] == ')') maybe_answer_strings.insert(s.substr(1, l)); // 去除第0个
        for(int i = 1; i < l; i++){ // 删除s中第i个（如果第i个是括号）
            if (s[i] =='(' || s[i] == ')'){
                //cout << "s["<<i<<"]: "<<s[i]<<endl;
                string s1 = s.substr(0, i) + s.substr(i+1, l); // 注意substr是左闭右开区间，所以前面是substr(0, i)
                maybe_answer_strings.insert(s1);
                cout << s1 << endl;
            }
        }
        return;
    }
    vector<string> removeInvalidParentheses(string s) {
        int l = s.length();
        vector<string> answer;
        // 1 在循环中依次列出“删一个”、“删两个”……的可能情况，用于广搜
        //cout << "1" << endl;
        unordered_set<string> maybe_answer_strings;
        
        maybe_answer_strings.insert(s);
        bool has_answer = 0;
        //cout << "2" << endl;
        while(1){
            //cout <<"==========="<<endl;
            for(auto s0: maybe_answer_strings){
                if(is_valid_string(s0)){
                    cout<<"answer "<< s0<<endl;
                    answer.push_back(s0);
                    //maybe_answer_strings.erase(s0);
                    has_answer = 1;
                }
            }
            // ！！不能一边使用迭代器一边erase它的成员
            unordered_set<string> maybe_answer_strings_next;
            if(has_answer) return answer;
            else{
                int l0 = maybe_answer_strings.size();
                //int have_found_son = 0;
                //cout << "3" << endl;
                for(auto s0: maybe_answer_strings){
                    //have_found_son++;
                    //if(have_found_son > l0) break;
                    //cout << "4" << endl;
                    found_son(s0, maybe_answer_strings_next);
                    
                }
                maybe_answer_strings = move(maybe_answer_strings_next);
            }
        }


    }
};
// @lc code=end

