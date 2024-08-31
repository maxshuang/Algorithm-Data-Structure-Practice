#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

#define ASSERT_OR_PRINT(condition, message) \
  do {                                      \
      if(!(condition)) {                    \
         std::cerr << "assert fail:"        \
          << message << std::endl;          \
         assert((condition));               \
      }                                     \
  }while(0)


class Solution {
public:
    vector<string> rankTeams(vector<vector<string>>& votes) {
        unordered_map<string, vector<int>> vg;
        for(const auto& v: votes) {
          for(int i=0; i<v.size(); ++i) {
              --vg[v[i]][i]; // reversed order
          }
        }
        
        using PT=pair<string, vector<int>>;
        vector<PT> pairs;
        for(const auto& [k, v]: vg) pairs.emplace_back(PT(k, v));
        
        auto cmp=[](const PT& lf, const PT& rt){
            if(lf.second==rt.second) return lf.first<rt.first;
            return lf.second<rt.second;
        };
        
        // default for sort is increasing order, so here is decreasing order
        std::sort(pairs.begin(), pairs.end(), cmp);
        
        vector<string> res;
        for(const auto& p: pairs) res.emplace_back(p.first);
        return res;
    }
};

int main() {
    Solution sl;
    // Input: votes = ["ABC","ACB","ABC","ACB","ACB"]
    // Output: "ACB"
    vector<vector<string>> votes = {{"A", "B", "C"}, {"A", "C", "B"}, {"A", "B", "C"}, {"A", "C", "B"}, {"A", "C", "B"}};
    auto res1 = sl.rankTeams(votes);
    ASSERT_OR_PRINT((res1==vector<string>{"A", "C", "B"}), "normal case1");
    return 0;
}