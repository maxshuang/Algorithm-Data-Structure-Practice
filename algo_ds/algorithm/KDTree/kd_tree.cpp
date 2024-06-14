#include <vector>
#include <functional>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// k-d tree is a special kind binary search tree, but with node as hyperplane in each layer

struct Point {
    std::vector<int> coords;
    int id;

    Point(const std::vector<int>& c, int id) : coords(c), id(id) {}

    bool operator<(const Point& other) const {
        return coords[0] < other.coords[0];
    }

    bool operator == (const Point& other) const {
        return this->coords==other.coords;
    }
};

struct KDNode {
    Point p;
    int axis;
    KDNode* left;
    KDNode* right;

    KDNode(Point p, int axis=0, KDNode* left=nullptr, KDNode* right=nullptr): p(p), axis(axis), left(left), right(right){}
};

class KDTree {
private:
    KDNode* tree;
    int curAxis;
    int axisCnt;

public:
    KDTree(std::vector<Point>& arr): tree(nullptr), curAxis(0), axisCnt(arr[0].coords.size()) {
        tree = divideRecur(arr, 0, arr.size()-1, curAxis);
    }

    ~KDTree(){
        // TODO delete all nodes
    }

    void Insert(const Point& p) {
        tree = insertRecur(p, tree, tree->axis);
    }

    // quite similar to binary search tree deletion
    // more complicated
    bool Delete(const Point& p) {
        return deleteRecur(p, tree, tree->axis);
    }

    std::vector<Point> GetTree() const {
        std::vector<Point> points;
        getTree(tree, points);

        return points;
    }

private:
    bool deleteRecur(const Point& p, KDNode*& root, int axis) {
        if(!root) return false; // miss

        // hit
        if(root->p==p) {
            if(!root->left && !root->right) {
                delete root;
                root=nullptr;
            }else if(!root->left) {
                KDNode* tmp=root;
                root=root->right;
                delete tmp;
            }else if(!root->right) {
                KDNode* tmp=root;
                root=root->left;
                delete tmp;
            }else {
                KDNode* successor = findMin(root->right, axis);
                // copy the data directly
                root->p=successor->p;
                // deal the right tree
                deleteRecur(successor->p, root->right, nextAxis(axis));
            }

            return true;
        }

        // dfs
        if(p.coords[axis] < root->p.coords[axis]) {
            return deleteRecur(p, root->left, nextAxis(axis));
        }

        return deleteRecur(p, root->right, nextAxis(axis));
    }

    // [NOTE]: we need to find the min node of the axis in subtree node
    KDNode* findMin(KDNode* node, int axis) {
        if(!node) return nullptr;
        
        // the smaller one could be at both children subtrees 
        if(node->axis != axis) {
            KDNode* lf=findMin(node->left, axis);
            KDNode* rt=findMin(node->right, axis);
            if(!lf && !rt) return node;
            else if(!lf) return rt;
            else if(!rt) return lf;
            else if(lf->p.coords[axis] < rt->p.coords[axis]) {
                // the root node may have the smallest value at axis
                return lf->p.coords[axis] < node->p.coords[axis]? lf: node;
            }
            return rt->p.coords[axis] < node->p.coords[axis]?rt:node;
        }

        KDNode* min=findMin(node->left, axis);
        return min? min: node;
    }

    KDNode* insertRecur(const Point& p, KDNode* root, int axis) {
        if(!root) return new KDNode(p, axis);

        if(p.coords[axis]<root->p.coords[axis]) {
            root->left=insertRecur(p, root->left, nextAxis(axis));
        }else {
            root->right=insertRecur(p, root->right, nextAxis(axis));
        }

        return root;
    }

    void getTree(KDNode* root, std::vector<Point>& points) const {
        if(!root) return;

        points.push_back(root->p);

        getTree(root->left, points);
        getTree(root->right, points);
    }

    KDNode* divideRecur(std::vector<Point>& points, int l, int r, int axis) {
        if(l>r) return nullptr;
        if(l==r) return new KDNode(points[l], axis);

        int mid = l+((r-l)>>1);
        // Find the medium and sort the range roughly
        // Time Complexity: O(N)
        // rearrange the vector so that n_element is at this position
        #if 0
        std::nth_element(points.begin()+l, points.begin()+mid, points.begin()+r+1,
                         [&axis](const Point& a, const Point& b) {
                             return a.coords[axis] < b.coords[axis];
                         });
        #endif
        nth_element(points, l, mid, r, axis);
        KDNode* root = new KDNode(points[mid], axis);

        // dfs: O(N)
        int nAxis=nextAxis(curAxis);
        root->left=divideRecur(points, l, mid-1, nAxis);
        root->right=divideRecur(points, mid+1, r, nAxis);   

        return root;
    }

    int nextAxis(int curAxis) {
        return (++curAxis)%axisCnt;
    }

    // The following implementation is for std::n_element
    void nth_element(std::vector<Point>& arr, int l, int n, int r, int axis) {
        int pt=-1;
        while(true) {
            pt=partition(arr, l, r, axis);
            if(pt==n) {
                break;
            }else if(pt<n) {
                l=pt+1;
            }else {
                r=pt-1;
            }
        }
    }

    int partition(std::vector<Point>& arr, int l, int r, int axis) {
        if(l>=r) return l;

        int pivot=selectPivot(arr, l, r, axis);
        // invariant: [l, i) <= pivot, [i, j) unknown, [j, r]>=pivot
        int i=l, j=r+1;
        while(true) {
            while(arr[++i].coords[axis]<pivot) if(i>=r) break;
            while(arr[--j].coords[axis]>pivot) if(j<=l) break;

            if(i>=j) break;
            std::swap(arr[i], arr[j]);      
        }

        std::swap(arr[l], arr[j]);

        return j;    // pivot point
    }

    int selectPivot(const std::vector<Point>& arr, int l, int r, int axis) {
        // [TODO]
        return arr[l].coords[axis];
    }
};

TEST_CASE("Test n_element", ""){
    std::vector<Point> points={
        {std::vector<int>{7, 2}, 1},
        {std::vector<int>{9, 6}, 2},
        {std::vector<int>{8, 1}, 3},
        {std::vector<int>{5, 4}, 4},
        {std::vector<int>{4, 7}, 5},
        {std::vector<int>{2, 3}, 6},
    };

    int m=2;
    std::nth_element(points.begin(), points.begin()+m, points.end(), 
                        [](const Point& a, const Point& b) {
                             return a.coords[0] < b.coords[0];
                        });
    std::vector<Point> res = {
        {std::vector<int>{2, 3}, 6},
        {std::vector<int>{4, 7}, 5},
        {std::vector<int>{5, 4}, 4},
        {std::vector<int>{7, 2}, 1},
        {std::vector<int>{8, 1}, 3},
        {std::vector<int>{9, 6}, 2},

    };
    REQUIRE(points==res);
}

TEST_CASE("Test K-Dimensional tree", "create/insert/delete") {
    std::vector<Point> points={
        {std::vector<int>{7, 2}, 1},
        {std::vector<int>{9, 6}, 2},
        {std::vector<int>{8, 1}, 3},
        {std::vector<int>{5, 4}, 4},
        {std::vector<int>{4, 7}, 5},
        {std::vector<int>{2, 3}, 6},
    };

    KDTree kdTree(points);

    /*
    //        <5, 4>
    //        /    \   
    //    <2, 3>   <7, 2>
    //        \    /     \
    //    <4, 7>  <8, 1>  <9, 6>
    */

   SECTION("create") {
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{9, 6}, 2},
        };
        REQUIRE(kdTree.GetTree()==res);
   }

    SECTION("insert1") {
        kdTree.Insert({std::vector<int>{4, 1}, 7});
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 1}, 7},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{9, 6}, 2},
        };
        REQUIRE(kdTree.GetTree()==res);
   }

    SECTION("insert2") {
        kdTree.Insert({std::vector<int>{4, 8}, 7});
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{4, 8}, 7},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{9, 6}, 2},
        };
        REQUIRE(kdTree.GetTree()==res);
   }

    SECTION("insert3") {
        kdTree.Insert({std::vector<int>{10, 7}, 8});
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{9, 6}, 2},
            {std::vector<int>{10, 7}, 8}
        };
        REQUIRE(kdTree.GetTree()==res);
   }

    SECTION("insert4") {
        kdTree.Insert({std::vector<int>{7, 1}, 8});
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{7, 1}, 8},
            {std::vector<int>{9, 6}, 2},        
        };
        REQUIRE(kdTree.GetTree()==res);
   }

    SECTION("delete non-existed node") {
        REQUIRE(kdTree.Delete({std::vector<int>{5, 4}, 4})==true);
        REQUIRE(kdTree.Delete({std::vector<int>{7, 2}, 1})==true);
        REQUIRE(kdTree.Delete({std::vector<int>{11, 2}, 1})==false);
        REQUIRE(kdTree.Delete({std::vector<int>{7, 20}, 1})==false);
    }

   SECTION("delete node with both children") {
        REQUIRE(kdTree.Delete( {std::vector<int>{5, 4}, 4})==true);
        std::vector<Point> res = {
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{9, 6}, 2},
            {std::vector<int>{8, 1}, 3},
        };
        REQUIRE(kdTree.GetTree()==res);

        REQUIRE(kdTree.Delete( {std::vector<int>{7, 2}, 1})==true);
        res = {
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{9, 6}, 2},
        };
        REQUIRE(kdTree.GetTree()==res);
   }

    SECTION("delete node without children") {
        REQUIRE(kdTree.Delete({std::vector<int>{4, 7}, 5})==true);
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            {std::vector<int>{2, 3}, 6},
            //{std::vector<int>{4, 7}, 5},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{9, 6}, 2},
        };
    }

    SECTION("delete node with one child") {
        REQUIRE(kdTree.Delete({std::vector<int>{2, 3}, 6})==true);
        std::vector<Point> res = {
            {std::vector<int>{5, 4}, 4},
            //{std::vector<int>{2, 3}, 6},
            {std::vector<int>{4, 7}, 5},
            {std::vector<int>{7, 2}, 1},
            {std::vector<int>{8, 1}, 3},
            {std::vector<int>{9, 6}, 2},
        };
    }
}