/*
Trees Height Solution Amazon OA SDE There are N trees in Jon's backyard and height of tree i is h[i]. 
Jon doesn't like the appearance of it and is planning to increase and decrease the height of trees such that the new heights are in strictly increasing order. 
Every day he can pick one tree and increase or decrease the height by 1 unit. 
Heights can be o or even negative (it's a magical world). Jon has guests coming after X days, 
hence he wants to know if it is possible to make heights strictly increasing in no more than X days? 
Also See: Amazon OA Online Assessment 2021 Questions and Answers Input format: 
First line contains one integer N<=2000 number of trees, X<=5000 number of days Jon has. 
Second line contains N space separated integers where ith integer is h[i] Output Format: YES or NO, 
if it is possible to make tree heights in strictly ascending order in no more than X days, 
if YES, also print the number of days it will take. 
Sample Input 1: 
5 13 
54321 
Sample Output 1: YES 12 
Explanation: For the first sample the final array will look like 1 2 3 4 5 Hence the number of days required will be 12. 

Sample Input 2: 
7 10 
7 1 4 10 5 8 12 
Sample Output 2: NO
*/

/*
Possible solution:
quite interesting question, for a strictly increasing array, we can obeserve the origin array from the perspective of prefixSub array:
For example: 7 1 4 10 5 8 12  => 0, -6, 3, 6, -5, 3, 4

for strictly increasing array, the element preSub array should all be larger than 0, to minimize the changes,  
*/
#include <vector>

class Solution {
public:
    // greedy algorithm?
    int minChange(const std::vector<int>& trees, int limit) {

    }
};
