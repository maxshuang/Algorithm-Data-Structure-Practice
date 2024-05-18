/*
 * There are n flights that are labeled from 1 to n.
You are given an array of flight bookings bookings, 
where bookings[i] = [first_i, last_i, seats_i] represents a booking for flights first_i through last_i (inclusive) with seats_i seats reserved for each flight in the range.
Return an array answer of length n, where answer[i] is the total number of seats reserved for flight i.

Constraints:
1 <= n <= 2 * 104
1 <= bookings.length <= 2 * 104
bookings[i].length == 3
1 <= firsti <= lasti <= n
1 <= seatsi <= 104
 */

#include <vector>

class Solution {
public:
    std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n) {
        std::vector<int> diff(n, 0);
        for(std::vector<int>& book: bookings) {
            diff[book[0]-1]+=book[2];
            // we can ignore diff[n]
            if(book[1]<n) {
                diff[book[1]]-=book[2];
            }
        }

        // subtle here
        for(int i=1; i<n; ++i){
            diff[i]+=diff[i-1];
        }

        return diff;
    }
};
