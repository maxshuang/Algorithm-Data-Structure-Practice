#include <iostream>
#include <vector>
#include <unordered_map>

struct UnionFind{	
	void Union(int i, int j) {
		if(i==j) return;
		
		int p=find(i);
		int q=find(j);
		if(p && p==q) return;
		if(!p) { father_[i]=i; p=i; }
		if(!q) { father_[j]=j; q=j; }
		father_[p]=q;
	}
	
	bool Connected(int i, int j){
		if(i==j) return true;
		
        int p=find(i);
		int q=find(j);
		if(p && p==q) return true;
		return false;		
	}

	int find(int i) {
		int fa=findFather(i);
        if(fa==0) return 0;

        if(fa==i) return i;
        father_[i]=find(fa);
		return father_[i];
	}

    // we can add the node if it does not exist
    int findFather(int i) {
        auto ite = father_.find(i);
		if(ite==father_.end()) return 0;
        return ite->second;
    }
	
	void Clear() {
		father_.clear();
	}

    // index => father index
	std::unordered_map<int, int> father_;
};

int T;
int N;

void checkRestrictions() {
	std::cin >> N;
	int i,j,equality;
	UnionFind uf;
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