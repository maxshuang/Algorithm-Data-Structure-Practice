
/*
 *Implement the RandomizedSet class:
RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in average O(1) time complexity.

Constraints:
-2^31 <= val <= 2^31 - 1
At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
 */

class RandomizedSet {
    vector<int> inner;
    unordered_map<int, int> index;
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
    }

    bool insert(int val) {
        if(index.count(val)) {
            return false;
        }
        inner.push_back(val);
        index[val]=inner.size()-1;
        return true;
    }

    bool remove(int val) {
        if(!index.count(val)) {
            return false;
        }

        int last=inner[inner.size()-1];
        int idx=index[val];
        inner[idx]=last;
        index[last]=idx;
        index.erase(val);
        inner.pop_back();
        return true;
    }

    int getRandom() {
        return inner[rand()%inner.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */


