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
private:
	int operate(string token, int val1, int val2)
	{
		if (token == "+")
			return val1 + val2;
		else if (token == "-")
			return val1 - val2;
		else if (token == "/")
			return val1 / val2;
		else if (token == "*")
			return val1 * val2;
		return 0;
	}

public:
	int evalRPN(vector<string> &tokens)
	{
		Stack<int> stack(10000);
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "/" && tokens[i] != "*")
			{
				stack.push(std::stoi((tokens[i])));
			}
			if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "/" || tokens[i] == "*")
			{
				int val2 = stack.top();
				stack.pop();
				int val1 = stack.top();
				stack.pop();
				int result = operate(tokens[i], val1, val2);
				stack.push(result);
			}
		}
		return stack.top();
	}
};