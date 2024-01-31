/*
 *Given an input string s, reverse the order of the words.
A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
Return a string of the words in reverse order concatenated by a single space.
Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

Constraints:
1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.
Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?
 */

class Solution {
public:
    // O(1) extra space
    string reverseWords(string s) {
        // in place reverse
        reverse(s.begin(), s.end());

        int n = s.size();
        int idx = 0;
        for (int start = 0; start < n; ++start) {
            if(s[start]!=' '){
                // append a space after word
                // append here we can make sure that
                // idx will point to the next char which needs to be erased
                if(idx!=0) s[idx++]=' ';

                int end=start;
                // move the word
                while(end<n&&s[end]!=' ') {
                    s[idx++]=s[end++];
                }
                // reverse the word
                reverse(s.begin()+idx-end+start, s.begin()+idx);
                start=end;
            }
        }

        // remove the remaining char
        s.erase(s.begin()+idx, s.end());
        return s;
    }

    // O(m) extra space
    string reverseWords2(string s) {
        vector<string> res;
        int left=0, right=0;
        // split
        while(right<s.size()) {
            while(left<s.size() && s[left]==' '){
                ++left;
            }
            right=left+1;
            while(right<s.size() && s[right]!=' '){
                ++right;
            }
            if(left<s.size()) {
                res.push_back(s.substr(left, right-left));
            }
            left=right+1;
        }

        // reverse append
        string ns;
        ns.reserve(s.size());
        for(int i=res.size()-1; i>=0; --i){
            ns.append(res[i]);
            ns.push_back(' ');
        }
        ns.pop_back();
        return ns;
    }
};
