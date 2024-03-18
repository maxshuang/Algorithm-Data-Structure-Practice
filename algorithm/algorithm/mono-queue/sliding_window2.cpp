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
        // [NOTE]: use back >= target to avoid somebody hack the test
        // [TRAP]: There is a trap here, if you remove the equal one，
        // you will get the wrong answer if there are some same values.
        // Or you will exceed the time limit
        // But the overall time complexity is O(N)
        // This is not a trap, it's different implement
        while (front < back && data[queue[back - 1]] >= data[i])
            back--;
        queue[back++] = i;
    }
    for (int i = WK; i < N; ++i)
    {
        std::cout << data[queue[front]] << " ";
        //[WRONG]: wrong here, need check the front < back, or
        // the while will keep going because all the elements are 0
        // WK == 1 will trigger this bug
        while (front < back && queue[front] <= (i - WK))
            front++;
        while (front < back && data[queue[back - 1]] >= data[i])
            back--;
        queue[back++] = i;
    }

    std::cout << data[queue[front]] << std::endl;
}

void get_max()
{
    // we only need a valid range
    // if [front, back) => front=0, back=0
    // if [front, back] => front=0, back=-1
    front = 0, back = 0;
    for (int i = 0; i < WK; ++i)
    {
        while (front < back && data[queue[back - 1]] <= data[i])
            back--;
        queue[back++] = i;
    }
    for (int i = WK; i < N; ++i)
    {
        std::cout << data[queue[front]] << " ";
        while (front < back && queue[front] <= i - WK)
            front++;
        while (front < back && data[queue[back - 1]] <= data[i])
            back--;
        queue[back++] = i;
    }

    std::cout << data[queue[front]] << std::endl;
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