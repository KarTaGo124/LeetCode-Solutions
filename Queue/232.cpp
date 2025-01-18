#include <stack>

class MyQueue
{
private:
	stack<int> s1;
	stack<int> s2;

public:
	MyQueue()
	{
	}

	void push(int x)
	{
		s1.push(x);
	}

	int pop()
	{
		int val;
		while (s1.size() > 1)
		{
			val = s1.top();
			s1.pop();
			s2.push(val);
		}
		int top = s1.top();
		s1.pop();
		while (s2.size() > 0)
		{
			val = s2.top();
			s2.pop();
			s1.push(val);
		}
		return top;
	}

	int peek()
	{
		int val;
		while (s1.size() > 1)
		{
			val = s1.top();
			s1.pop();
			s2.push(val);
		}
		int top = s1.top();
		while (s2.size() > 0)
		{
			val = s2.top();
			s2.pop();
			s1.push(val);
		}
		return top;
	}

	bool empty()
	{
		return (s1.empty());
	}
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */