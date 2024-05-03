#include <algorithm>
#include <iterator>
#include "digraph.hpp"

class DirectReversePost {
public:
    DirectReversePost(const Digraph& g): marked_(g.V(), false) { 
        for(int i=0; i<g.V(); ++i){
            if(!marked_[i])
                dfs(g, i);
        }

        std::reverse_copy(post_order_.begin(), post_order_.end(), std::back_inserter(reverse_post_order_));
    } 
    
    std::vector<int> ReversePostOrder() const { return reverse_post_order_; }
    std::vector<int> PostOrder() const { return post_order_; }

private:
    void dfs(const Digraph& g, int v) {
        marked_[v]=true;
        auto pair=g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge& e){
            if(!marked_[e.Dest()]) {
                dfs(g, e.Dest());
            }
        });

        post_order_.push_back(v);
    }

private:
    std::vector<bool> marked_;
    std::vector<int> post_order_;
    std::vector<int> reverse_post_order_;
};