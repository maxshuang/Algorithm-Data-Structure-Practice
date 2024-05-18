/*
 *Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

 Constraints:
The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
       ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;
        ListNode *pre = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }

        ListNode *newTail=pre->next;
        //reverse the list
        ListNode *cur=pre->next;
        ListNode *next=cur->next;
        int steps=right-left;
        for (int i = 0; i < steps; ++i) {
            ListNode* tmp=cur;
            cur=next;
            next=next->next;
            cur->next=tmp;
        }
        pre->next=cur;
        newTail->next=next;

        return dummyNode->next;
    }
};
