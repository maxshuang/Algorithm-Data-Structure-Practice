#include "BST.h"

BST::~BST()
{
    Clear();
}

BST::Node* BST::Put(int key, int value)
{
    // return put_loop(key, value);
    BST::Node* find=nullptr;
    root_ = put_recur(root_, &find, key, value);

    return find;
}

BST::Node* BST::put_recur(BST::Node *node, BST::Node** find, int key, int value)
{
    if (node == nullptr)
    {
        *find = new BST::Node(key, value);
        return *find;
    }

    if (node->key == key)
    {
        *find=node;
        node->value = value;
    }
    else if (node->key > key)
    {
        node->left = put_recur(node->left, find, key, value);
    }
    else
    {
        node->right = put_recur(node->right, find, key, value);
    }

    return node;
}

BST::Node* BST::put_loop(int key, int value)
{
    if (root_ == nullptr)
    {
        root_= new BST::Node(key, value);
        return root_;
    }

    BST::Node *pp = nullptr;
    BST::Node *p = root_;
    bool isLeft = false;
    while (p)
    {
        if (p->key == key)
        {
            p->value = value;
            return p;
        }
        else if (p->key < key)
        {
            pp = p;
            p = p->right;
            isLeft = false;
        }
        else
        {
            pp = p;
            p = p->left;
            isLeft = true;
        }
    }

    BST::Node *new_node = new BST::Node(key, value);
    if (isLeft)
        pp->left = new_node;
    else
        pp->right = new_node;

    return new_node;
}

BST::Node *BST::Set(int key, int value)
{
    return Put(key, value);
}

BST::Node *BST::Get(int key)
{
    BST::Node *p = root_;
    while (p)
    {
        if (p->key == key)
            return p;
        else if (p->key < key)
            p = p->right;
        else
            p = p->left;
    }

    return nullptr;
}

BST::Node* BST::Delete(int key)
{
    BST::Node* find=nullptr;
    root_ = delete (root_, &find, key);
    return find;
}

// return next valid node
BST::Node* BST::delete_recur(BST::Node *node, BST::Node** find, int key)
{
    if (node == nullptr)
        return nullptr;

    if (node->key == key)
    {
        if (node->left == nullptr)
        {
            BST::Node *right = node->right;
            delete node;
            *find=right;
            return right;
        }
        else if (node->right == nullptr)
        {
            BST::Node *left = node->left;
            delete node;
            *find=left;
            return left;
        }
        else
        {
            BST::Node *right_most = max_recur(p->left);
            // copyable??
            node->key = right_most->key;
            node->value = right_most->value;
            // trick is here, delete_max will return the right node after delete
            node->left=delete_max_recur(p->left);
            *find=node;
            return node;
        }
    }
    else if (node->key < key)
    {
        return delete_recur(node->right, find, key);
    }

    return delete_recur(node->left, find, key);
}

BST::Node *BST::Min()
{
    return min_recur(root_);
}

BST::Node *BST::min_recur(BST::Node *node)
{
    if (node == nullptr)
        return nullptr;

    BST::Node *p = node;
    while (p->left)
        p = p->left;

    return p;
}

BST::Node *BST::Max()
{
    return max_recur(root_);
}

BST::Node *BST::max_recur(BST::Node *node)
{
    if (node == nullptr)
        return nullptr;

    BST::Node *p = node;
    while (p->right)
        p = p->right;

    return p;
}

BST::Node *BST::LowerBound(int key)
{
    return ceiling_recur(root_, key);
}

BST::Node *BST::UpperBound(int key)
{
    return upper_bound_recur(root_, key);
}

BST::Node *BST::upper_bound_recur(BST::Node *node, int key)
{
    if (node == nullptr)
        return nullptr;

    if (node->key <= key)
        return upper_bound_recur(node->right, key);

    // if all the keys in the left subtree are not larger than key, then the root is the upper bound
    BST::Node *p = upper_bound_recur(node->left, key);
    if (p)
        return p;

    return node;
}

BST::Node *BST::Ceiling(int key)
{
    return ceiling_recur(root_, key);
}

BST::Node *BST::ceiling_recur(BST::Node *node, int key)
{
    if (node == nullptr)
        return nullptr;

    if (node->key == key)
        return node;
    else if (node->key > key)
    {
        BST::Node *p = ceiling_recur(node->left, key);
        if (p)
            return p;

        return node; // if all keys in the left subtree are smaller than key, then the root is the ceiling
    }

    return ceiling_recur(node->right, key); // definitely in the right subtree
}

BST::Node *BST::Floor(int key)
{
    return floor_recur(root_, key);
}

BST::Node *BST::floor_recur(BST::Node *node, int key)
{
    if (node == nullptr)
        return nullptr;

    if (node->key == key)
        return node;
    else if (node->key < key)
    {
        BST::Node *p = floor_recur(node->right, key);
        if (p)
            return p;

        return node; // if all keys in the right subtree are larger than key, then the root is the floor
    }

    return floor_recur(node->left, key); // definitely in the left subtree
}

/*
int BST::RankWrong(int key)
{
    BST::Node *p = LowerBound(key);
    // all keys are smaller than key or is the smallest one
    if (p == nullptr || p->left == nullptr)
        return 0;

    // count is only the node num of its own left and right subtree
    return p->left->size;
}
*/

int BST::Rank(int key)
{
    return rank_recur(root_, key);
}

int BST::rank_recur(BST::Node *node, int key)
{
    if (node == nullptr || node->left == nullptr)
        return 0;

    if (node->key == key)
        return node->left.size;
    else if (node->key < key)
        return 1 + node->left.size + rank_recur(node->right, key);

    return rank_recur(node->left, key);
}

BST::Node *BST::Select(int rank)
{
    return select_recur(root_, rank);
}

BST::Node *BST::select_recur(BST::Node *node, int rank)
{
    if (node == nullptr || node->left == nullptr)
        return nullptr;

    if (node->left.size == rank)
        return node;
    else if (node->left.size < rank)
        return select_recur(node->right, rank - node->left.size - 1);

    return select_recur(node->left, rank);
}

void BST::DeleteMin()
{
    root_ = delete_min_recur(root_);
}

// return the right node after delete
BST::Node *BST::delete_min_recur(BST::Node *node)
{
    if (node == nullptr)
        return nullptr;

    // min node is the leftmost node
    if (node->left == nullptr)
    {
        BST::Node *right = node->right;
        delete node;
        return right;
    }

    node->left = delete_min_recur(node->left);
    return node;
}

BST::Node *BST::delete_min_loop(BST::Node *root)
{
    if (root == nullptr)
        return nullptr;

    // delete root
    if (root->left == nullptr)
    {
        BST::Node *right = root->right;
        delete root;
        return right;
    }

    BST::Node *pp = root;
    BST::Node *p = pp->left;
    while (p)
    {
        pp = p;
        p = p->left;
    }
    pp->left = p->right;
    delete p;
    return root;
}

void BST::DeleteMax()
{
    root_ = delete_max_recur(root_);
}

BST::Node *BST::delete_max_recur(BST::Node *node)
{
    if (node == nullptr)
        return nullptr;

    // max node is the rightmost node
    if (node->right == nullptr)
    {
        BST::Node *left = node->left;
        delete node;
        return left;
    }

    node->right = delete_max_recur(node->right);
    return node;
}

BST::Node *BST::delete_max_loop()
{
    if (root_ == nullptr)
        return nullptr;

    // delete root
    if (root_->right == nullptr)
    {
        BST::Node *left = root_->left;
        delete root;
        return left;
    }

    BST::Node *pp = root;
    BST::Node *p = pp->right;
    while (p)
    {
        pp = p;
        p = p->right;
    }
    pp->right = p->left;
    delete p;
    return root;
}

int BST::Size(){
    return 0;
}

bool BST::Empty() {
    return root_ == nullptr;
}

void BST::Clear(){}