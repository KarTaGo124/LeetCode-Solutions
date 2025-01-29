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

class StockSpanner
{
private:
	stack<pair<int, int>> stock;

public:
	StockSpanner()
	{
	}

	int next(int price)
	{
		int span = 1;
		while (!stock.empty() && price >= stock.top().first)
		{
			span += stock.top().second;
			stock.pop();
		}
		stock.push({price, span});
		return span;
	}
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */