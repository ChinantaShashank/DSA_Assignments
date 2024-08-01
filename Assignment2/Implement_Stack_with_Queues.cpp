#include<bits/stdc++.h>
class MyStack
{
private:
    std::queue<int> queue1;
    std::queue<int> queue2;

public:
    MyStack() 
    {
    }

    void push(int x) 
    {
        queue2.push(x);
        while (!queue1.empty()) 
        {
            queue2.push(queue1.front());
            queue1.pop();
        }
        std::swap(queue1, queue2);
    }

    int pop() 
    {
        if (empty()) throw std::runtime_error("Stack is empty");
        int top = queue1.front();
        queue1.pop();
        return top;
    }

    int top() 
    {
        if (empty()) throw std::runtime_error("Stack is empty");
        return queue1.front();
    }

    bool empty() 
    {
        return queue1.empty();
    }
};

int main()
{
    MyStack stack;
    stack.push(1);
    stack.push(2);
    std::cout << stack.top() << std::endl;  
    std::cout << stack.pop() << std::endl;  
    std::cout << std::boolalpha << stack.empty() << std::endl;
    return 0;
}