/*
 Given a string s, return the longest palindromic substring in s.

Constraints:
1 <= s.length <= 1000
s consist of only digits and English letters.
*/

class Solution {
public:
    string longestPalindrome(string s) {
        string maxRes="";
        int size = s.size();
        for(int i=0; i<size; ++i) {
            string s1 = checkPalindrome(s, i, i);
            string s2 = checkPalindrome(s, i, i+1);
            maxRes = s1.size()>maxRes.size()?s1:maxRes;
            maxRes = s2.size()>maxRes.size()?s2:maxRes;
        }

        return maxRes;
    }

    string checkPalindrome(string s, int l, int r){
        while(l>=0 && r<s.size() && s[l]==s[r]) {
            --l;
            ++r;
        }
        return s.substr(l+1, r-l-1);
    }
};
