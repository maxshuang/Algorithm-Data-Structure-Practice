// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/quadtrees.pdf

// QuadTree divides the 2-dimension space into four parts evenly untill 


struct Point {
    static const int dims=4;
    int coords[dims];
};

struct QuadNode {
    Point p;
    QuadNode* lu;  // left + up
    QuadNode* ld;  // left + down
    QuadNode* ru;  // right + up
    QuadNode* rd;  // right + down
};