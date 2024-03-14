#include <deque>
#include <stack>
#include <iostream>
#include <string>

std::deque<int> post;
std::stack<int> pre;
std::string empty;

// for k, pre holds the first k/2, post holds the latter k/2
void balance()
{
    int gap = int(post.size() - pre.size());
    if (gap == 0 || gap == 1)
        return;
    if (gap > 0) // gap>=2
    {
        gap = gap >> 1;
        while (gap)
        {
            pre.push(post.front());
            post.pop_front();
            --gap;
        }
    }
    else // gap < 0
    {
        gap = (-gap);
        gap = ((gap & 1) ? (gap >> 1) + 1 : gap >> 1);
        while (gap)
        {
            post.push_front(pre.top());
            pre.pop();
            --gap;
        }
    }
}

void findMedium()
{
    if (post.size() == pre.size())
    {
        if (post.front() < pre.top())
        {
            std::cout << post.front() << std::endl;
            post.pop_front();
        }
        else
        {
            std::cout << pre.top() << std::endl;
            pre.pop();
        }
    }
    else
    {
        // definitely in the post
        std::cout << post.front() << std::endl;
        post.pop_front();
    }
}

void clear()
{
    post.clear();
    std::stack<int> empty_pre;
    pre.swap(empty_pre);
}

int main()
{
    while (!std::cin.eof())
    {
        int tmp;
        std::cin >> tmp;
        if (tmp != 0 && tmp != -1)
        {
            post.push_back(tmp);
        }
        else if (tmp == -1)
        {
            balance();
            findMedium();
        }
        else
        {
            std::getline(std::cin, empty);
            std::cout << std::endl;
            clear();
        }
    }
}