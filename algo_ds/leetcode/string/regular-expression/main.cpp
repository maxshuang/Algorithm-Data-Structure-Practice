#include <string>
#include "catch.hpp"
using namespace std;

// Part1: only have '.', just skip the '.'
class Solution0 {
public:
    bool isMatch(string s, string p) {
        if(s.size()!=p.size()) return false;

        for(size_t i=0; i<s.size(); ++i) {
            if('.'==p[i]) continue;
            else if(s[i]!=p[i]) return false;
        }

        return true;
    }
};

// Part2: have '.', may have digit after the '.'
// abcdd, a.3d
class Solution1 {
private:
    int getNum(const std::string& p, int st, int& ed) {
        int num=0;
        while(st<p.size() && isdigit(p[st])) {
            num=num*10+p[st]-'0';
            ++st;
        }

        ed=st;
        return num;
    }
public:
    bool isMatch(string s, string p) {
        int m=s.size(), n=p.size();
        int i=0, j=0;
        while(i<m && j<n) {
            if('.'==p[j]) {
                if(j+1<n && isdigit(p[j+1])) {
                    int ed=0;
                    i+=getNum(p, j+1, ed);;
                    j=ed;
                    continue;
                }
            }else if(s[i]!=p[j]) { 
                return false;
            }
            
            ++i;
            ++j;
        }

        return true;
    }
};

class Solution2 {
public:
    bool isMatch(string s, string p) {

    }
};

TEST_CASE("test match0", "") {
    Solution0 s0;
    REQUIRE(s0.isMatch("abc", "abc")==true);
    REQUIRE(s0.isMatch("abc", "ab.")==true);
    REQUIRE(s0.isMatch("abc", ".bc")==true);
    REQUIRE(s0.isMatch("abc", "a.c")==true);
    REQUIRE(s0.isMatch("abc", "...")==true);
    REQUIRE(s0.isMatch("abc", "ab")==false);
    REQUIRE(s0.isMatch("abc", "..")==false);
    REQUIRE(s0.isMatch("abc", "....")==false);
}