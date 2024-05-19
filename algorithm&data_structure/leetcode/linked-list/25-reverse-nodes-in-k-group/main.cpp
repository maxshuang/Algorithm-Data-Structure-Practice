/*
 * Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
k is a positive integer and is less than or equal to the length of the linked list. 
If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
You may not alter the values in the list's nodes, only nodes themselves may be changed.

Constraints:
The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000
 */

#include "../list.hpp"

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* p=head;
        int i=0;
        while(p!=nullptr && i<k){
            p=p->next;
            ++i;
        }
        if(i<k) {
            // less than k, do nothing
            return head;
        }

        // reverse the k-list from head
        ListNode *q=head, *t=head->next;
        for(int i=0; i<k-1; ++i){
            ListNode *tmp=q;
            q=t;
            t=t->next;
            q->next=tmp;
        }

        head->next=reverseKGroup(t, k);

        return q;
    }
};
