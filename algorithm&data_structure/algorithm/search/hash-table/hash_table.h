#pragma once
#include <vector>
#include <new>
#include <stddef.h>
#include <cmath>
#include <algorithm>

template<class Key, class Value, class Hash=std::hash<Key>, class KeyEqual=std::equal_to<Key>>
class HashTable
{
public:
    struct Node
    {
        int key;
        int value;
        Node *next;
        Node(int key, int value) : key(key), value(value), next(nullptr){};
    };

public:
    HashTable() : slots_(kSize, nullptr), size_(0), capacity_(kSize), max_load_factor_(0.75){};
    void Put(int key, int value);
    // Q1: how to deal with the case that the key does not exist?
    // A1: two interfaces, 1. int at(int key), check the bound, throw exception; 2. int Get(int key), insert if not exists
    int Get(int key);
    void Delete(int key);
    bool IsEmpty() const;
    size_t Size() const;
    void Clear();
    float LoadFactor() const{ return (float)size_/capacity_; }

private:
    // Q5: how to generize the hash and equal function? 
    int hashFunc(int key) const;
    void rehash();

    static const int kSize = 13;
    std::vector<Node *> slots_;
    size_t size_;
    // Q3: how to choose a better capacity_? prime number?
    size_t capacity_;
    // Q2: rehash
    float max_load_factor_; // if size_/capacity_ > factor_, then enlarge and rehash
};