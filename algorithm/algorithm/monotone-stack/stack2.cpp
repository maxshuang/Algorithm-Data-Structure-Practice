#include <iostream>
#include <string.h>

#define kMaxSize 1000005

int heights[kMaxSize];
int energies[kMaxSize];
int sums[kMaxSize];
int N = 0;

struct MonoStack
{
    int data[kMaxSize];
    int top;
    MonoStack() : top(0) {}
    void push(int x)
    {
        data[top++] = x;
    }
    void pop()
    {
        --top;
    }
    int Top()
    {
        return data[top - 1];
    }
    bool empty()
    {
        return top == 0;
    }
};

int main()
{
    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> heights[i] >> energies[i];
    }

    // Only one round can find the both directions
    MonoStack stack1;
    for (int i = 1; i <= N; ++i)
    {
        while (!stack1.empty() && heights[stack1.Top()] < heights[i])
        {
            sums[i] += energies[stack1.Top()];
            stack1.pop();
            //[NOTE]: 这里很容易忘记这个 break, 导致一直循环下去
        }
        if (!stack1.empty())
            sums[stack1.Top()] += energies[i];
        stack1.push(i);
    }

    int max = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (sums[i] > max)
            max = sums[i];
    }

    std::cout << max << std::endl;
}