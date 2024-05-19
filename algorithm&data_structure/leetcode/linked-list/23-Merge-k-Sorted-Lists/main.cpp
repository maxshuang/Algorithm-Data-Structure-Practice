/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Constraints:

k == lists.length
0 <= k <= 104
0 <= lists[i].length <= 500
-104 <= lists[i][j] <= 104
lists[i] is sorted in ascending order.
The sum of lists[i].length will not exceed 104.
*/

#include <vector>
#include <queue>
#include <functional>
#include "../list.hpp"

class Solution {
public:
    // divide and merge
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        return mergeMany(lists, 0, lists.size()-1);
    }

    ListNode* mergeMany(std::vector<ListNode*>& lists, int start, int end){
        //base case
        if(start>end) return nullptr;
        if(start==end) return lists[start];
        // divide
        int mid=(start+end)>>1;
        return mergeTwo(mergeMany(lists, start, mid), mergeMany(lists, mid+1, end));
    }

    ListNode* mergeTwo(ListNode* list1, ListNode* list2){
        ListNode dummy, *p=&dummy;
        ListNode *p1=list1, *p2=list2;
        while(p1&&p2){
            if(p1->val>p2->val){
                p->next=p2;
                p2=p2->next;
            }else {
                p->next=p1;
                p1=p1->next;
            }
            p=p->next;
        }
        if(!p1) {
            p->next=p2;
        }
        if(!p2) {
            p->next=p1;
        }
        return dummy.next;
    }

    // another solution is using a priority queue to sort the nodes
    ListNode* mergeKLists2(std::vector<ListNode*>& lists) {
        // using priority queue to get the smallest node
        std::priority_queue<ListNode*, std::vector<ListNode*>, std::function<bool(ListNode*, ListNode*)>> pq(
        [] (ListNode* a, ListNode* b) { return a->val > b->val; });
        // dummy head
        ListNode *dummy=new ListNode(-1), *p=dummy;
        // init pq by all lists' head
        for(auto head: lists) {
            if(head) pq.push(head);
        }

        while(!pq.empty()){
            // insert top node to list and pop
            ListNode* top=pq.top();
            pq.pop();
            p->next=top;
            p=p->next;
            if(top->next) pq.push(top->next);
        }

        return dummy->next;
    }
};
