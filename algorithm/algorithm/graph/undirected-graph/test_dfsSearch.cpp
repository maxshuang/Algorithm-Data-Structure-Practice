#include "dfsSearch.h"
#include <cassert>

int main() {
    UndirectedGraphWithoutWeight graph(6); // Create a graph with 6 vertices
    graph.AddEdge(0, 1); // Add edges
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);

    DfsSearch dfsSearch(graph, 0);

    // Check if all vertices are marked
    for (int i = 0; i < 6; i++) {
        assert(dfsSearch.Marked(i) == true);
    }

    // Check the count
    assert(dfsSearch.Count() == 6);
}
