#include "trie.h"

Trie::~Trie(){
    removeAll(root);
}

void Trie::removeAll(Node* p) {
    if(p==nullptr) {
        return;
    }
    for(int i=0; i<26; ++i) {
        removeAll(p->next[i]);
    }
    // all children have been removed
    delete p;
}

void Trie::Insert(const char* str, int l){
    Node* p = root;
    for(int i = 0; i < l; i++){
        if(p->next[str[i] - 'a'] == nullptr){
            p->next[str[i] - 'a'] = new Node();
        }
        p = p->next[str[i] - 'a'];
    }
    p->isEnd = true;
}

void Trie::Insert(const std::string &str){
    Insert(str.c_str(), str.size());
}   

bool Trie::Search(const char* str, int l) const{
    Node* p=root;
    for(int i=0; i<l; ++i) {
        if(p->next[str[i]-'a']==nullptr) {
            return false;
        }
        p=p->next[str[i]-'a'];
    }
    return p->isEnd;
}

bool Trie::Search(const std::string& str) const{
    return Search(str.c_str(), str.size());
}

bool Trie::Remove(const char* str, int l) {
    bool isRemoved = false;
    return cascadingRemove(root, str, l, isRemoved);
}

bool Trie::Remove(const std::string& str) {
    return Remove(str.c_str(), str.size());
}

bool Trie::cascadingRemove(Node* p, const char* str, int l, bool& isRemoved) {
    // base condition
    isRemoved = false;
    if(p==nullptr) {
        return false;
    }
    if(l==0) {
        if(p->isEnd) {
            p->isEnd=false;
            if(isLeafNode(p)) {
                delete p;
                isRemoved = true;
            }
            return true;
        }
        return false;
    }

    // recursive condition
    // return true if the child node is removed
    bool issRemoved = false;
    if(cascadingRemove(p->next[str[0]-'a'], str+1, l-1, issRemoved)) {
        if(issRemoved) {
            p->next[str[0]-'a'] = nullptr;
            if(isLeafNode(p) && !p->isEnd) {
                delete p;
                isRemoved = true;
            }
        }
        return true;
    }
    return false;
}

bool Trie::isLeafNode(Node* p) const{
    for(int i=0; i<26; ++i) {
        if(p->next[i]!=nullptr) {
            return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////
// Trie2

Trie2::~Trie2() {
}

void Trie2::Insert(const char* str, int l) {
    int p = root;
    for(int i = 0; i < l; i++) {
        if(node[p][str[i]-'a']==-1) {
            node[p][str[i]-'a'] = count++;
        }
        p = node[p][str[i]-'a'];
    }
    isEnd[p] = true;
}

void Trie2::Insert(const std::string &str) {
    Insert(str.c_str(), str.size());
}

bool Trie2::Search(const char* str, int l) const {
    int p = root;
    for(int i = 0; i < l; i++) {
        if(node[p][str[i]-'a']==-1) {
            return false;
        }
        p = node[p][str[i]-'a'];
    }
    return isEnd[p];
}

bool Trie2::Search(const std::string& str) const {
    return Search(str.c_str(), str.size());
}