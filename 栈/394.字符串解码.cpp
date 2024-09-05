/*
 * @lc app=leetcode.cn id=394 lang=cpp
 *
 * [394] 字符串解码
 */

// @lc code=start
#include<string>
#include<iostream>
#include<stack>
using namespace std;
class Solution {
public:
    stack <int> repeat_n;
    stack <string> wait_to_repeat;
    int get_number(string& s, int i, int l){
        //int l = s.length();
        if(s[i]<'0' || s[i] > '9'){//代表无数字 因为对应的字符串没有]作为结尾，所以也要单独处理
            repeat_n.push(1);
            return i;
        }
        string s_number = "";
        int j;
        for(j = i; j < l; j++){
            cout << "get_number i: "<<j<<endl;
            if(s[j]>='0' && s[j] <= '9'){
                s_number+=s[j];
            }
            else break;
        }
        cout<<"get_number: number "<<s_number<<endl;
        i = j; // 下一步寻找的start place
        //s = s.substr(i, l);
        repeat_n.push(atoi(s_number.c_str()));
        return i;
    }
    int get_string(string& s, int start_place, int l){
        //int l = s.length();
        string part_string = "";
        int i;
        for(i = start_place; i < l; i++){
            // 2[ad3[cd]ef]
            if(s[i] == '[') continue;
            else if(s[i] >= 'a' && s[i] <= 'z'){
                part_string += s[i];
                continue;
            }
            else if(s[i] == ']'){
                wait_to_repeat.push(part_string);
                start_place = i+1; // 下一步从i+1开始找
                return start_place;
                //find(s, start_place, l);
                //return;
            }
            else{ // 遇见了[]里套[]的类型，这种类型下，这里遇到的一定是数字
                string little_string;
                i = find(s, i, l, little_string) - 1;
                part_string += little_string; // 加上子部分
            }
        }
        wait_to_repeat.push(part_string); // 对于没有]结尾的string
        return i+1;
    }
    int find(string & s, int start_place, int l, string & little_string){ 
        // find 起到一个把栈里的东西组合成结果数组的作用，在一个大编码（形如3[ab2[cd3[ef]4[gh]jk]], 或者是简单的无编码abde这种） 解码结束后调用
        //string little_string = "";
        int next_start_place;
        //if(s[start_place] >= '0' && s[start_place] <= '9'){ // 形如 3[zb]
            next_start_place = get_number(s, start_place, l);
            next_start_place = get_string(s, next_start_place, l);
            // start to repeate to new string

            int np = repeat_n.top(); 
            repeat_n.pop();
            cout<<"np: "<<np<<endl;
            string st = wait_to_repeat.top();
            wait_to_repeat.pop();
            cout<<"st: "<<st<<endl;

            while(np>0){
                little_string += st;
                np--;
            }
            //cout<<"repeat_n.empty(): "<< repeat_n.empty()<<endl;
            //cout<<"wait_to_repeat.empty(): "<< wait_to_repeat.empty()<<endl;
        //}
        return next_start_place;
    }
    string decodeString(string s) {
        // 不能一边遍历一边修改s
        // 所以遍历的i应该设置为全局变量？
        
        int l = s.length();
        int first_id = 0;
        string final_string = "";

        while(first_id < l){
            string once_result_string = "";
            first_id = find(s, first_id, l, once_result_string);
            final_string += once_result_string;
        }
        return final_string;
    }
};
// @lc code=end

