/*
 * Given a string s, find the length of the longest substring without repeating characters.

 Constraints:
0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
 */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // s consists of English letters, digits, symbols and spaces.
        vector<bool> dict(256, false);

        int maxLength=0;

        int left=0, right=0;
        // we maintain a window to deal substring
        while(right<s.size()) {
            // enlarge right entill we meet a repeating characters
            if(!dict[int(s[right])]) {
                dict[int(s[right])] = true;
                ++right;
                continue;
            }

            // update maxLength
            maxLength=max(maxLength, right-left);

            // enlarge left entill we delete the repeating characters
            dict[int(s[left])] = false;
            ++left;
        }

        maxLength=max(maxLength, right-left);
        return maxLength;
    }
};
