// 强联通分量是有向图中一个非常有意思的结构，它把整个图划分成不同的 components
// 不同 components 之间形成 DAG，而 component 内部是互相联通的节点集合
// 感觉可以做一些有效的压缩
//
// 不管是有环图还是无环图，一次 O(V+E) 的遍历都可以遍历所有节点
// 但是从任意节点开始是无法获取到内部的联通关系的，需要根据 postorder 顺序 traversal
// 但是内部有环，无法构造 topological order 怎么办？ 
// 应该这样理解，有环的话 reverse postorder traversal result 就不是一个 topological order
//
// 要解决这个问题，需要能获取到一个正确的访问次序，一个有效的方法应该是 reverse graph, 这样在 topological order 排在最后的点
// 就可以通过 dfs reverse postorder 获得。

//Remarkably, the implementation KosarajuSCC on the facing page does the job with just a few lines of code 
//added to CC, as follows:
//* Given a digraph G, use DepthFirstOrder to compute the reverse postorder of 
//its reverse, G R.
//* Run standard DFS on G, but consider the unmarked vertices in the order just 
//computed instead of the standard numerical order. 
//* All vertices reached on a call to the recursive dfs() from the constructor are in a 
//strong component (!), so identify them as in CC

#include <algorithm>
#include "digraph.hpp"


class StronglyComponent {
public:
    StronglyComponent(const Digraph& g): marked_(g.V(), false), id_(g.V(), 0), count_(0){ 
        // first: get reverse postorder traversal result of reverse graph 
        std::vector<int> reverse_order(g.V());
        dfs_reverse_graph(g, reverse_order);
        // second: traverse the origin graph according to the reverse_order
        dfs_graph(g, reverse_order);
    }
    bool StronglyConnected(int v, int w) const{ return id_[v]==id_[w]; }
    int Count() const{ return count_; }
    int ID(int v)const { return id_[v]; }

private:
    void dfs_reverse_graph(const Digraph& g, std::vector<int>& reverse_order) {
        Digraph reverse_g=g.Reverse();
        std::vector<int> post_order;
        dfs(reverse_g, post_order);
        std::reverse_copy(post_order.begin(), post_order.end(), reverse_order.begin());
    }

    void dfs(const Digraph& g, std::vector<int>& post_order) {
        for(int i=0; i<g.V(); ++i) {
            if(!marked_[i]) {
                dfs_recur(g, i, post_order);
            }
        }
    }

    void dfs_recur(const Digraph& g, int v, std::vector<int>& post_order) {
        marked_[v]=true;
        auto pair=g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge& e){
            if(!marked_[e.Dest()]) {
                dfs_recur(g, e.Dest(), post_order);
            }
        });

        // post order traversal
        post_order.push_back(v);
    }

    void dfs_graph(const Digraph& g, const std::vector<int>& reverse_order) {
        std::fill(marked_.begin(), marked_.end(), false);
        for(int i: reverse_order) {
            if(!marked_[i]) {
                // a new strongly connected component here
                ++count_;
                dfs_recur(g, i);
            }
        }
    }

    void dfs_recur(const Digraph& g, int v) {
        marked_[v]=true;
        // all nodes in a strongly connected component will be reachable to each other
        id_[v]=count_;
        
        auto pair=g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge& e){
            if(!marked_[e.Dest()]) {
                dfs_recur(g, e.Dest());
            }
        });
    }

private:
    std::vector<bool> marked_;
    std::vector<int> id_;
    int count_;
};