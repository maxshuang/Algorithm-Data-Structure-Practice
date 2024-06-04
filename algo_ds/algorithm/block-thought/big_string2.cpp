#include <cmath>
#include <iostream>
#include <string>

#define kMaxSize 1005

std::string org_data;
int block_len = 0;
int block_num = 0;

struct BlockList
{
    struct Node
    {
        Node() : next(0), size(0) {}
        int next;
        char data[kMaxSize << 1];
        int size;
    };

    BlockList() : cur_node(1), head(0) {}

    void init(const std::string &d)
    {
        int pre_node = head;
        for (int i = 0; i < block_num-1; ++i)
        {
            pool[pre_node].next = cur_node;
            pool[cur_node].size = block_len;
            pool[cur_node].next = 0;
            int offset = i * block_len;
            for(int j=0; j<block_len; ++j) {
                pool[cur_node].data[j]=d[offset+j];
            }
            pre_node = cur_node;
            ++cur_node;
        }

        // left over
        pool[pre_node].next = cur_node;
        int offset=(block_num-1)*block_len;
        pool[cur_node].size = d.size()-offset;
        pool[cur_node].next = 0;
        for(int j=0; j<pool[cur_node].size; ++j) {
            pool[cur_node].data[j]=d[offset+j];
        }
        ++cur_node;
    }

    void insert(char c, int p)
    {
        int pre=head;
        int p1 = pool[pre].next;
        int sum = 0;
        while (p1)
        {
            Node &cur = pool[p1];
            if (sum + cur.size >= p)
            {
                int pos = p - sum - 1;
                for (int i = cur.size - 1; i >= pos; --i)
                {
                    cur.data[i + 1] = cur.data[i];
                }
                cur.data[pos] = c;
                cur.size++;
                checkLimit(p1);
                return;
            }
            else
            {
                sum += cur.size;
                pre=p1;
                p1 = cur.next;
            }
        }

        // push back
        if(pre==0) {
            // empty
            pool[cur_node].next = 0;
            pool[cur_node].size = 1;
            pool[cur_node].data[0] = c;
            pool[head].next = cur_node;
            ++cur_node;
        }else {
            // add to tail
            Node &cur=pool[pre];
            cur.data[cur.size]=c;
            cur.size++;
            checkLimit(pre);
        }
    }

    char query(int p)
    {
        int p1 = pool[head].next;
        int sum = 0;
        while (p1)
        {
            Node &cur = pool[p1];
            if (sum + cur.size > p)
            {
                int pos = p - sum - 1;
                return cur.data[pos];
            }
            else
            {
                sum += cur.size;
                p1 = cur.next;
            }
        }
    }

    void checkLimit(int p)
    {
        if (pool[p].size <= 2 * block_len)
            return;
        // split
        pool[cur_node].next = pool[p].next;
        pool[cur_node].size = pool[p].size - block_len;
        for (int i = 0; i < pool[cur_node].size; ++i)
        {
            pool[cur_node].data[i] = pool[p].data[i + block_len];
        }
        pool[p].size = block_len;
        pool[p].next = cur_node;
        ++cur_node;
    }

    int cur_node; // from 1
    int head;   // head is 0
    Node pool[kMaxSize];
};

BlockList data;

int main()
{
    std::cin >> org_data;
    block_len = (int)std::sqrt((float)org_data.size());
    block_num = (org_data.size() + block_len - 1) / block_len; // round up
    
    data.init(org_data);
    int N = 0;
    std::cin >> N;
    while (N)
    {
        char op;
        std::cin >> op;
        if (op == 'I')
        {
            char c;
            int p;
            std::cin >> c >> p;
            data.insert(c, p);
        }
        else if (op == 'Q')
        {
            int p;
            std::cin >> p;
            std::cout << data.query(p) << std::endl;
        }
        --N;
    }
}