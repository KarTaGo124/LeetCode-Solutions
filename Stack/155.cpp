class MinStack
{
private:
	int *stack;
	int *min_stack;
	int max_capacity;
	int top_index;

public:
	MinStack()
	{
		max_capacity = 1000;
		stack = new int[max_capacity];
		min_stack = new int[max_capacity];
		top_index = -1;
	}

	void push(int val)
	{
		if (top_index + 1 >= max_capacity)
			return;
		stack[++top_index] = val;

		if (top_index == 0)
		{
			min_stack[top_index] = val;
		}
		else
		{
			min_stack[top_index] = (val < min_stack[top_index - 1]) ? val : min_stack[top_index - 1];
		}
	}

	void pop()
	{
		if (top_index == -1)
			return;
		--top_index;
	}

	int top()
	{
		if (top_index == -1)
			return -1;
		return stack[top_index];
	}

	int getMin()
	{
		if (top_index == -1)
			return INT_MAX;
		return min_stack[top_index];
	}
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */