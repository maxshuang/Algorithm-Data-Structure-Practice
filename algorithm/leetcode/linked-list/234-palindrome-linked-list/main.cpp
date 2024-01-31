/*
 * Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

 Constraints:
The number of nodes in the list is in the range [1, 105].
0 <= Node.val <= 9

Follow up: Could you do it in O(n) time and O(1) space?
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
    bool isPalindrome(ListNode* head) {
        // O(N) time, O(1) space
        // reverse half link list and compare
        // slow + fast to get the medium node
        ListNode *slow=head, *fast=head;
        while(fast!=nullptr && fast->next!=nullptr) {
            slow=slow->next;
            fast=fast->next->next;
        }

        // reverse the latter half
        ListNode *cur=slow, *next=cur->next;
        while(next!=nullptr){
            ListNode *tmp=cur;
            cur=next;
            next=next->next;
            cur->next=tmp;
        }
        slow->next=nullptr;

        for(ListNode *p1=head, *p2=cur; p2!=nullptr; p1=p1->next, p2=p2->next){
            //cout << p1->val << "," << p2->val ;
            if(p1->val!=p2->val){
                return false;
            }
        }

        return true;
    }
};

class Solution {
    ListNode* left;
    int maxDepth;
    bool res;
public:
    bool isPalindrome(ListNode* head) {
        left=head;
        maxDepth=0;
        res=true;

        dfs(head, 0);
        return res;
    }

    void dfs(ListNode* head, int depth) {
        if(head==nullptr){
            return;
        }

        ++maxDepth;
        dfs(head->next, depth+1);

        if(depth<maxDepth/2){
            return;
        }

        if(left->val!=head->val) {
            res=false;
            return;
        }

        left=left->next;
        return;
    }
};
