#include <queue>
#include "bfs_path.h"

BfsPaths::BfsPaths(const UndirectedGraph& G, int s): marked_(G.V(), false), edge_to_(G.V(), -1), source_(s) {
    if (s < 0 || s >= G.V()) return;
    bfs(G, s);
}

bool BfsPaths::HasPathTo(int v) const {
    if(v < 0 || v >= (int)this->marked_.size()) return false;
    return this->marked_[v];
}

std::vector<int> BfsPaths::PathTo(int v) const {
    std::vector<int> path;
    if(!HasPathTo(v)) return path;

    for(int x = v; x != this->source_; x = this->edge_to_[x]) {
        path.push_back(x);
    }
    path.push_back(this->source_);
    return path;
}

void BfsPaths::bfs(const UndirectedGraph& G, int v) {
    std::queue<int> q;
    this->marked_[v] = true;
    q.push(v);
    while (!q.empty()) {
        // for a queue, we use front() to get the first element and pop() to remove it
        // to avoid "pop" throw out some exceptions 
        int x = q.front();
        q.pop();
        for (const Edge& w : G.Adj(x)) {
            if (!this->marked_[w.Dest()]) {
                this->edge_to_[w.Dest()] = x;
                this->marked_[w.Dest()] = true;
                q.push(w.Dest());
            }
        }
    }
}