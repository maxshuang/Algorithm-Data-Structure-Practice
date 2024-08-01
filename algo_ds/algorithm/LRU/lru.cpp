#include <unordered_map>

class LRU {
public:
    LRU(int cap);
    ~LRU();
    int get(int key);
    void set(int key, int val);
private:
    struct Item {
        int key;
        int val;
        Item* pre;
        Item* nxt;

        Item(): pre(nullptr), nxt(nullptr){}
        Item(int k, int v, Item *p, Item *n): key(k), val(v), pre(p), nxt(n){}
    };

    void adjust(Item* it);
    
    int cap;
    int cnt;
    Item head;
    Item *tail;
    std::unordered_map<int, Item*> mapInner;
};

LRU::LRU(int cap):cap(cap), cnt(0), end(nullptr){
}

LRU::~LRU(){
    // TODO：release
}

int LRU::get(int key) {
    if(!mapInner.count(key)) {
        // throw error
        return -1;
    }

    Item* it=mapInner[key];
    adjust(it);

    return it->val;
}

void LRU::set(int key, int val) {
    if(mapInner.count(key)) {
        adjust(mapInner[key]);
        mapInner[key]=val;
        return;
    }

    Item* nit= new Item(key, val, nullptr, nullptr);
    
    // set tail if tail is nullptr
    if(!tail) tail=nit; 

    // insert into the list head
    nit->nxt=head.nxt;
    if(cnt>0) head.nxt->pre=it;
    head.nxt=it;
    ++cnt;

    // check if overflow, if so, remove the last one
    if(cnt>cap) {
        Item* tmp=tail;
        tail=tail->pre;   // [TODO] tail may point to head here
        tail->nxt=nullptr;
        mapInner.erase(tmp->key);
        delete tmp;
        --cnt;
    }
} 

void LRU::adjust(Item* it) {
    if(cnt<=1 && it->pre==&head) return;

    if(it==tail) tail=it->pre;

    // move from previous pos    
    it->pre->nxt=it->nxt;
    if(it->nxt) it->nxt->pre=it->pre;

    // add to head
    it->nxt=head.nxt;
    head.nxt->pre=it;
    head.nxt=it;
}