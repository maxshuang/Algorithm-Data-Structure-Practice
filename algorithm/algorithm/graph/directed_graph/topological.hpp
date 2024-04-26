#include "digraph.hpp"
#include "dag.hpp"

// Topological Sort is the abstract of precedence-contrained scheduling problem
class Topological
{
public:
    Topological(const Digraph &g) : marked_(g.V(), false), path_(g.V(), false), has_cycle_(false) { dfs(g); }
    bool IsDAG() const { return !has_cycle_; }
    std::vector<int> Order() const { return order_; }

private:
    void dfs(const Digraph &g)
    {
        for (int i = 0; i < g.V() && !has_cycle_; ++i)
        {
            if (!marked_[i])
                dfs_recur(g, i);
        }

        if (!has_cycle_)
            reverse_order();
        else
            order_.clear();
    }

    void dfs_recur(const Digraph &g, int v)
    {
        if (has_cycle_)
            return;

        marked_[v] = true;
        path_[v] = true;
        auto pair = g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      {
            if(has_cycle_) return;

            if(!marked_[e.Dest()]) {
                dfs_recur(g, e.Dest());
            }else if(path_[e.Dest()]) {
                has_cycle_=true;
            } });
        // reverse back
        path_[v] = false;
        // postorder traversal
        order_.push_back(v);
    }

    void reverse_order()
    {
        std::vector<int> tmp(order_.size());
        std::reverse_copy(order_.begin(), order_.end(), tmp.begin());
        order_.swap(tmp);
    }

private:
    std::vector<int> marked_;
    // cycle test
    std::vector<bool> path_;
    bool has_cycle_;
    // put the reverse postorder
    std::vector<int> order_;
};