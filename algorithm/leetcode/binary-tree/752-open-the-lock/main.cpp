/*
 * You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.
The lock initially starts at '0000', a string representing the state of the 4 wheels.
You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.
Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

Constraints:
1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target will not be in the list deadends.
target and deadends[i] consist of digits only.
*/

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        // use hash table to record deads
        unordered_set<string> deads;
        for (string s : deadends) {
            deads.insert(s);
        }
        // record the visited
        unordered_set<string> visited;
        // it's the same as asking you the min-depth to reach the target
        queue<string> q;
        q.push("0000");
        int depth=0;
        while(q.size()!=0) {
            // bfs
            int size=q.size();
            for(int i=0; i<size; ++i) {
                string cur=q.front();
                q.pop();

                if(deads.count(cur)){
                    continue;
                }

                if(cur==target){
                    return depth;
                }

                for(int i=0; i<4; ++i) {
                    // for each position, we can backward or forward
                    for(int j=0; j<2; ++j) {
                        string newCur=cur;
                        if(j==0) {
                            // forward
                            if(newCur[i]=='9') {
                                newCur[i]='0';
                            }else {
                                ++newCur[i];
                            }
                        }else {
                            // backward
                            if(newCur[i]=='0') {
                                newCur[i]='9';
                            }else {
                                --newCur[i];
                            }
                        }
                        // check visited
                        if(visited.count(newCur)) {
                            continue;
                        }
                        visited.insert(newCur);
                        // bfs, add to queue
                        q.push(newCur);
                    }
                }
            }
            ++depth;
        }

        return -1;
    }
};

