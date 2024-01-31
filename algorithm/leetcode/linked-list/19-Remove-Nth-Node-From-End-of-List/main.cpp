/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.
Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 
Follow up: Could you do this in one pass?
 * */

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // use a dummy head to alleviate the corner case
        ListNode *dummy = new ListNode(-1, head);
        // 1. we use step point to get the (n+1)th node from end
        ListNode *p=dummy, *step=dummy;
        for(int i=0; i<n+1; i++) {
            step=step->next;
        }
        while(step!=NULL) {
            p=p->next;
            step=step->next;
        }
        // 2. remove the nth node from end
        p->next=p->next->next;

        return dummy->next;
    }

    // another solution is to use recursive to location the nth node
    // from end
    int cur=0;
    ListNode* removeNthFromEnd2(ListNode* head, int n) {
       if(!head) return NULL;
       head->next = removeNthFromEnd(head->next,n);
       // recursive is from the end
       cur++;
       if(n==cur) return head->next;
       return head;
    }
};
