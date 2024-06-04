#include "hash_table.h"

inline std::vector<int> getPrime(int n) {
    std::vector<int> primes;
    std::vector<bool> isPrime(n+1, true);
    int end=std::pow(n, 0.5);
    for(int i=2; i<=end; i++) {
        if(isPrime[i]) {
            // i*i, i*(i+1), i*(i+2) ...
            for(int j=i*i; j<n+1; j+=i) {
                isPrime[j]=false;
            }
        }
    }

    for(int i=2; i<n+1; i++) {
        if(isPrime[i]) primes.push_back(i);
    }

    return primes;
}

inline bool isPrime(int n) {
    if(n<2) return false;
    else if(n==2) return true;
    else if((n&1)==0) return false;

    int end=std::pow(n, 0.5);
    for(int i=3; i<end; i++) {
        if(n%i==0) return false;
    }
    return true;
}

// Q4: use static table to store prime numbers
static std::vector<int> kPrimeVec=getPrime(10e5);

inline int findNextPrime(int n) {
    return *(std::upper_bound(kPrimeVec.begin(), kPrimeVec.end(), n));
}

void HashTable::Put(int key, int value)
{
    int slot = hashFunc(key);
    Node *node = slots_[slot];
    while (node)
    {
        if (node->key == key)
        {
            node->value = value;
            return;
        }
        node = node->next;
    }
    Node *newNode = new Node(key, value);
    newNode->next = slots_[slot];
    slots_[slot] = newNode;
    ++size_;
    rehash();
}

void HashTable::Delete(int key)
{
    int slot = hashFunc(key);
    Node *node = slots_[slot];
    Node *prev = nullptr;
    while (node)
    {
        if (node->key == key)
        {
            if (prev)
            {
                prev->next = node->next;
            }
            else
            {
                slots_[slot] = node->next;
                delete node;
                --size_;
                return;
            }
        }
        else
        {
            prev = node;
            node = node->next;
        }
    }
}

int HashTable::Get(int key)
{
    int slot = hashFunc(key);
    Node *node = slots_[slot];
    while (node)
    {
        if (node->key == key)
        {
            return node->value;
        }
        node = node->next;
    }

    // insert if not exists
    Node *newNode = new Node(key, -1);
    newNode->next = slots_[slot];
    slots_[slot] = newNode;
    ++size_;
    rehash();

    return -1;
}

int HashTable::hashFunc(int key) const
{
    return key % capacity_;
}

bool HashTable::IsEmpty() const
{
    return size_ == 0;
}

size_t HashTable::Size() const
{
    return size_;
}

void HashTable::Clear()
{
}

void HashTable::rehash()
{
    bool rehash = false;
    if (size_ > capacity_ * max_load_factor_)
    {
        capacity_ = findNextPrime(capacity_ * 2);
        rehash = true;
    }
    else if (capacity_ >= kSize && size_ < capacity_ / 8) // shrink if the size_ is the 1/4 of original size_
    {
        // Q: Would it enlarge and shrink frequently?
        capacity_ = findNextPrime(capacity_ / 2);
        rehash = true;
    }

    if (rehash)
    {
        std::vector<Node *> newSlots(capacity_, nullptr);
        for (Node *node : slots_)
        {
            while (node)
            {
                int slot = hashFunc(node->key);
                Node *next = node->next;
                node->next = newSlots[slot];
                newSlots[slot] = node;
                node = next;
            }
        }

        slots_.swap(newSlots);
        newSlots.clear();
    }
}