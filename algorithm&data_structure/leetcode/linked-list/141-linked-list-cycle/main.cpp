/*
Given head, the head of a linked list, determine if the linked list has a cycle in it.
There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
Return true if there is a cycle in the linked list. Otherwise, return false.

Constraints:
1. The number of the nodes in the list is in the range [0, 104].
2. -105 <= Node.val <= 105
3. pos is -1 or a valid index in the linked-list.
 
Follow up: Can you solve it using O(1) (i.e. constant) memor
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
    bool hasCycle(ListNode *head) {
        // using slow/fast pointer to detect cycle
        ListNode *slow=head, *fast=head;
        while(fast!=NULL&&fast->next!=NULL) {
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast){
                return true;
            }
        }

        // fast pointer reach the end
        return false;
    }
   
    // Another interesting solution is to set the value to a specified 
    // value, so that we can detect the value to check out if we had visited the node before.
    // Set the node's next to itself has the same idea as this one.
    bool hasCycle2(ListNode *head) {
        while (head != NULL){
                if(head->val == 1000000) return true;
                head->val = 1000000;
                head = head->next;
            }
        return false;
    }
};
