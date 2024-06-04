/*
You are given the heads of two sorted linked lists list1 and list2.
Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
Return the head of the merged linked list.

Constraints:

The number of nodes in both lists is in the range [0, 50].
-100 <= Node.val <= 100
Both list1 and list2 are sorted in non-decreasing order.
*/

#include "../list.hpp"

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // The benefits of the recursive:
        // 1: it can be solved by a smaller problem
        // 2: we can get a father/children node directly

        // base case
        if(list1==nullptr) {
            return list2;
        }else if (list2==nullptr) {
            return list1;
        }

        // recursive
        ListNode* head=nullptr;
        if(list1->val<=list2->val) {
            head=list1;
            head->next=mergeTwoLists(list1->next, list2);
        }else{
            head=list2;
            head->next=mergeTwoLists(list1, list2->next);
        }

        return head;
    }

    // another solution is compare the node in two lists one by one
    ListNode* mergeTwoLists2(ListNode* list1, ListNode* list2) {
        // When we need a new list, create a dummy head is quiet useful to allivate the corner case
        // dummy head
        ListNode dummy, *p = &dummy;
        ListNode *p1=list1, *p2=list2;
        while(p1!=nullptr && p2!=nullptr) {
            if(p1->val > p2->val) {
                p->next = p2;
                p2 = p2->next;
            }else {
                p->next = p1;
                p1 = p1->next;
            }

            p=p->next;
        }

        // left
        if(p1==nullptr) {
            p->next = p2;
        }else {
            p->next = p1;
        }

        return dummy.next;
    }
};
