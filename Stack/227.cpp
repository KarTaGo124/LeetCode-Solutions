//
// Created by Guillermo Galvez on 19/01/2025.
//
#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:
	T *arr;
	int topIndex;
	int capacity;

public:
	explicit Stack(int size)
	{
		capacity = size;
		arr = new T[capacity];
		topIndex = -1;
	}

	~Stack()
	{
		delete[] arr;
	}

	void push(T value)
	{
		if (topIndex + 1 == capacity)
		{
			cout << "Stack overflow, cannot push.\n";
			return;
		}
		arr[++topIndex] = value;
	}

	void pop()
	{
		if (isEmpty())
		{
			cout << "Stack is empty, cannot pop.\n";
			return;
		}
		topIndex--;
	}

	[[nodiscard]] T top() const
	{
		if (isEmpty())
		{
			throw out_of_range("Stack is empty.");
		}
		return arr[topIndex];
	}

	[[nodiscard]] bool isEmpty() const
	{
		return topIndex == -1;
	}

	[[nodiscard]] bool isFull() const
	{
		return topIndex == capacity - 1;
	}

	void display() const
	{
		for (int i = topIndex; i >= 0; --i)
		{
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
};

class Solution
{
public:
	int operate(char token, int val1, int val2)
	{
		if (token == '+')
			return val1 + val2;
		else if (token == '-')
			return val1 - val2;
		else if (token == '/')
			return val1 / val2;
		else if (token == '*')
			return val1 * val2;
		return 0;
	}

	int calculate(string s)
	{
		Stack<long long int> stack(100000);
		char sign = '+';
		long long int number = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (isdigit(s[i]))
				number = 10 * number + s[i] - '0';

			if (!isdigit(s[i]) && !isspace(s[i]) || i == s.size() - 1)
			{
				if (sign == '-')
				{
					stack.push(-number);
				}
				else if (sign == '+')
				{
					stack.push(number);
				}
				else
				{
					int val;
					if (sign == '*')
					{
						val = stack.top() * number;
					}
					else
					{
						val = stack.top() / number;
					}
					stack.pop();
					stack.push(val);
				}
				sign = s[i];
				number = 0;
			}
		}
		int result = 0;
		while (!stack.isEmpty())
		{
			result += stack.top();
			stack.pop();
		}
		return result;
	}
};