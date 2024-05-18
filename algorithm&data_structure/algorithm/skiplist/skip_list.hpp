#include <time.h>
#include <stdexcept>
#include <vector>

class SkipList
{
private:
    static const int MaxLevel = 21;
    static const int Limit = 0x7FFF;
    struct Node
    {
        Node(int k, int v, int lev) : key(k), value(v), level(lev), forward(lev, nullptr) {}
        int key;
        int value;
        int level;
        std::vector<Node*> forward;
    };

public:
    SkipList(float p) : len_(0), p_(p), threshold_(Limit * p_), max_level_(1), head_(-1, -1, MaxLevel)
    {
        srand(time(NULL));
    }

    ~SkipList()
    {
        Node *n = head_.forward[0];
        while (n)
        {
            Node *next = n->forward[0];
            delete n;
            n = next;
        }
    }

    bool Insert(int key, int value)
    {
        std::vector<Node*> pres(MaxLevel, &head_);
        Node *pre = find(key, &pres, max_level_);

        if (pre->forward[0] && pre->forward[0]->key == key)
        {
            pre->forward[0]->value = value;
            return false;
        }

        Node *new_node = new Node(key, value, randomLevel());
        for (int i = 0; i < new_node->level; ++i)
        {
            new_node->forward[i] = pres[i]->forward[i];
            pres[i]->forward[i] = new_node;
        }
        ++len_;
        update_max_level(new_node->level);
        return true;
    }

    void Delete(int key)
    {
        std::vector<Node*> pres(MaxLevel, &head_);
        Node *pre = find(key, &pres, max_level_);

        if (!pre->forward[0] || pre->forward[0]->key != key)
            return;

        Node *del_node = pre->forward[0];
        for (int i = 0; i < del_node->level; ++i)
        {
            pres[i]->forward[i] = del_node->forward[i];
            del_node->forward[i] = nullptr;
        }
        if(del_node->level == max_level_)
            update_max_level();
        delete del_node;
        --len_;
    }

    int Get(int key)
    {
        Node *pre = find(key, nullptr, max_level_);

        if (pre->forward[0] && pre->forward[0]->key == key)
            return pre->forward[0]->value;

        throw std::out_of_range("key doesn't exists");
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
    Node *find(int key, std::vector<Node*>* pre, int max_level)
    {
        Node *n = &head_;
        for (int i = max_level - 1; i >= 0; i--)
        {
            while (n->forward[i] && n->forward[i]->key < key)
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
    // TODO:
    // 2. template
    // 3. compare function for the map
    // 4. rank access
    // 5. iterator
};