/*
 * There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).
You are given the integer capacity and an array trips where trips[i] = [numPassengers_i, from_i, to_i] indicates that 
the i_th trip has numPassengers_i passengers and the locations to pick them up and drop them off are from_i and to_i respectively. 
The locations are given as the number of kilometers due east from the car's initial location.
Return true if it is possible to pick up and drop off all passengers for all the given trips, or false otherwise.

Constraints:
1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengers_i <= 100
0 <= from_i < to_i <= 1000
1 <= capacity <= 105
 */

/*
Solution: M is the range of a trip, N is the count of trips
1. force algorithm: O(M*N), quite normal and natural solution
2. for range add operation, a technique is using difference array to transform it into O(1) operation => O(N).
Then for all locations, we can reconstruct the num of passenger by O(M).
Time Complexity: O(M+N)
*/

#include <vector>

class Solution {
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity) {
        // using difference array to reduce to O(m) time complexity
        // change the O(n) range operation to O(1) operation
        // Diff[i]=nums[i]-nums[i-1]
        std::vector<int> diff(1001, 0);
        for(std::vector<int> trip: trips) {
            diff[trip[1]]+=trip[0];
            diff[trip[2]]-=trip[0];
        }
        int sum=0;
        for(int d: diff) {
            sum+=d;
            if(sum>capacity){
                return false;
            }
        }

        return true;
    }
};

class Solution2 {
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity) {
        const int maxl=1001;
        std::vector<int> ps(maxl, 0);
        for(auto& t: trips) {
            // [numPassengers_i, from_i, to_i]
            int fr=t[1];
            int to=t[2];
            for(int i=fr; i<to; ++i) {
                ps[i]+=t[0];
            }
        }

        for(int i=0; i<1001; ++i) {
            if(ps[i]>capacity) return false;
        }

        return true;
    }
};
