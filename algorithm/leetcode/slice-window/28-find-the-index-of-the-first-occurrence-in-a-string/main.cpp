/*
 * Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

 Constraints:
1 <= haystack.length, needle.length <= 104
haystack and needle consist of only lowercase English characters.
 */

// kmp, Rabin-Karp, horspool, sunday algorithm
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (m < n) {
            return -1;
        }

        // pi is the longest prefix sub-string length
        // elegent
        vector<int> pi(m, 0);
        //s[pi[pi[j - 1]-1]-1]==s[pi[j - 1]-1]==s[j-1]==s[i-1]
        int j=0;
        // O(n) time complexity
        for(int i=1; i<n; ++i) {
            while(j>0 && needle[i]!=needle[j]) {
                j=pi[j-1];
            }
            if(needle[i]==needle[j]) {
                ++j;
            }
            pi[i]=j;
        }

        for(int i=0, j=0; i<m; ++i) {
            while(j>0 && haystack[i]!=needle[j]) {
                j=pi[j-1];
            }

            if(haystack[i]==needle[j]) {
                ++j;
            }
            if(j==n) {
                return i-n+1;
            }
        }

        return -1;
    }
};
