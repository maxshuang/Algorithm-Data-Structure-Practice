#include <iostream>
#include <vector>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // path compression
        }
        return parent[x];
    }

    void Union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }

    bool Connected(int x, int y) {
        return find(x) == find(y);
    }
};

int T;
int N;

void checkRestrictions() {
	std::cin >> N;
	int i,j,equality;
	UnionFind uf(100001);
	std::vector<std::pair<int, int>> checklists;
	while(N>0) {
	  	std::cin >> i >> j >> equality;

		if(equality==1) {
			uf.Union(i, j);	
		}else {
			checklists.push_back(std::pair<int, int>{i, j});
		}
	 --N;
	}
	
	for(auto& kv: checklists) {
		if(uf.Connected(kv.first, kv.second)) {
			std::cout << "NO" << std::endl;
			return;
		}
	}
	
	std::cout << "YES" << std::endl; 
}

int main() {
	std::cin >> T;
	while(T>0) {
		checkRestrictions();
		--T;
	}
	
	return 0;	
}