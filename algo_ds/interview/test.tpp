#define CATCH_CONFIG_MAIN
#include <iostream>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <memory> // For smart pointers
#include <queue>
#include <sys/time.h> // For gettimeofday
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <utility>
//#include <algorithm>
#include "catch.hpp"
using namespace std;

// determine: winner, voting system
// List<String> findWinner(List<Ballot> votes)
// Ballot: name of candidate, list<string>, may be not the same size, liimited to 3
// ten votes, up to three candidates, weight: [3, 2, 1]
// descending order at the total points 
// contrains: voters and candidates => int,  

// a easier： List<Ballot> votes
// candidate： candidate => array[3], {3, 2, 1} > {2, 3, 3}
// sort the array[3] in the descending
// define our own compare function: position*weight => total 

// => append 0 if we lack the exact vote at different position
//  no two candicates has the same vote

/*
finWinner => interface finWinner {
vector<string> findWinner(vector<vector<string>> votes) {}
}
class VoteManager {
private:
    vector<int> weight{3, 2, 1};
    finWinner* finder;
public:
    // strategy design pattern
    vector<string> findWinner(vector<vector<string>> votes)  {finder()}
};
*/

vector<int> weight{3, 2, 1};

auto cmp = [](const pair<string, vector<int>>& lf, const pair<string, vector<int>>& rt) {
    int lfw=0;
    int i=0;
    for(const int& v: lf.second) {
        lfw+=v*weight[i];
        ++i;
    }
    int rtw=0;
    i=0;
    for(const int& v: rt.second) {
        rtw+=v*weight[i];
        ++i;
    }

    return lfw>rtw;
};

// Basic algorithm: explaination
vector<string> findWinner(vector<vector<string>> votes) {
    unordered_map<string, vector<int>> voteMap;

    for(const vector<string>& vote: votes) {
        for(int i=0; i<vote.size() && i<3; ++i) {
            if(!voteMap.count(vote[i])) {
                voteMap.emplace(vote[i], vector<int>(3, 0));
                voteMap[vote[i]][i]=1;
            }else {
                ++voteMap[vote[i]][i];
            }
        }
    }

    std::vector<pair<string, vector<int>>> votesNew;
    for(auto iter=voteMap.begin(); iter!=voteMap.end(); ++iter) {
        votesNew.emplace_back(std::make_pair(iter->first, iter->second));
    }

    // default: ascending order
    std::sort(votesNew.begin(), votesNew.end(), cmp);

    std::vector<string> res;
    for(int i=0; i<3; ++i) {
        res.emplace_back(votesNew[i].first);
    } 
    return res;
}

TEST_CASE("Normal test", "[]")
{  
    /*
    {{"alina", "max"}, {"alina", "alina2", "max"}}
    {{}, {}, {}}
    {{"alina", "max", "max2", "xxxx"}, {"alina", "alina2", "max"}}}
    */
    vector<vector<string>> votes{{"alina", "max", "max2"}, {"alina", "alina2", "max"}};
    // alina: [2, 0, 0] => first win, 6
    // max: [0, 1, 1] => second win, 3
    // max2: [0, 0, 1] => , 1
    // alina2: [0, 1, 0] => third win 2
    SECTION("success") {
        REQUIRE(findWinner(votes)==vector<string>{"alina", "max", "alina2"});
    }
}