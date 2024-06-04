#pragma once
#include <string>

class Trie{
public:
    Trie(){ root = new Node();};
    ~Trie();
    void Insert(const char* str, int l);
    void Insert(const std::string &str);
    bool Search(const char* str, int l) const;
    bool Search(const std::string& str) const;
    bool Remove(const char* str, int l);
    bool Remove(const std::string& str);
private:
    struct Node{
        bool isEnd;
        Node* next[26];
        Node(){
            isEnd = false;
            for(int i = 0; i < 26; i++){
                next[i] = nullptr;
            }
        }
    };
    // can use lazy delete, only delete the leaf node
    bool cascadingRemove(Node* p, const char* str, int l, bool& isRemoved);
    void removeAll(Node* p);
    bool isLeafNode(Node* p) const;
private:
    Node* root;
};


class Trie2{
public:
    Trie2():count(1), root(0){
        for(int i = 0; i < 100; i++){
            isEnd[i] = false;
            for(int j = 0; j < 26; j++){
                node[i][j] = -1;
            }
        }
    }
    ~Trie2();
    void Insert(const char* str, int l);
    void Insert(const std::string &str);
    bool Search(const char* str, int l) const;
    bool Search(const std::string& str) const;
    //bool Remove(const char* str, int l);
    //bool Remove(const std::string& str);
private:
    //bool cascadingRemove(Node* p, const char* str, int l, bool& isRemoved);
    //void removeAll(Node* p);
    //bool isLeafNode(Node* p) const;
private:
    // better locality of reference
    int count;
    int node[100][26];
    bool isEnd[100];
    int root;
};

/*
对于算法题，可以使用更紧凑的实现，更简单直接
leetcode pattern:

struct trie {
  // more compact implementation
  int nex[100000][26], cnt;
  // could use bitmap for more compact implementation, but need more computation
  bool exist[100000];  // 该结点结尾的字符串是否存在

  void insert(char *s, int l) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) nex[p][c] = ++cnt;  // 如果没有，就添加结点
      p = nex[p][c];
    }
    exist[p] = 1;
  }

  bool find(char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return 0;
      p = nex[p][c];
    }
    return exist[p];
  }
};


// has a better encapsulation
struct Node {
    // 4*26 = 104 bytes + 4(1+3)
    bool isEnd;
    int count;
    Node* next[26];
    Node() {
        isEnd = false;
        for (int i = 0; i < 26; i++) {
            next[i] = nullptr;
        }
    }
};
*/