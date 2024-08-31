#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
// queue/priority_queue
#include <queue>
// pair
#include <utility>
#include <cassert>
using namespace std;

/*
Given a list of [FileName, FileSize, [Collection]] - Collection is optional, i.e., a collection can have 1 or more files. Same file can be a part of more than 1 collection.
How would you design a system

To calculate total size of files processed.
To calculate Top K collections based on size.
Example:
file1.txt(size: 100)
file2.txt(size: 200) in collection "collection1"
file3.txt(size: 200) in collection "collection1"
file4.txt(size: 300) in collection "collection2"
file5.txt(size: 100)
Output:

Total size of files processed: 900
Top 2 collections:

collection1 : 400
collection2 : 300
 */

#define ASSERT_OR_PRINT(condition, message) \
    do {                                    \
        if(!(condition)) {                  \
            std::cerr << "assert fail:"     \
              << message << std::endl;      \
            assert((condition));            \
        }                                   \
    }while(0)                               

struct FileInfo {
    string fileName;
    int fileSize;
    vector<string> collection;
};

class FileProcessingTopK {
public:
    FileProcessingTopK(): totalFileSize(0){}
    vector<string> fileProcessing(vector<FileInfo> lists, int topK);
    ~FileProcessingTopK()=default;
private:
    int totalFileSize;
    unordered_map<string, int> collectionSizeMap;
};

vector<string> FileProcessingTopK::fileProcessing(vector<FileInfo> lists, int topK) {
    for(const auto& fi: lists) {
        this->totalFileSize += fi.fileSize;
        for(const auto& cl: fi.collection) {
            this->collectionSizeMap[cl] += fi.fileSize;
        }
    }

    // maintain a K min priority queue, all remaining in the queue at last is 
    // top K collections. 
    auto greater = [](const pair<int, string>& lf, const pair<int, string>& rt) {
        return (lf.first==rt.first && lf.second>rt.second) ||    lf.first>rt.first;
    };
    
    // top/emplace/push/pop/empty/size
    using PT = pair<int, string>;
    priority_queue<PT, vector<PT>, decltype(greater)> pq(greater);
    
    for(const auto& [k, v]: this->collectionSizeMap) {
        pq.emplace(pair<int, string>(v, k));
        if(pq.size()>topK) pq.pop();
    }

    vector<string> res;
    while(!pq.empty()) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res; 
}

void print(const std::vector<string>& vec) {
   std::cout << "[";
   for(auto& str: vec) std::cout << str << ",";
   std::cout << "]";
}

int main() {
    // collection1: 400, collection2: 300, collection3: 200
    vector<FileInfo> lists{{"file1.txt", 100, {}}, {"file2.txt", 200,    {"collection1", "collection3"}},{"file3.txt", 200, {"collection1"}}, {"file4.txt", 300, {"collection2"}}, {"file5.txt", 100, {}}};
    
    FileProcessingTopK fp;
    auto res = fp.fileProcessing(lists, 2);
    //print(res);
    ASSERT_OR_PRINT((res==vector<string>{"collection2", "collection1"}), "fail");
}