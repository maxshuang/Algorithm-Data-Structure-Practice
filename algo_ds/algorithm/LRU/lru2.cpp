class LRUCache {
public:
    LRUCache(int capacity) : m_capacity(capacity) {}
    
    int get(int key) {
        auto iter = m_map.find(key); // 在哈希表中查找键值
        if (iter == m_map.end()) { // 如果未找到，则返回-1
            return -1;
        }
        m_list.splice(m_list.begin(), m_list, iter->second); // 将查找到的节点移动到列表头部
        return iter->second->second; // 返回节点值
    }
    
    void put(int key, int value) {
        auto iter = m_map.find(key); // 在哈希表中查找键值
        if (iter != m_map.end()) { // 如果键值已经存在，则更新节点值，并移动到列表头部
            iter->second->second = value;
            m_list.splice(m_list.begin(), m_list, iter->second);
            return;
        }
        if (m_map.size() == m_capacity) { // 如果缓存已满，则删除最久未使用的节点
            m_map.erase(m_list.back().first);
            m_list.pop_back();
        }
        m_list.emplace_front(key, value); // 将新节点插入列表头部
        m_map[key] = m_list.begin(); // 在哈希表中保存节点位置
    }
  private:
    int m_capacity;
    std::list<std::pair<int, int>> m_list; // 双向链表，用于保存节点
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_map; // 哈希表，用于快速查找节点  
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */