#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

#define ASSERT_OR_PRINT(condition, message) \
  do {                                      \
      if(!(condition)) {                    \
         std::cerr << "assert fail:"        \
          << message << std::endl;          \
         assert((condition));               \
      }                                     \
  }while(0)


#if 0
class Trie {
public:
  Trie(){}
  ~Trie(){
      cleanDFS(&root);
  }
  
  struct TrieNode {
    unordered_map<string, TrieNode*> children;
    bool isValid;
    int value;
    
    TrieNode(): isValid(false), value(-1){}
  };
  
  bool insert(const vector<string>& path, int value){
      TrieNode* cur=&root;
      for(const auto& str: path) {
         if(!cur->children.count(str)) {
            cur->children[str]=new TrieNode();
         }
         cur=cur->children[str];
      }
      cur->value=value;   
      if(cur->isValid) return false;
      
      cur->isValid=true;
      return true;
  }
  
  int get(const vector<string>& path){
      TrieNode* cur=&root;
      for(const auto& str: path) {
         if(!cur->children.count(str)) {
            return -1;
         }
         cur=cur->children[str];
      }
      
      if(cur->isValid) return cur->value;
      
      return -1;
  }
  
private:
  TrieNode root;
  
  void cleanDFS(TrieNode* cur) {
      if(!cur) return;
      
      if(cur->children.size()==0) {
          delete cur;
          return;
      }
      
      for(auto& [k, v]: cur->children) {
          cleanDFS(v);
      }
  }
};

void print(const std::vector<string>& vec) {
    std::cout << "[";
    for(auto s: vec) std::cout << s << ",";
    std::cout << "]";
}

class FileSystem {
public:
    FileSystem() {
    }

    bool createPath(string path, int value) {
         vector<string> paths = split(path);
         //print(paths);
         return tree.insert(paths, value);
    }

    int get(string path) {
        vector<string> paths = split(path);
        //print(paths);
        return tree.get(paths);
    }

private:
    Trie tree;
    
    vector<string> split(const string& path) {
        int st=-1, end=-1, lastEnd=-1;
        vector<string> paths;
        for(int i=0; i<path.size(); ++i) {
            if(path[i]=='/') {
              if(st==-1) st=i+1;
              else if(end==-1) end=i;
            }
            if(st!=-1 && end!=-1) {
              paths.emplace_back(path.substr(st, end-st));
              st=-1;
              lastEnd=end;
              end=-1;
            }
        }
        
        // corner case here 
        if(st==-1) st=lastEnd+1;
        if(end==-1) paths.emplace_back(path.substr(st));
        return paths;
    }
};
#endif

class FileSystem {
public:
    FileSystem() {
    }

    bool createPath(string path, int value) {
        bool res=false;
        if(pathValueMap.count(path))
            res=true;
        
        pathValueMap[path]=value;
        return res;
    }

    int get(string path) {
        if(pathValueMap.count(path)) 
          return pathValueMap[path];
          
        return -1;
    }
    
private:
    unordered_map<string, int> pathValueMap;
};

int main() {
    FileSystem fs;
    fs.createPath("/a", 1); // return true
    ASSERT_OR_PRINT((fs.get("/a")==1), "Should return 1"); // return 1
    ASSERT_OR_PRINT((fs.get("/a/b")==-1), "/a/b doesn't exist"); // return 1
    return 0;
}