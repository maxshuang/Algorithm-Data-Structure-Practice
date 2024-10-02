#pragma once

class BST {
private:
    struct Node {
        int key;
        int value;
        //Node* parent;
        Node* left;
        Node* right;
        int size;

        Node(int key, int value): key(key), value(value), left(nullptr), right(nullptr), size(1) {};
        //Node(int key, int value, Node* parent, Node* left, Node* right): key(key), value(value), parent(parent), left(left), right(right), size(1) {};
    };
public:
    //BST():Node(-1, -1, nullptr, this, this){};
    BST():root_(nullptr){};
    ~BST();
    // insert a new node and return the new Node*
    Node* Put(int key, int value);
    // delete a node and return the next valid Node*
    Node* Delete(int key);
    // set a new value to a node and return the Node*
    Node* Set(int key, int value);
    // get a node by key
    Node* Get(int key);
    // get the minimum node
    Node* Min();
    // get the maximum node
    Node* Max();
    // delete the minimum node and return the deleted Node*
    Node* DeleteMin();
    // delete the maximum node and return the deleted Node*
    Node* DeleteMax();
    // get the node with the smallest key that is greater than or equal to the given key
    Node* LowerBound(int key);
    // get the node with the largest key that is less than or equal to the given key
    Node* UpperBound(int key);
    // get the node with the smallest key that is greater than or equal to the given key
    Node* Ceiling(int key);
    // get the largest node with the key less than or equal to the given key
    Node* Floor(int key);
    int Rank(int key);
    Node* Select(int rank);
    //std::pair<Node*, Node*> RangeQuery(int low, int high);
    //int RangeSize(int low, int high);
    int Size();
    bool Empty();
    void Clear();

private:
    Node* put_recur(Node* node, Node** find, int key, int value);
    Node* put_loop(int key, int value);
    Node* delete_recur(Node* node, Node** find, int key);
    Node* delete_loop(int key);
    Node* min_recur(Node* node);
    Node* max_recur(Node* node);
    Node* delete_min_recur(Node* node, Node** find);
    Node* delete_max_recur(Node* node, Node** find);
    Node* delete_min_loop(Node* node, Node** find);
    Node* delete_max_loop(Node* node, Node** find);
    Node* ceiling_recur(Node* node, int key);
    Node* floor_recur(Node* node, int key);
    Node* upper_bound_recur(Node* node, int key);
    Node* lower_bound_recur(Node* node, int key);
    int rank_recur(Node* node, int key);
    Node* select_recur(Node* node, int rank);


private:
    Node* root_;
};