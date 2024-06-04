/*
 *Given the head of a singly linked list, reverse the list, and return the reversed list.

 Constraints:
The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000
 */

#include "../list.hpp"

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

    // recursive is the stack
    ListNode* reverseList2(ListNode* head) {
        if(!head || !head->next) return head;

        ListNode* new_head=reverseList2(head->next);
        head->next->next=head;
        head->next=nullptr;
        return new_head;
    }

    ListNode* reverseList3(ListNode* head) {
        if(head==nullptr) return nullptr;

        ListNode dm(-1, head);
        ListNode *pre=&dm, *cur=head;
        ListNode *nxt;
        while(cur!=nullptr){
            nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }
        
        head->next=nullptr;
        return pre;
    }
};
