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

template <typename T>
class Vector
{
	T *arr;
	size_t capacity_ = 1;
	size_t size_ = 0;

public:
	// Constructor
	Vector()
	{
		arr = new T[capacity_];
	}

	// Destructor
	~Vector()
	{
		clear();
		delete[] arr;
	}

	Vector(const size_t &n) : capacity_(n), size_(n)
	{
		arr = new T[capacity_];
	}

	// Copy Constructor
	Vector(const Vector &other) : capacity_(other.capacity_), size_(other.size_)
	{
		arr = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
		{
			arr[i] = other.arr[i];
		}
	}

	// Move Constructor
	Vector(Vector &&other) noexcept : arr(other.arr), capacity_(other.capacity_), size_(other.size_)
	{
		other.arr = nullptr;
		other.capacity_ = 0;
		other.size_ = 0;
	}

	// Copy Assignment Operator
	Vector &operator=(const Vector &other)
	{
		if (this != &other)
		{
			T *temp = new T[other.capacity_];
			for (size_t i = 0; i < other.size_; ++i)
			{
				temp[i] = other.arr[i];
			}
			delete[] arr;
			arr = temp;
			capacity_ = other.capacity_;
			size_ = other.size_;
		}
		return *this;
	}

	// Move Assignment Operator
	Vector &operator=(Vector &&other) noexcept
	{
		if (this != &other)
		{
			delete[] arr;
			arr = other.arr;
			capacity_ = other.capacity_;
			size_ = other.size_;
			other.arr = nullptr;
			other.capacity_ = 0;
			other.size_ = 0;
		}
		return *this;
	}

	void resize(const size_t &new_capacity)
	{
		capacity_ = new_capacity;
		T *temp = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
		{
			temp[i] = std::move(arr[i]);
		}
		delete[] arr;
		arr = temp;
	}

	// Copy push_back
	void push_back(const T &value)
	{
		if (size_ == capacity_)
		{
			resize(capacity_ * 2);
		}
		arr[size_++] = value;
	}

	// Move push_back
	void push_back(T &&value)
	{
		if (size_ == capacity_)
		{
			resize(capacity_ * 2);
		}
		arr[size_++] = std::move(value);
	}

	void pop_back()
	{
		if (size_ == 0)
		{
			throw std::out_of_range("Vector is empty");
		}
		--size_;
	}

	T &operator[](const size_t &index)
	{
		if (index >= size_)
		{
			throw std::out_of_range("Index out of bounds");
		}
		return arr[index];
	}

	const T &operator[](const size_t &index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Index out of bounds");
		}
		return arr[index];
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	void clear()
	{
		while (size_ > 0)
		{
			pop_back();
		}
		size_ = 0;
	}
};

class Solution
{
public:
	struct Edge
	{
		int neighbor;
		bool color;

		Edge() = default;
		Edge(int n, bool c) : neighbor(n), color(c) {}
		Edge(Edge &other) : neighbor(other.neighbor), color(other.color) {}
	};

	struct State
	{
		int node;
		bool lastColor;
		int distance;

		State(int node, bool lastColor, int distance) : node(node), lastColor(lastColor), distance(distance) {}
	};

	vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
	{
		// Adjacent list graph
		Vector<Vector<Edge>> graph(n);
		for (const auto &edge : redEdges)
		{
			graph[edge[0]].push_back({edge[1], 0});
		}
		for (const auto &edge : blueEdges)
		{
			graph[edge[0]].push_back({edge[1], 1});
		}

		// Result
		vector<int> result(n, -1);
		// Visited [node][color]
		vector<vector<bool>> visited(n, vector<bool>(2, false));

		Queue<State *> q(300);

		q.enqueue(new State({0, 0, 0}));
		q.enqueue(new State({0, 1, 0}));
		visited[0][0] = visited[0][1] = true;
		result[0] = 0;

		while (!q.isEmpty())
		{
			auto curr = q.front();
			q.dequeue();

			for (size_t i = 0; i < graph[curr->node].size(); ++i)
			{
				Edge edge = graph[curr->node][i];
				if (edge.color != curr->lastColor && !visited[edge.neighbor][edge.color])
				{
					visited[edge.neighbor][edge.color] = true;
					int nextDistance = 1 + curr->distance;
					q.enqueue(new State({edge.neighbor, edge.color, nextDistance}));
					if (result[edge.neighbor] == -1)
					{
						result[edge.neighbor] = nextDistance;
					}
				}
			}
		}
		return result;
	}
};
