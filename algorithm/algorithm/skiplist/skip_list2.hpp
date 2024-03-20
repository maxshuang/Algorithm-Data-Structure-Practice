#include <time.h>
#include <stdexcept>
#include <vector>

template <typename K>
struct Lesser
{
    bool operator()(const K &a, const K &b) const
    {
        return a < b;
    }
};

template <typename K, typename V, typename C = Lesser<K>>
class SkipList2
{
private:
    static const int MaxLevel = 21;
    static const int Limit = 0x7FFF;

    struct Node
    {
        Node(const K &k, const V &v, int level) : key(k), value(v), level(level), size(0), forward(level, nullptr) {}
        K key;
        V value;
        int level;
        int size;
        std::vector<Node *> forward;
    };

public:
    SkipList2(float p): len_(0), p_(p), threshold_(Limit * p_), max_level_(1), head_(-1, -1, MaxLevel)
    {
        srand(time(NULL));
    }

    ~SkipList2()
    {
        Node *n = head_.forward[0];
        while (n)
        {
            Node *next = n->forward[0];
            delete n;
            n = next;
        }
    }

    bool Insert(const K &key, const V &value)
    {
        std::vector<Node *> pres(MaxLevel, &head_);
        Node *pre = find(key, &pres, max_level_);

        if (pre->forward[0] && !compare_(key, pre->forward[0]->key))
        {
            pre->forward[0]->value = value;
            return false;
        }

        Node *new_node = new Node(key, value, randomLevel());

        // insert
        for (int i = 1; i < new_node->level; ++i)
        {
            new_node->forward[i] = pres[i]->forward[i];
            pres[i]->forward[i] = new_node;
            pres[i]->size += 1;
        }
        ++len_;
        update_max_level(new_node->level);
        return true;
    }

    void Delete(const K &key)
    {
        std::vector<Node *> pres(MaxLevel, &head_);
        Node *pre = find(key, &pres, max_level_);

        if (!pre->forward[0] || compare_(key, pre->forward[0]->key))
            return;

        // update size


        // delete
        for (int i = 0; i < del_node->level; ++i)
        {
            pres[i]->forward[i] = del_node->forward[i];
            del_node->forward[i] = nullptr;
        }
        if (del_node->level == max_level_)
            update_max_level();
        delete del_node;
        --len_;
    }

    int Get(const K &key)
    {
        Node *pre = find(key, nullptr, max_level_);
        // pre is the largest node that key < key, so if its successor is not larger than key
        // then its successor is the node we want
        if (pre->forward[0] && !compare_(key, pre->forward[0]->key))
            return pre->forward[0]->value;

        throw std::out_of_range("key doesn't exists");
    }

    Node& GetRank(int rank) {
        if(rank > len_)
            throw std::out_of_range("rank out of range");

        Node* n=&head_;
        for(int i=max_level_-1; i>=0; --i) {
            while(n->forward[i] && n->forward[i]->size<rank) {
                n=n->forward[i];
            }
        }
        return *(n->forward[0]);
    }

    int Size() const { return len_; }

    bool Empty() const { return len_ == 0; }

private:
    int randomLevel() const
    {
        int level = 1;
        while (level < MaxLevel && (rand() & Limit) < threshold_)
            level++;
        return level;
    }

    // return the largest node that key < key in level 0
    Node *find(const K &key, std::vector<Node *> *pre, int max_level)
    {
        Node *n = &head_;
        for (int i = max_level - 1; i >= 0; i--)
        {
            while (n->forward[i] && compare_(n->forward[i]->key, key))
                n = n->forward[i];
            if (pre)
                (*pre)[i] = n;
        }

        return n;
    }

    void update_max_level(int level)
    {
        if (level > max_level_)
            max_level_ = level;
    }

    void update_max_level()
    {
        for (int i = max_level_ - 1; i >= 0; --i)
        {
            if (head_.forward[i])
            {
                max_level_ = i + 1;
                return;
            }
        }
        max_level_ = 1;
    }

private:
    int len_;
    float p_;
    int threshold_;
    int max_level_;
    Node head_;
    C compare_;
    // TODO:
    // 5. iterator
    // 6. copy constructor/assignment constructor/deep copy/shallow copy
};