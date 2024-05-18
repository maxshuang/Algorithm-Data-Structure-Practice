/*
 * Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
The testcases will be generated such that the answer is unique.
 
Constraints:
m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
*/

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        for(char c:t){
            ++need[c];
        }

        int left=0, right=0;
        int valid=0;
        int minWin=s.size()+1;
        int resLeft=0, resRight=0;
        while(right<s.size()) {
            int c=s[right];
            if(need.count(c)) {
                ++window[c];
                if(need[c]==window[c]) {
                    ++valid;
                }
            }
            ++right;
            // enlarge right bound entill we meet the requirement
            if(valid!=need.size()) {
                continue;
            }

            // shrink left bound
            while(valid==need.size()) {
                // update minWindow
                int curWin=right-left;
                if(minWin>curWin){
                    minWin=curWin;
                    resLeft=left;
                    resRight=right;
                }

                int c=s[left];
                if(need.count(c)) {
                    if(need[c]==window[c]) {
                        --valid;
                    }
                    --window[c];
                }
                ++left;
            }
        }

        return minWin!=s.size()+1?s.substr(resLeft, resRight-resLeft):"";
    }
};
