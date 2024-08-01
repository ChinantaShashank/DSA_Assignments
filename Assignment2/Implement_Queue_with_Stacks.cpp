class MyQueue 
{
    public:
        stack<int> stack1;
        stack<int> stack2;
    
    MyQueue() 
    {
        
    }
    
    void push(int x) {
        stack1.push(x);
    }
    
    int pop() 
    {
        if (stack1.empty() && stack2.empty()) 
        {
            return -1;
        }
        if (!stack2.empty()) 
        {
            int top = stack2.top();
            stack2.pop();
            return top;
        } 
        else 
        {
            while (!stack1.empty()) {
                auto top = stack1.top();
                stack1.pop();
                stack2.push(top);
            }
        }
        int top = stack2.top();
        stack2.pop();
        return top;
    }
    
    int peek()
    {
        if (stack1.empty() && stack2.empty()) 
        {
            return -1;
        }
        if (!stack2.empty()) 
        {
            return stack2.top();
        } else {
            while (!stack1.empty()) 
            {
                auto top = stack1.top();
                stack1.pop();
                stack2.push(top);
            }
        }
        return stack2.top();
    }
    
    bool empty() {
        return stack1.empty() && stack2.empty();
    }
};