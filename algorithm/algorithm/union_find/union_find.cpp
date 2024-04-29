#include "union_find.h"

int UnionFind::Find(int x)
{
    // compress the path every time we find the root
    while (parent_[x] != x)
    {
        int p = parent_[x];
        parent_[x] = parent_[p]; // make x to be sibling of p
        x = p;
    }

    return x;
}

void UnionFind::Union(int x, int y)
{
    // Q1: it may produce a O(N) chain here
    // parent_[y]=x;
    // parent_[Find(y)] = Find(x);
    int p = Find(x);
    int q = Find(y);
    if (p == q)
        return;
    //parent_[q] = p;
    // heuristic: always attach the smaller tree to the larger tree
    /*
    if(size_[p]>size_[q]) {
        parent_[q]=p;
        size_[p]+=size_[q];
    }else {
        parent_[p]=q;
        size_[q]+=size_[p];
    }
    */
    // heuristic: always attach the shallower tree to the deeper tree
    if (depth_[p] > depth_[q])
    {
        parent_[q] = p;
        depth_[p] = std::max(depth_[p], depth_[q] + 1);
    }
    else
    {
        parent_[p] = q;
        depth_[q] = std::max(depth_[q], depth_[p] + 1);
    }
    
    connected_count_--;
}

bool UnionFind::Connected(int x, int y)
{
    return Find(x) == Find(y);
}

/*
int UnionFind::ConnectedCount()
{
    int count = 0;
    for (int i = 0; i < (int)parent_.size(); ++i)
    {
        if (parent_[i] == i)
        {
            count++;
        }
    }

    return count;
}
*/

int UnionFind::MaxDepth()
{
    int max_depth = 0;
    for (int i = 0; i < (int)depth_.size(); ++i)
    {
        max_depth = std::max(max_depth, depth_[i]);
    }

    return max_depth;
}