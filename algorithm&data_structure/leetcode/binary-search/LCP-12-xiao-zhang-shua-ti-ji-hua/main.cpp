/*
 *为了提高自己的代码能力，小张制定了 LeetCode 刷题计划，他选中了 LeetCode 题库中的 n 道题，编号从 0 到 n-1，
并计划在 m 天内按照题目编号顺序刷完所有的题目（注意，小张不能用多天完成同一题）。
在小张刷题计划中，小张需要用 time[i] 的时间完成编号 i 的题目。
此外，小张还可以使用场外求助功能，通过询问他的好朋友小杨题目的解法，可以省去该题的做题时间。
为了防止“小张刷题计划”变成“小杨刷题计划”，小张每天最多使用一次求助。
我们定义 m 天中做题时间最多的一天耗时为 T（小杨完成的题目不计入做题总时间）。请你帮小张求出最小的 T 是多少。

限制：
1 <= time.length <= 10^5
1 <= time[i] <= 10000
1 <= m <= 1000
 */

/*
The relationship of cost time per day and total days is monotonic, non-increasing. [min(time), sum(time)]
*/


#include <vector>
#include <algorithm>

class Solution {
public:
    int minTime(std::vector<int>& time, int m) {
        int mini=0, sum=0;
        for(int t: time){
            mini=std::min(mini, t);
            sum+=t;
        }

        int start=mini, end=sum;
        while(start<=end){
            int mid=start+(end-start)/2;
            if(check(time, m, mid)) {
                end=mid-1;
            }else {
                start=mid+1;
            }
        }

        return start;
    }

    bool check(std::vector<int>& time, int m, int cap) {
        // maxi is used to save the maximum one, don't add it to the sum
        int split=1, sum=0, maxi=0;
        for(int i=0; i<time.size(); ++i) {
            int next=std::min(maxi, time[i]);
            if(next+sum<=cap) {
                sum+=next;
                maxi=std::max(maxi, time[i]);
                continue;
            }

            // hold maxi so that we can ease the corner cases significantly
            ++split;
            sum=0;
            // i_th element doesn't be dealed last time
            maxi=time[i];
        }

        return split<=m;
    }
};
