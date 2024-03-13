#include <string.h>
#include <bits/stdc++.h>

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
        memset(slots, 0, sizeof(slots)); 
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

void rd(int& x) {
	x=0;int f=1;char ch=getchar();
	while (!isdigit(ch)) (ch=='-')&&(f=-1),ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;
}

void wt(int x) {
	(x<0)&&(x=-x,putchar('-'));
	if (x>9) wt(x/10);putchar(x%10^48);
}

void deDupData(int N) {
    data_set.clear();
    for(int i=0; i<N; ++i) {
        int tmp;
        rd(tmp);
        if(!data_set.add(tmp))
            wt(tmp);
            putchar(' ');
    }
    puts("");
}

int main()
{
    rd(T);
    for(int i=0; i<T; ++i) {
        rd(N);
        deDupData(N);
    }   

    return 0;
}