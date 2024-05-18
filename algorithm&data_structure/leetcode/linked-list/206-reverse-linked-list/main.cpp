/*
 *Given the head of a singly linked list, reverse the list, and return the reversed list.

 Constraints:
The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000
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
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr) return nullptr;

        ListNode *i=head, *j=head->next;
        while(j!=nullptr){
            ListNode* tmp=i;
            i=j;
            j=j->next;
            i->next=tmp;
        }
        head->next=nullptr;
        return i;
    }
};
