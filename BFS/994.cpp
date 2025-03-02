//
// Created by Guillermo Galvez on 14/02/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H
#define ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class Queue
{
private:
	T *arr;
	int frontIndex, rearIndex, capacity;

public:
	explicit Queue(int cap)
	{
		capacity = cap;
		arr = new T[capacity];
		frontIndex = 0;
		rearIndex = -1;
	}

	~Queue()
	{
		delete[] arr;
	}

	void enqueue(T value)
	{
		if (rearIndex + 1 == capacity)
		{
			cout << "Queue is full, cannot enqueue.\n";
			return;
		}
		rearIndex++;
		arr[rearIndex] = value;
	}

	void dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue is empty, cannot dequeue.\n";
			return;
		}
		frontIndex++;
	}

	[[nodiscard]] T front() const
	{
		if (isEmpty())
		{
			throw out_of_range("Queue is empty.");
		}
		return arr[frontIndex];
	}

	[[nodiscard]] bool isEmpty() const
	{
		return frontIndex > rearIndex;
	}

	[[nodiscard]] bool isFull() const
	{
		return rearIndex == capacity - 1;
	}

	void display() const
	{
		if (isEmpty())
		{
			cout << "Queue is empty.\n";
			return;
		}
		for (int i = frontIndex; i <= rearIndex; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
};

#endif // ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H

class Solution
{
public:
	int orangesRotting(vector<vector<int>> &grid)
	{
		int m = grid.size();
		int n = grid[0].size();
		Queue<int> q(m * n);
		int fresh = 0;

		auto encode = [n](int x, int y)
		{ return x * n + y; };
		auto getX = [n](int val)
		{ return val / n; };
		auto getY = [n](int val)
		{ return val % n; };

		int nextLevelSize = 0;
		int currentLevelSize = 0;

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (grid[i][j] == 2)
				{
					q.enqueue(encode(i, j));
					currentLevelSize++;
				}
				else if (grid[i][j] == 1)
				{
					fresh++;
				}
			}
		}

		if (fresh == 0)
			return 0;

		int dx[] = {1, -1, 0, 0};
		int dy[] = {0, 0, 1, -1};
		int minutes = -1;

		while (!q.isEmpty())
		{
			minutes++;

			while (currentLevelSize > 0)
			{
				int curr = q.front();
				int x = getX(curr);
				int y = getY(curr);
				q.dequeue();
				currentLevelSize--;

				for (int i = 0; i < 4; i++)
				{
					int nx = x + dx[i];
					int ny = y + dy[i];

					if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1)
					{
						grid[nx][ny] = 2;
						fresh--;
						q.enqueue(encode(nx, ny));
						nextLevelSize++;
					}
				}
			}

			if (nextLevelSize == 0)
				break;

			currentLevelSize = nextLevelSize;
			nextLevelSize = 0;
		}

		return fresh == 0 ? minutes : -1;
	}
};