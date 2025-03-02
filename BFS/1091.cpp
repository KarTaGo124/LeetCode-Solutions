//
// Created by Guillermo Galvez on 14/02/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H
#define ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H

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
		if (empty())
		{
			cout << "Queue is empty, cannot dequeue.\n";
			return;
		}
		frontIndex++;
	}

	[[nodiscard]] T front() const
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}
		return arr[frontIndex];
	}

	[[nodiscard]] bool empty() const
	{
		return frontIndex > rearIndex;
	}

	[[nodiscard]] bool full() const
	{
		return rearIndex == capacity - 1;
	}

	void display() const
	{
		if (empty())
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

struct Pair
{
	int x;
	int y;
	Pair(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

class Solution
{
public:
	int shortestPathBinaryMatrix(vector<vector<int>> &grid)
	{
		int n = grid.size();
		if (n == 0)
			return -1;
		if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
			return -1;

		Queue<Pair *> q(pow(n, 2));
		q.enqueue(new Pair(0, 0));

		grid[0][0] = 1;

		int directions[8][2] = {
			{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

		while (!q.empty())
		{
			auto pair = q.front();
			int x = pair->x;
			int y = pair->y;

			q.dequeue();
			int pathLength = grid[x][y];

			if (x == n - 1 && y == n - 1)
				return pathLength;

			for (int i = 0; i < 8; i++)
			{
				int nx = x + directions[i][0];
				int ny = y + directions[i][1];
				if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0)
				{
					q.enqueue(new Pair(nx, ny));
					grid[nx][ny] = pathLength + 1;
				}
			}
		}

		return -1;
	}
};