/**
Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.

Constraints:
The number of nodes of listA is in the m.
The number of nodes of listB is in the n.
1 <= m, n <= 3 * 104
1 <= Node.val <= 105
0 <= skipA < m
0 <= skipB < n
intersectVal is 0 if listA and listB do not intersect.
intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
 

Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 1. The core idea of solution is when we merge two lists but
        // reverse them respectively, we will meet at the intersection node at last.
        // merge two lists when reverse
        ListNode *p1=headA, *p2=headB;
        while(p1!=p2){
            // reverse list1, if reaches end, then reverse list2
            if(p1!=NULL){
                p1=p1->next;
            }else {
                p1=headB;
            }

            // reverse list2, if reaches end, then reverse list1
            if(p2!=NULL){
                p2=p2->next;
            }else {
                p2=headA;
            }

            if(p1==p2){
                return p1;
            }
        }

        return p1;
    }

    // another solution is to link the last node of one list to the head node
    // of the other list. So that we can translate this problem to detect whether
    // there is a loop in linked list
};
