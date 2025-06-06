
#include <queue>

class MyStack
{
private:
	queue<int> q1;
	queue<int> q2;

public:
	MyStack()
	{
	}

	void push(int x)
	{
		q1.push(x);
	}

	int pop()
	{
		int val;
		while (q1.size() > 1)
		{
			val = q1.front();
			q1.pop();
			q2.push(val);
		}
		val = q1.front();
		q1.pop();
		swap(q1, q2);
		return val;
	}

	int top()
	{
		int val;
		while (q1.size() > 1)
		{
			val = q1.front();
			q1.pop();
			q2.push(val);
		}
		val = q1.front();
		q1.pop();
		q2.push(val);
		swap(q1, q2);
		return val;
	}

	bool empty()
	{
		return (q1.empty());
	}
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */