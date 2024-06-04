/*
 *The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
For example, "ACGAATTCCG" is a DNA sequence.
When studying DNA, it is useful to identify repeated sequences within the DNA.
Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.

Constraints:
1 <= s.length <= 105
s[i] is either 'A', 'C', 'G', or 'T'.
 */

class Solution {
    const int L=10;
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if(s.size()<L) return vector<string>();

        unordered_map<char, int> dict{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
        unordered_map<int, int> subMap;
        vector<string> rr;

        // use 0-3 to represent the DNA element, so we can put 10-letter-long DNS sequence to int, and achieve compare string in O(1) time complexity
        // x= (x<<2 | dict(s[i])) & (1<<20-1)
        int x=0;
        for(int i=0; i<L; ++i){
            x= (x<<2 | dict[s[i]]);
        }
        subMap[x]++;

        for(int i=1; i<s.size()-L+1; ++i) {
            x= (x<<2 | dict[s[i+L-1]]) & ((1<<20)-1);
            subMap[x]++;
            if(subMap[x]==2){
                rr.push_back(s.substr(i, 10));
            }
        }

        return rr;
    }
};
