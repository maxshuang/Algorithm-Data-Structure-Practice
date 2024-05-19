/*
 *Given the head of a singly linked list and two integers left and right where left <= right, 
reverse the nodes of the list from position left to position right, and return the reversed list.

Constraints:
The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 */

#include "../list.hpp"
#include "catch.hpp"

class Solution {
public:
    // Space Complexity: O(1)
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(-1, head);
        ListNode *pre=&dummy, *cur=head, *last=head;
        for(int i=1; i<left; ++i) {
            pre=pre->next;
            cur=cur->next;
        }
        for(int i=1; i<right+1; ++i) {
            last=last->next;
        }

        // reverse the [cur, last)
        ListNode *pp=pre, *cc=cur, *ll=last;
        ListNode *nxt;
        while(cc!=ll) {
            nxt=cc->next;
            cc->next=pp;
            pp=cc;
            cc=nxt;
        }
        // rebuild the list
        pre->next = pp; 
        cur->next = last;

        return dummy.next;
    }

    // Space Complexity: O(N)
    ListNode* reverseBetween2(ListNode* head, int left, int right) {
        ListNode dummy(-1, head);
        ListNode *pre=&dummy, *cur=head, *last=head;
        for(int i=1; i<left; ++i) {
            pre=pre->next;
            cur=cur->next;
        }
        for(int i=1; i<right+1; ++i) {
            last=last->next;
        }

        pre->next=reverse_recur(cur, last);
        cur->next=last;
        
        return dummy.next;
    }

    // reverse the list from cur to last, [cur, last)
    ListNode* reverse_recur(ListNode* cur, ListNode* last) {
        if(!cur|| cur->next==last) return cur;

        ListNode* new_head=reverse_recur(cur->next, last);
        cur->next->next=cur;
        cur->next=nullptr;
        return new_head;
    }
};

TEST_CASE("Test reverseBetween", "") {
    ListNode* head=new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    
    #if 1
    SECTION("reverseBetween") {
        Solution sl;
        sl.reverseBetween(head, 2, 4);

        ListNode* cur=head;
        REQUIRE(cur->val==1);
        cur=cur->next;
        REQUIRE(cur->val==4);
        cur=cur->next;
        REQUIRE(cur->val==3);
        cur=cur->next;
        REQUIRE(cur->val==2);
        cur=cur->next;
        REQUIRE(cur->val==5);
    }
    #endif

    SECTION("reverseBetween") {
        Solution sl;
        sl.reverseBetween2(head, 2, 4);

        ListNode* cur=head;
        REQUIRE(cur->val==1);
        cur=cur->next;
        REQUIRE(cur->val==4);
        cur=cur->next;
        REQUIRE(cur->val==3);
        cur=cur->next;
        REQUIRE(cur->val==2);
        cur=cur->next;
        REQUIRE(cur->val==5);
    }
}