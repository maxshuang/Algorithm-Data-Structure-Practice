/*
 * Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

Constraints:
1 <= s.length, p.length <= 3 * 104
s and p consist of lowercase English letters.
 */

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // we use a fixed-length window to slice s.
        // to compare the substring and p, we need a
        // map to simulate the anagrams
        map<char, int> need, window;
        for (char c : p) need[c]++;

        vector<int> res;
        int left=0, right=0;
        int valid=0;
        while(right<s.size()) {
            char c=s[right];
            if(need.count(c)) {
                ++window[c];
                // once we satisfy one condition, increase valid
                if(need[c]==window[c]){
                    ++valid;
                }
            }
            ++right;

            // this 'while' will maintain fix window
            while(right-left>=p.size()) {
                // when we reach the window size, check if the substring is a anagram of p
                if(valid==need.size()) {
                    res.push_back(left);
                }

                //shirnk left bound
                int c=s[left];
                if(need.count(c)){
                    // we break the condition again here
                    if(need[c]==window[c]){
                        --valid;
                    }
                    --window[c];
                }
                ++left;
            }
        }

        return res;
    }
};
