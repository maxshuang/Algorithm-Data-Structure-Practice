#include <cmath>
#include <iostream>
#include <list>
#include <vector>
#include <string>

typedef std::list<std::string> BlockList;

BlockList data;
std::string org_data;
int block_len=0;
int block_num=0;

void checkLimit(BlockList::iterator ite) {
    if(ite->size()<=2*block_len) return;
    // split
    data.insert(ite++, ite->substr(block_len, ite->size()-block_len));
    ite->erase(block_len);
}

void insert(char c, int p) {
    int sum=0;
    BlockList::iterator ite=data.begin();
    for(ite; ite!=data.end(); ++ite) {
        if(sum+ite->size()>p) {
            ite->insert(p-sum-1, 1, c);
            checkLimit(ite);
            return;
        }
        sum+=ite->size();
    }
    data.back().push_back(p);
}

char query(int p) {
    int sum=0;
    BlockList::iterator ite=data.begin();
    for(ite; ite!=data.end(); ++ite) {
        if(sum+ite->size()>p) {
            return (*ite)[p-sum-1];
        }
        sum+=ite->size();
    }
}

int main() {
   std::cin >> org_data;
   block_len=(int)std::sqrt(org_data.size());
   block_num=(org_data.size()+block_len-1)/block_len; // round up
   for(int i=0; i<block_num; ++i) {
      data.push_back(org_data.substr(i*block_len, block_len));
   }
   
   int N=0;
   std::cin >> N;
   while(N) {
    char op; std::cin >> op;
    if(op=='I') {
        char c; int p; std::cin >> c >> p;
        insert(c, p);
    }else if(op=='Q') {
        int p; std::cin >> p;
        std::cout << query(p) << std::endl;
    }
    --N;
   }
}