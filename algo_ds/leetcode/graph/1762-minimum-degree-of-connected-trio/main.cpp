#include <vector>
#include <iostream>
#include <set>
#include "catch.hpp" 
using namespace std;

// For a sparse graph, M << N^2

// Wrong: DFS can't get all cycles
// Possible solution:
// M is the edge num, N is the vertice num
// 1. O(N) DFS to detect the trio cycle with only three node, DFS here can't find all the cycles in the graph
// 2. O(3*N), for every trio, traverse the edge list of its node and count the
// edge which is not in the trio total Time Complexity: O(3*N*N) total Space
// Space Complexity: O(M) for the graph

#if 0
class Solution {
    static const int MAX = 160005;
    int cnt;
    typedef vector<int> EdgeList;
    vector<EdgeList> graph;
    vector<bool> visited;
    vector<int> prePath; // for cycle detection
    int minDegree;

public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        init(n);
        buildGraph(edges);
        // multiple cc
        for (int i = 1; i < cnt + 1; ++i) {
            dfs(i, 0);
        }

        return minDegree != MAX ? minDegree : -1;
    }

    void init(int n) {
        graph.clear();
        visited.clear();
        prePath.clear();
        cnt = n;
        graph.resize(n + 1);
        visited.resize(n + 1, false);
        prePath.resize(n + 1, -1);
        minDegree = MAX;
    }

    void buildGraph(vector<vector<int>>& edges) {
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
    }

    void dfs(int n, int fa) {
        if (prePath[n] != -1) {
            // build a cycle here
            std::set<int> cycle;
            buildCycle(n, fa, cycle);
            // trio here
            if(cycle.size()== 3) calculateTrioDegree(n, cycle);
            return;
        }

        if (visited[n])
            return;

        visited[n] = true;
        prePath[n] = fa;
        // traverse the all the edges
        for (auto i : graph[n]) {
            if(i != fa) dfs(i, n);
        }

        // revert back
        prePath[n] = -1;
    }

    void buildCycle(int n, int fa, std::set<int>& cycle) {
        cycle.insert(n);
        int i=fa;
        while(i!=n) {
            cycle.insert(i);
            i=prePath[i];
        }
    }

    void calculateTrioDegree(int n, const set<int>& cycle) {
        int degree = 0;
        for(int i: cycle) {
            for(int vi: graph[i]) {
                if(cycle.count(vi)==0) ++degree;
            }
        }

        if (degree < minDegree) {
            minDegree = degree;
        }
    }
};
#endif

// For dense graph
// Using Adjacent Matrix to quickly check the connected trio
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n, vector<int>(n));
        vector<int> degree(n);

        for (auto&& edge: edges) {
            int x = edge[0] - 1, y = edge[1] - 1;
            g[x][y] = g[y][x] = 1;
            ++degree[x];
            ++degree[y];
        }

        int ans = INT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (g[i][j] == 1) {
                    for (int k = j + 1; k < n; ++k) {
                        if (g[i][k] == 1 && g[j][k] == 1) {
                            ans = min(ans, degree[i] + degree[j] + degree[k] - 6);
                        }
                    }
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

// Sparse graph, 直接使用序号约束节点遍历顺序的话，在第二轮遍历中复杂度只在 O(M/2) 这个级别
// Time Complexity: O(N+ M*M)
// Space Complexity: O(M)
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> graph(n+1);
        
        for (const vector<int>& edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        
        int ans = INT_MAX;
        for (int i = 1; i <= n; i++) {
            const unordered_set<int>& neighbors = graph[i];
            int tmp_a = graph[i].size() - 2;
            if (tmp_a >= ans) {
                continue;
            }
            for (int b : neighbors) {
                int tmp_b = tmp_a + graph[b].size() - 2;
                if (b < i || tmp_b >= ans) {
                    continue;
                }
                for (int c : graph[b]) {
                    if (neighbors.count(c) > 0) {
                        ans = min(ans, tmp_b + (int)graph[c].size() - 2);
                    }
                } 
            }
        }
        
        return ans == INT_MAX? -1 : ans;
    }
};



TEST_CASE("test trio cycle", "") {
    SECTION("1") {
        vector<vector<int>> edges{{1,2},{1,3},{3,2},{4,1},{5,2},{3,6}};
        Solution sl;
        REQUIRE(sl.minTrioDegree(6, edges)==3);
    }

    SECTION("2") {
        vector<vector<int>> edges{{1,3},{4,1},{4,3},{2,5},{5,6},{6,7},{7,5},{2,6}};
        Solution sl;
        REQUIRE(sl.minTrioDegree(7, edges)==0);
    }

    SECTION("3") {
        vector<vector<int>> edges{{6,5},{4,3},{5,1},{1,4},{2,3},{4,5},{2,6},{1,3}};
        Solution sl;
        REQUIRE(sl.minTrioDegree(7, edges)==3);
    }
}

// 这个度导致的方向性为什么会对遍历是有帮助的？？ 这个直觉非常有意思, 并且第二层遍历复杂度下降这么快？ 不知道直觉是什么
// 
// 这个算法的 intuition 非常难以理解，只能说按照度数将无向图转成有向图之后，可以有效减少三元组的遍历个数
// 由于无向图被转成了有向图，所以第一次遍历所有的边 [i, j] 复杂度为 O(M)
// 而根据第一条边遍历点的出边 [j, k] 时，按照有向边的定义，所有点的出边都不可能超过 \sqrt(2M) => O(\sqrt(M))
// 而 [i, k] 的连通性可以使用 hash table 以 O(1) 实现
// 所以总的时间复杂度是： O(N+M*\sqrt(M)), 其中 N 是第一个外层循环的次数，但不是 multiple 的关系，因为 sparse graph 大部分点是不进行内层循环的
// Space Complexity: O(M)

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        // 原图
        vector<unordered_set<int>> g(n);
        // 定向后的图
        vector<vector<int>> h(n);
        vector<int> degree(n);

        for (auto&& edge: edges) {
            int x = edge[0] - 1, y = edge[1] - 1;
            g[x].insert(y);
            g[y].insert(x);
            ++degree[x];
            ++degree[y];
        }
        for (auto&& edge: edges) {
            int x = edge[0] - 1, y = edge[1] - 1;
            if (degree[x] < degree[y] || (degree[x] == degree[y] && x < y)) {
                h[x].push_back(y);
            }
            else {
                h[y].push_back(x);
            }
        }

        int ans = INT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j: h[i]) {
                for (int k: h[j]) {
                    if (g[i].count(k)) {
                        ans = min(ans, degree[i] + degree[j] + degree[k] - 6);
                    }
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
