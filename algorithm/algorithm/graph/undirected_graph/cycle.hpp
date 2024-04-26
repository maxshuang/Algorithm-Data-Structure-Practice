#include <vector>
#include "undirected_graph.h"

class Cycle {
public:
    Cycle(const UndirectedGraph& graph): marked_(graph.V(), false), edge_to_(graph.V(), -1), has_cycle_(false){ dfs(graph); }
    bool HasCycle() const { return has_cycle_; }
    std::vector<int> GetCycle() const { return cycle_; }

private:
    void dfs(const UndirectedGraph& g){
        for(int i=0; i<g.V(); ++i) {
            if(!has_cycle_ && !marked_[i]) {
                edge_to_[i]=i;
                // source ans destination is itself
                dfs_recur(g, i, i);
                edge_to_[i]=-1;
            }
        }
    }
    void dfs_recur(const UndirectedGraph& g, int from, int to) {
        if(has_cycle_) return;

        marked_[to]=true;
        auto pair = g.Adj(to);
        std::for_each(pair.first, pair.second, [&](const Edge& e){
            if(has_cycle_) return;

            if(!marked_[e.Dest()]) {
                edge_to_[e.Dest()]=e.Src();
                dfs_recur(g, e.Src(), e.Dest());
                edge_to_[e.Dest()]=-1;
            }else if(from != e.Dest()){
                // undirected graph has a cycle here
                has_cycle_=true;
                // construct a cycle
                edge_to_[e.Dest()]=e.Src();
                get_cycle(e.Src());
            }
        });
    }

    void get_cycle(int v) {
        cycle_.push_back(v);
        int w=v;
        while(edge_to_[w] != v) {
            cycle_.push_back(edge_to_[w]);
            w=edge_to_[w];
        }
    }

private:
    // 无向图的成环检测有点难呀，因为边是双向的，有点区分不开环和双向边
    // 实现思路错了，无向图需要排除双向边即可。比有向图要难一点。
    // for dfs
    std::vector<int> marked_;
    std::vector<int> edge_to_;
    std::vector<int> cycle_;
    bool has_cycle_;
};