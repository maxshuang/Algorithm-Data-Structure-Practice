/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.
Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 
Follow up: Could you do this in one pass?
 * */

/*
Solution:
1. Scan the list and find out the length, the find the reserve-N element
2. Use double point to move the reverse-N element
3. Use stack to get the reverse-N element
*/

#include "../list.hpp"

class Solution {
public:
    // Time Complexity: O(N), Space Complexity: O(1)
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(-1, head);
        ListNode *pre=&dummy, *cur=head;
        // need move pre to the reverse-n+1 node
        while(n>0) {
            cur=cur->next;
            --n;
        }

        // move cur to nullptr, so that pre points to the reverse-n+1 node
        while(cur) {
            cur=cur->next;
            pre=pre->next;
        }

        pre->next=pre->next->next;

        return dummy.next;
    }

    // another solution is to use recursive to location the nth node
    // from end
    // Time Complexity: O(N), Space Complexity: O(N)
    int cur=0;
    ListNode* removeNthFromEnd2(ListNode* head, int n) {
       if(!head) return nullptr;
       head->next = removeNthFromEnd(head->next,n);
       // recursive is from the end
       cur++;
       if(n==cur) return head->next;
       return head;
    }
};
