#include <iostream>
#include <string.h>

struct HashSet {
    struct Node {
        int key;
        int next;
    };

    HashSet():next_node(0) { clear();  }
    bool get(int key) 
    { 
        int slot = index(key);
        for(int p=slots[slot]; p; p=node_pool[p].next) {
            if(node_pool[p].key==key) return true;
        }
        return false;
    }
    
    void set(int key) { 
        int slot = index(key);
        for(int p=slots[slot]; p; p=node_pool[p].next) {
            if(node_pool[p].key==key) return;
        }
        ++next_node;
        node_pool[next_node].key=key;
        node_pool[next_node].next=slots[slot];
        slots[slot]=next_node;
    }

    bool add(int key) { 
        int slot = index(key);
        for(int p=slots[slot]; p; p=node_pool[p].next) {
            if(node_pool[p].key==key) return true;
        }
        ++next_node;
        node_pool[next_node].key=key;
        node_pool[next_node].next=slots[slot];
        slots[slot]=next_node;
        return false;
    }
    
    void clear() { 
        memset(slots, 0, sizeof(slots)*sizeof(int)); 
        next_node=0;    
    }
    
    int index(int key) { 
        return (key%kSize+kSize)%kSize;
    }
    
    static const int kSize=50021;
    int slots[kSize];
    Node node_pool[kSize];
    int next_node;
};

int T;
int N;
HashSet data_set;


void deDupData(int N) {
    data_set.clear();
    for(int i=0; i<N; ++i) {
        int tmp;
        std::cin >> tmp;
        if(!data_set.add(tmp))
            std::cout << tmp << " ";
    }
    std::cout << std::endl;
}


int main()
{
    std::cin >> T;
    for(int i=0; i<T; ++i) {
        std::cin >> N;
        deDupData(N);
    }   

    return 0;
}