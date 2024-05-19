/**
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Constraints:
The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200
 *
 */

#include "../list.hpp"

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *dummy = new ListNode(-1, head);
        ListNode *p1 =dummy, *p2=head;

        while(p1->next!=nullptr && p2->next!=nullptr) {
            // move p1 to the last node whose val is less than x
            if(p1->next->val<x){
                p1=p1->next;
                continue;
            }
            // skip the small node from beginning and move p2 to the last node whose val is greater than or equal to x
            if(p2->val<x || p2->next->val>=x){
                p2=p2->next;
                continue;
            }

            //exchange position
            ListNode* tmp = p2->next;
            p2->next = p2->next->next;
            tmp->next = p1->next;
            p1->next = tmp;
        }
        return dummy->next; 
    }

    ListNode* partition2(ListNode* head, int x) {
      // similar to merge two lists, we firstly split the entire list into two lists, then merge them
      ListNode *smaller = new ListNode(-1), *p1=smaller;
      ListNode *larger = new ListNode(-1), *p2=larger;

      ListNode *p = head;
      while(p!=nullptr) {
          // link node to specified list
          if(p->val<x) {
              p1->next = p;
              p1=p1->next;
          }else {
              p2->next=p;
              p2=p2->next;
          }

          // get next p and cut the origin p
          ListNode* tmp=p;
          p=p->next;
          tmp->next=nullptr;
      }

      // link smaller's tail to the larger's head
      p1->next=larger->next;
      return smaller->next;
    }
};
