#include <vector>
#include <string>
#include <algorithm>
#include "catch.hpp"
using namespace std;

#if 0

struct string_shallow {
    std::string::const_iterator st;
    std::string::const_iterator ed; 

    string_shallow(const std::string::const_iterator& st,
    const std::string::const_iterator& ed):st(st), ed(ed){}

    // we should return 1/-1/0 to indicate the real situation
    int compare(const string_shallow& rt) const{
        int d1=this->ed-this->st;
        int d2=rt.ed-rt.st;
        int min=std::min(d1, d2);
        for(int i=0; i<min; ++i) {
            if(*(this->st+i) < *(rt.st+i)) return 1;
            else if (*(rt.st+i) < *(this->st+i)) return -1;
        }

        if(d1<d2) return 1;
        else if(d2<d1) return -1;
        return 0;
    } 
};

// average log length: M
// total number of log: N
// Possible solution:
// exchange the digit-logs to end: O(N+M) + sort the letter-logs: O(NlogN*M)

struct Compare {
    bool operator()(const std::string& lf, const std::string& rt) const {
        auto iteLf = std::find(lf.begin(), lf.end(), ' ');
        auto iteRt = std::find(rt.begin(), rt.end(), ' ');

        int res = string_shallow(iteLf+1, lf.end()).compare(string_shallow(iteRt+1, rt.end()));
        if(res==1) {
            return true;
        }else if(res==-1) {
            return false;
        }
        
        return string_shallow(lf.begin(), iteLf).compare(string_shallow(rt.begin(), iteRt))>=0? true: false;
    }
};


class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        // exchange all digit logs to the end
        // keep the ordering
        int i=logs.size();
        for(int j=logs.size()-1; j>=0; --j) {
            if(isDigitLog(logs[j])) {
                std::swap(logs[j], logs[--i]);
            }
        }

        // sort the rest letter-log
        sortImpl(logs, 0, i);

        return logs;
    }

    bool isDigitLog(const std::string& log) {
        auto ite = std::find(log.begin(), log.end(), ' ');
        int c=*(ite+1)-'0';
        return c>=0 && c<=9? true: false; 
    }

    void sortImpl(vector<string>& logs, int i, int j) {
        Compare comp;
        std::sort(logs.begin()+i, logs.begin()+j, comp);
    }
};

#endif

// So delicated
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        stable_sort(logs.begin(), logs.end(), [&](const string & log1, const string & log2) {
            int pos1 = log1.find_first_of(" ");
            int pos2 = log2.find_first_of(" ");
            bool isDigit1 = isdigit(log1[pos1 + 1]);
            bool isDigit2 = isdigit(log2[pos2 + 1]);
            if (isDigit1 && isDigit2) {
                return false;
            }
            if (!isDigit1 && !isDigit2) {
                // [NOTE]: we can use self-defined string_view to optimize this cost
                string s1 = log1.substr(pos1);
                string s2 = log2.substr(pos2);
                if (s1 != s2) {
                    return s1 < s2;
                }
                return log1 < log2;
            }
            return isDigit1 ? false : true;
        });
        return logs;
    }
};

TEST_CASE("test reorder logs", "") {
    SECTION("1") {
        vector<string> logs{"zoey i love you","lucas i love you","rong i love you"};
        Solution sl;
        REQUIRE(sl.reorderLogFiles(logs)==vector<string>{"lucas i love you","rong i love you","zoey i love you"});
    }
}
