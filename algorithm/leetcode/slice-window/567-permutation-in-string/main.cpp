/*
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.

Constraints:
1 <= s1.length, s2.length <= 104
s1 and s2 consist of lowercase English letters.
 */

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> need, window;
        for(char c: s1){
            ++need[c];
        }

        int left=0, right=0;
        // 'valid' is based on the fact that the anagrams of s2 has the same length as s2, so the nums of each char must the same as s2.
        int valid=0;
        while(right<s2.size()) {
            char c=s2[right];
            if(need.count(c)) {
                ++window[c];
                if(need[c]==window[c]){
                    ++valid;
                }
            }
            ++right;

            while(right-left>=s1.size()) {
                if(valid==need.size()) {
                    return true;
                }

                char c=s2[left];
                if(need.count(c)) {
                    if(need[c]==window[c]){
                        --valid;
                    }
                    --window[c];
                }
                ++left;
            }
        }

        return false;
    }
};
