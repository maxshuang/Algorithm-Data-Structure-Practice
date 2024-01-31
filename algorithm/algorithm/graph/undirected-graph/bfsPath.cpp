#include <queue>
#include "bfsPath.h"

BfsPaths::BfsPaths(UndirectedGraphWithoutWeight G, int s): marked(G.V(), false), edgeTo(G.V(), -1), source(s) {
    if (s < 0 || s >= G.V()) return;
    bfs(G, s);
}

bool BfsPaths::HasPathTo(int v) const {
    if(v < 0 || v >= (int)this->marked.size()) return false;
    return this->marked[v];
}

std::vector<int> BfsPaths::PathTo(int v) const {
    std::vector<int> path;
    if(!HasPathTo(v)) return path;

    for(int x = v; x != this->source; x = this->edgeTo[x]) {
        path.push_back(x);
    }
    path.push_back(this->source);
    return path;
}

void BfsPaths::bfs(UndirectedGraphWithoutWeight G, int v) {
    std::queue<int> q;
    this->marked[v] = true;
    q.push(v);
    while (!q.empty()) {
        // for a queue, we use front() to get the first element and pop() to remove it
        // to avoid "pop" throw out some exceptions 
        int x = q.front();
        q.pop();
        for (const Edge& w : G.Adj(x)) {
            if (!this->marked[w.Dest()]) {
                this->edgeTo[w.Dest()] = x;
                this->marked[w.Dest()] = true;
                q.push(w.Dest());
            }
        }
    }
}