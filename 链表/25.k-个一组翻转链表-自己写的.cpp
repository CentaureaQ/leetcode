/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
 */

// @lc code=start
/** */
//Definition for singly-linked list.
#include<iostream>
using namespace std;
/* */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
}; 

class Solution {
public:
    void exchange(ListNode* first, ListNode* previous, int k){
        //ListNode* tail;
        ListNode* next[k+1];
        ListNode* mid = first;
        for(int i = 1; i <= k; i++){
            next[i] = mid->next;
            mid = next[i];
        }
        ListNode* ptr = first->next;
        first->next = next[k];
        ListNode* next_ptr = ptr->next;
        ptr->next = previous->next;
        cout<<"1"<<endl;
        for(int i = 3; i <= k; i++){
            ptr = next_ptr;
            next_ptr = ptr->next;
            ptr->next = next[i-2];
            cout<<"2"<<endl;
        }
        previous->next = next[k-1];
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        // head 1 2 3 4 5   6
        // head 5 4 3 2 1   6
        // head 1 2    6
        // head 2 1    6
        // next[6] 储存1-5的下一个
        // new_next[1] = next[5] 1的新的下一个是原来5的下一个
        // new_next[2] = next[head] [is 1]
        // new_next[3] = next[1] 
        // new_next[4] = next[2] 
        // new_next[5] = next[3] 
        // new_next[head] = next[4] 
        if (k == 1 || head == nullptr) {
            return head; // 当k为1或链表为空时，直接返回原链表
        }
        ListNode minus1(-1, head);
        ListNode* previous = & minus1;
        int n=0;
        ListNode *p = & minus1;
        while(p->next!=NULL){ // 需要注意最后一项的next是null
            n++;
            p=p->next;
        }

        // 先把前k个 第一组解决了
        //exchange ()
        ListNode* first = head;
        cout<<head->val<<endl;
        cout<<"n: "<<n<<endl;
        for(int i = 0; i <= n-k; i+=k){ // 这里i的最大值是n-k，因为要预留出k个循环里用到的值
            cout<<"exchange"<<endl;
            exchange(first, previous, k);
            // first 变成新的 tail，下组的previous
            previous = first;
            first = first->next;
        }
        p=minus1.next;
        while(p->next!=NULL){
            n++;
            cout << "!!"<<p->val<<endl;
            p=p->next;
        }
        return minus1.next;
    }
};
// @lc code=end

