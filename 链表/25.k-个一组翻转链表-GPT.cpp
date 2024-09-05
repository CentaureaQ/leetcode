/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
 */

// @lc code=start
/** 
 * Definition for singly-linked list.*/
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

class Solution {
public:
    // 翻转以first为首的k个节点
    ListNode* reverseKNodes(ListNode* first, int k) {
        ListNode* prev = nullptr;
        ListNode* curr = first; // 1
        while (k--) {
            ListNode* nextNode = curr->next; //2
            curr->next = prev; //null 
            prev = curr; //prev=1
            curr = nextNode; //curr = 2
        }
        return prev;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1 || head == nullptr) {
            return head; // 当k为1或链表为空时，直接返回原链表
        }
        
        // 计算链表长度
        ListNode* p = head;
        int n = 0;
        while (p) {
            n++;
            p = p->next;
        }
        
        ListNode dummy(-1);
        dummy.next = head;
        ListNode* prevGroupEnd = &dummy;

        for (int i = 0; i <= n - k; i += k) {
            ListNode* groupStart = prevGroupEnd->next;
            ListNode* groupEnd = groupStart;
            for (int j = 1; j < k; j++) {
                groupEnd = groupEnd->next;
            }
            ListNode* nextGroupStart = groupEnd->next;

            // 翻转这一组的节点
            groupEnd->next = nullptr;
            prevGroupEnd->next = reverseKNodes(groupStart, k);
            groupStart->next = nextGroupStart;

            // 更新前一组的结尾节点
            prevGroupEnd = groupStart;
        }

        return dummy.next;
    }
};

// @lc code=end

