#include <iostream>

#define kMaxSize 1000005

int data[kMaxSize];
int queue[kMaxSize];
int front, back;
int N;
int WK;

void get_min()
{
    front = 0, back = 0;
    for (int i = 0; i < WK; ++i)
    {
        while (front < back && queue[back - 1] > data[i])
            back--;
        queue[back++] = data[i];
    }
    for (int i = WK; i < N; ++i)
    {
        std::cout << queue[front] << " ";
        while (front < back && queue[back - 1] > data[i])
            back--;
        queue[back++] = data[i];
        if (front < back && queue[front] == data[i - WK])
            front++;        
    }

    std::cout << queue[front] << std::endl;
}

void get_max()
{
    front = 0, back = 0;
    for (int i = 0; i < WK; ++i)
    {
        while (front < back && queue[back - 1] < data[i])
            back--;
        queue[back++] = data[i];
    }
    for (int i = WK; i < N; ++i)
    {
        std::cout << queue[front] << " ";
        // if we save the value, we must preserve all the same value
        while (front < back && queue[back - 1] < data[i])
            back--;
        queue[back++] = data[i];
        if (front < back && queue[front] == data[i - WK])
            front++;
    }

    std::cout << queue[front] << std::endl;
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