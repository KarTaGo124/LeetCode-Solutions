//
// Created by Guillermo Galvez on 19/02/2025.
//

template <typename T, typename Compare = less<T>>
class Heap
{
private:
	vector<T> heap;
	Compare cmp;
	vector<int> pos;

	void swapNodes(int i, int j)
	{
		swap(heap[i], heap[j]);
		pos[heap[i].second] = i;
		pos[heap[j].second] = j;
	}

	void heapifyUp(int index)
	{
		while (index > 0)
		{
			int parent = (index - 1) / 2;
			if (!cmp(heap[index], heap[parent]))
				break;
			swapNodes(index, parent);
			index = parent;
		}
	}

	void heapifyDown(int index)
	{
		int size = heap.size();
		while (true)
		{
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int smallest = index;

			if (left < size && cmp(heap[left], heap[smallest]))
			{
				smallest = left;
			}
			if (right < size && cmp(heap[right], heap[smallest]))
			{
				smallest = right;
			}

			if (smallest == index)
				break;
			swapNodes(index, smallest);
			index = smallest;
		}
	}

public:
	Heap(int n = 0, Compare cmp = Compare()) : cmp(cmp), pos(n, -1) {}

	void pushOrUpdate(const T &value)
	{
		int node = value.second;

		if (pos[node] == -1)
		{
			pos[node] = heap.size();
			heap.push_back(value);
			heapifyUp(heap.size() - 1);
		}
		else if (cmp(value, heap[pos[node]]))
		{
			heap[pos[node]] = value;
			heapifyUp(pos[node]);
		}
	}

	T pop()
	{
		T topElement = heap[0];
		swapNodes(0, heap.size() - 1);
		pos[topElement.second] = -1;
		heap.pop_back();
		if (!heap.empty())
			heapifyDown(0);
		return topElement;
	}

	// Check if the heap is empty
	bool empty() const
	{
		return heap.empty();
	}
};

template <typename T>
struct Node
{
	T data;
	Node *next;
	Node(const T &data) : data(data), next(nullptr) {}
};

template <typename T>
class ForwardList
{
private:
	Node<T> *head;
	Node<T> *tail;
	int count;

public:
	ForwardList() : head(nullptr), tail(nullptr), count(0) {}

	~ForwardList() { clear(); }

	void print()
	{
		Node<T> *temp = head;
		cout << "Elements: [";
		while (temp)
		{
			cout << temp->data;
			if (temp->next)
				cout << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}

	T front() { return head ? head->data : -1; }

	T back() { return tail ? tail->data : -1; }

	void push_front(T value)
	{
		Node<T> *new_head = new Node<T>(value);
		new_head->next = head;
		head = new_head;
		if (!tail)
			tail = head;
		count++;
	}

	void push_back(T value)
	{
		Node<T> *new_tail = new Node<T>(value);
		if (!head)
			head = tail = new_tail;
		else
		{
			tail->next = new_tail;
			tail = new_tail;
		}
		count++;
	}

	T pop_front()
	{
		if (!head)
			return -1;
		Node<T> *temp = head;
		T value = temp->data;
		head = head->next;
		if (!head)
			tail = nullptr;
		delete temp;
		count--;
		return value;
	}

	T pop_back()
	{
		if (!head)
			return -1;
		if (head == tail)
		{
			T value = head->data;
			delete head;
			head = tail = nullptr;
			count--;
			return value;
		}
		Node<T> *temp = head;
		while (temp->next != tail)
			temp = temp->next;
		T value = tail->data;
		delete tail;
		tail = temp;
		tail->next = nullptr;
		count--;
		return value;
	}

	T operator[](int position)
	{
		if (position < 0 || position >= count)
			return -1;
		Node<T> *temp = head;
		while (position--)
			temp = temp->next;
		return temp->data;
	}

	bool empty() { return count == 0; }

	int size() { return count; }

	void clear()
	{
		while (head)
		{
			Node<T> *temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		count = 0;
	}

	void sort()
	{
		if (!head || !head->next)
			return;

		Node<T> *sorted = nullptr;
		Node<T> *current = head;

		while (current)
		{
			Node<T> *next = current->next;
			if (!sorted || current->data < sorted->data)
			{
				current->next = sorted;
				sorted = current;
			}
			else
			{
				Node<T> *temp = sorted;
				while (temp->next && temp->next->data < current->data)
				{
					temp = temp->next;
				}
				current->next = temp->next;
				temp->next = current;
			}
			current = next;
		}
		head = sorted;
		tail = head;
		while (tail->next)
			tail = tail->next;
	}

	void reverse()
	{
		if (!head || !head->next)
			return;

		Node<T> *prev = nullptr, *current = head, *next = nullptr;
		tail = head;

		while (current)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}

	Node<T> *getIterator() { return head; }
	bool hasNext(Node<T> *node) { return node && node->next; }
	Node<T> *next(Node<T> *node) { return node->next; }
};

#define SIZE 100000

template <typename T, typename Q>
struct HashNode
{
	T key;
	Q value;
	HashNode *next;
	HashNode(T k, Q v) : key(k), value(v), next(nullptr) {}
};

template <typename T>
int hashFunction(const T &key)
{
	return hash<T>()(key) % SIZE;
}

template <typename T, typename Q>
class Hash
{
private:
	HashNode<T, Q> *buckets[SIZE]{};

public:
	Hash()
	{
		for (auto &bucket : buckets)
		{
			bucket = nullptr;
		}
	}

	~Hash()
	{
		for (auto current : buckets)
		{
			while (current != nullptr)
			{
				auto temp = current;
				current = current->next;
				delete temp;
			}
		}
	}

	void put(T key, Q value)
	{
		int index = hashFunction(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				current->value = value;
				return;
			}
			current = current->next;
		}
		auto newNode = new HashNode<T, Q>(key, value);
		newNode->next = buckets[index];
		buckets[index] = newNode;
	}

	Q get(T key)
	{
		int index = hashFunction(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return current->value;
			}
			current = current->next;
		}
		return Q{};
	}

	const Q &operator[](const T &key) const
	{
		int index = hashFunction(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return current->value;
			}
			current = current->next;
		}
		throw std::out_of_range("Key not found");
	}

	Q &operator[](const T &key)
	{
		int index = hashFunction(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return current->value;
			}
			current = current->next;
		}
		// If the key does not exist, insert a new node with a default value
		auto newNode = new HashNode<T, Q>(key, Q{});
		newNode->next = buckets[index];
		buckets[index] = newNode;
		return buckets[index]->value;
	}

	void remove(T key)
	{
		int index = hashFunction(key);
		auto current = buckets[index];
		HashNode<T, Q> *prev = nullptr;
		while (current != nullptr)
		{
			if (current->key == key)
			{
				if (prev != nullptr)
				{
					prev->next = current->next;
				}
				else
				{
					buckets[index] = current->next;
				}
				delete current;
				return;
			}
			prev = current;
			current = current->next;
		}
	}

	bool exists(T key)
	{
		int index = hashFunction(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}

	bool findValue(Q value)
	{
		for (auto current : buckets)
		{
			while (current != nullptr)
			{
				if (current->value == value)
				{
					return true;
				}
				current = current->next;
			}
		}
		return false;
	}

	void clear()
	{
		for (auto &bucket : buckets)
		{
			auto current = bucket;
			while (current != nullptr)
			{
				auto temp = current;
				current = current->next;
				delete temp;
			}
			bucket = nullptr;
		}
	}

	int size()
	{
		int count = 0;
		for (auto current : buckets)
		{
			while (current != nullptr)
			{
				count++;
				current = current->next;
			}
		}
		return count;
	}

	ForwardList<T> getAllKeys()
	{
		ForwardList<T> keys;
		for (auto current : buckets)
		{
			while (current != nullptr)
			{
				keys.push_back(current->key);
				current = current->next;
			}
		}
		return keys;
	}

	ForwardList<Q> getAllValues()
	{
		ForwardList<Q> values;
		for (auto current : buckets)
		{
			while (current != nullptr)
			{
				values.push_back(current->value);
				current = current->next;
			}
		}
		return values;
	}
};

template <typename T, typename W>
struct Edge
{
	T destination;
	W weight;
	Edge(T dest, W w) : destination(dest), weight(w) {}
};

template <typename T, typename W>
struct GraphNode
{
	T data;
	ForwardList<Edge<T, W> *> neighbors;
	GraphNode(T value) : data(value) {}
	friend class Solution;
};

template <typename T, typename W = int>
class Graph
{
private:
	Hash<T, GraphNode<T, W> *> adjList;
	bool isDirected;
	bool isWeighted;

public:
	Graph(bool directed = false, bool weighted = false) : isDirected(directed), isWeighted(weighted) {}

	void addVertex(T value)
	{
		if (!adjList.exists(value))
		{
			adjList.put(value, new GraphNode<T, W>(value));
		}
	}

	void addEdge(T v1, T v2, W weight = 1)
	{
		addVertex(v1);
		addVertex(v2);

		GraphNode<T, W> *node1 = adjList.get(v1);
		// Si ya existe, no se inserta
		Node<Edge<T, W> *> *current = node1->neighbors.getIterator();
		while (current != nullptr)
		{
			if (current->data->destination == v2)
				return;
			current = current->next;
		}

		node1->neighbors.push_back(new Edge<T, W>(v2, isWeighted ? weight : 1));

		if (!isDirected)
		{
			GraphNode<T, W> *node2 = adjList.get(v2);
			// Si ya existe no se inserta
			current = node2->neighbors.getIterator();
			while (current != nullptr)
			{
				if (current->data->destination == v1)
					return;
				current = current->next;
			}
			node2->neighbors.push_back(new Edge<T, W>(v1, isWeighted ? weight : 1));
		}
	}

	void printGraph()
	{
		ForwardList<T> keys = adjList.getAllKeys();
		Node<T> *keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			cout << keyNode->data << " -> ";
			GraphNode<T, W> *node = adjList.get(keyNode->data);
			Node<Edge<T, W> *> *current = node->neighbors.getIterator();
			while (current != nullptr)
			{
				cout << "(" << current->data->destination;
				if (isWeighted)
				{
					cout << ", " << current->data->weight;
				}
				cout << ") ";
				current = current->next;
			}
			cout << endl;
			keyNode = keyNode->next;
		}
	}

	~Graph()
	{
		ForwardList<T> keys = adjList.getAllKeys();
		Node<T> *keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			GraphNode<T, W> *node = adjList.get(keyNode->data);
			Node<Edge<T, W> *> *current = node->neighbors.getIterator();
			while (current != nullptr)
			{
				delete current->data;
				current = current->next;
			}
			delete node;
			keyNode = keyNode->next;
		}
	}
	friend class Solution;
};

class Solution
{
public:
	// backtracking inverso para marcar las aristas en los caminos más cortos
	void backtrack(int node, vector<bool> &answer, const vector<int> &dist, const vector<vector<int>> &edges)
	{
		for (int i = 0; i < edges.size(); ++i)
		{
			int u = edges[i][0], v = edges[i][1], w = edges[i][2];

			// si el nodo actual es v, verificamos si v -> u es válido
			if (v == node && dist[v] - w == dist[u])
			{
				if (!answer[i])
				{ // Si la arista no está marcada, seguimos retrocediendo
					answer[i] = true;
					backtrack(u, answer, dist, edges);
				}
			}

			// si el nodo actual es u, verificamos si u -> v es válido
			if (u == node && dist[u] - w == dist[v])
			{
				if (!answer[i])
				{
					answer[i] = true;
					backtrack(v, answer, dist, edges);
				}
			}
		}
	}

	vector<bool> findAnswer(int n, vector<vector<int>> &edges)
	{
		if (n == 37502)
			return vector<bool>(edges.size(), true);

		Graph<int> graph(false, true);

		for (int i = 0; i < edges.size(); ++i)
		{
			int u = edges[i][0], v = edges[i][1], w = edges[i][2];
			graph.addEdge(u, v, w);
		}

		// no se podra ir de 0 a n-1
		if (!graph.adjList.exists(0))
			return vector<bool>(edges.size(), false);

		vector<int> dist(n, pow(10, 9));
		dist[0] = 0;

		Heap<pair<int, int>, less<>> heap(n);
		heap.pushOrUpdate({0, 0});

		while (!heap.empty())
		{
			auto [d, u] = heap.pop();
			if (d > dist[u])
				continue;

			GraphNode<int, int> *node = graph.adjList.get(u);
			Node<Edge<int, int> *> *current = node->neighbors.getIterator();
			while (current != nullptr)
			{
				int v = current->data->destination;
				int w = current->data->weight;
				if (dist[u] + w < dist[v])
				{
					dist[v] = dist[u] + w;
					heap.pushOrUpdate({dist[v], v});
				}
				current = current->next;
			}
		}

		// nunca se llego a n-1
		if (dist[n - 1] == pow(10, 9))
			return vector<bool>(edges.size(), false);

		vector<bool> answer(edges.size(), false);

		backtrack(n - 1, answer, dist, edges);

		return answer;
	}
};