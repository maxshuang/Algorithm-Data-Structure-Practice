#include <iostream>

#define kMaxSize 1000005

int data[kMaxSize];
int N;
int WK;

typedef bool (*CMP)(int, int);

// for non-increasing queue
bool lesser(int i, int j) { return i < j; }
// for non-decreasing queue
bool larger(int i, int j) { return j < i; }

struct MonoDeque
{
    MonoDeque() : front_(0), back_(0), cmp_(NULL) {}

    void init(CMP cmp)
    {
        cmp_ = cmp;
        front_ = 0;
        back_ = 0;
    }

    void push_back(int i)
    {
        while (!empty() && cmp_(back(), i))
        {
            pop_back();
        }
        queue_[back_++] = i;
    }
    int front()
    {
        return queue_[front_];
    }
    int back()
    {
        return queue_[back_ - 1];
    }
    void pop_front()
    {
        front_++;
    }
    void pop_back()
    {
        back_--;
    }
    bool empty()
    {
        return front_ == back_;
    }

    int front_; // [front, back)
    int back_;
    CMP cmp_;
    int queue_[kMaxSize];
};

MonoDeque deque;

void output()
{
    for (int i = 0; i < WK; ++i)
    {
        deque.push_back(data[i]);
    }

    for (int i = WK; i < N; ++i)
    {
        std::cout << deque.front() << " ";
        if (deque.front() == data[i - WK])
            deque.pop_front();
        deque.push_back(data[i]);
    }
    std::cout << deque.front() << std::endl;
}

void get_min()
{
    deque.init(larger);
    output();
}

void get_max()
{
    deque.init(lesser);
    output();
}

int main()
{
    std::cin >> N >> WK;

    for (int i = 0; i < N; ++i)
    {
        std::cin >> data[i];
    }

    get_min();
    get_max();
    return 0;
}