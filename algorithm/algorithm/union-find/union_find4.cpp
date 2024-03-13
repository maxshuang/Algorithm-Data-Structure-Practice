#include <iostream>

// https://open.kattis.com/problems/almostunionfind
// Dynamic disjoint set
// Support element deletion and move


struct UnionFind {
    UnionFind() { clear(); }    
    
    int GetSize(int i) { return size_[find(i)]; }
    long long GetSum(int i) { return sum_[find(i)]; }

    void Union(int i, int j){
        int p=find(i);
        int q=find(j);
        if(p==q) return;
        
        father_[q]=p;
        size_[p]+=size_[q];
        sum_[p]+=sum_[q];
    }
    
    bool Connected(int i, int j){
        return find(i)==find(j);
    }
    
    void Move(int i, int j){
        int p=find(i);
        int q=find(j);
        if(p==q) return;

        // i is always the leaf node
        father_[i]=q;
        size_[p]--;
        size_[q]++;
        sum_[p]-=sum_[i];
        sum_[q]+=sum_[i];
    }

    void Delete(int i) {
        int p=find(i);
        father_[i]=i;
        size_[p]--;
        sum_[p]-=sum_[i];
    }
    
    int find(int i){
        // path compression
        if(father_[i]==i) return i;
        father_[i]=find(father_[i]);
        return father_[i];
    }
    
    void clear(){
        // normal node points to its virtual node
        for(int i=0; i<kSize; ++i) {
            father_[i]=i+kSize;
            size_[i]=1;
            sum_[i]=i;
        }
        // virtual node points to itself
        for(int i=kSize; i<2*kSize; ++i) {
            father_[i]=i;
            // already has a node attached to it
            size_[i]=size_[i-kSize];
            sum_[i]=sum_[i-kSize];
        }
    }

    static const int kSize=1e5+1;
    // node + virtual node
    int father_[2*kSize];
    int size_[2*kSize];
    long long sum_[2*kSize];
};

int main() {
    int N;
    int M;
    // [NOTE]: care for the input format
    while(!std::cin.eof()) {
        std::cin >> N >> M;
        UnionFind uf;
        while(M) {
            int op, l, r;
            std::cin >> op;
            if(op==1) {
                std::cin >> l >> r;
                uf.Union(l, r);
            }else if(op==2) {
                std::cin >> l >> r;
                uf.Move(l, r);
            }else {
                std::cin >> l;
                std::cout << uf.GetSize(l) << " " << uf.GetSum(l) << std::endl;
            }
            --M;
        }
    }
}