/*
 Given a string s, return the longest palindromic substring in s.

Constraints:
1 <= s.length <= 1000
s consist of only digits and English letters.
*/

/*
Solution:
Palindromic string has a special pattern: it's synmetric from the central point.
So we just need to treat every pos in original string as the central point and check whether it's Palindromic string.
Tricky things here: aba and abba has different Palindromic pattern.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
#include <string>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        std::string maxRes="";
        int size = s.size();
        for(int i=0; i<size; ++i) {
            std::string s1 = checkPalindrome(s, i, i);
            std::string s2 = checkPalindrome(s, i, i+1);
            maxRes = s1.size()>maxRes.size()?s1:maxRes;
            maxRes = s2.size()>maxRes.size()?s2:maxRes;
        }

        return maxRes;
    }

    std::string checkPalindrome(std::string s, int l, int r){
        while(l>=0 && r<s.size() && s[l]==s[r]) {
            --l;
            ++r;
        }
        return s.substr(l+1, r-l-1);
    }
};
