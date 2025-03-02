#include <iostream>
using namespace std;

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
};

template <typename T, typename W = int>
class Graph
{
private:
	Hash<T, GraphNode<T, W> *> adjList;
	Hash<T, int> colors; // 0: Blanco, 1: Gris, 2: Negro
	Hash<T, int> discoveryTime;
	Hash<T, int> finishTime;
	Hash<T, T> parent;
	int time;
	bool isDirected;
	bool isWeighted;

	void DFSVisit(T u)
	{
		colors.put(u, 1); // Gris: visitado pero no finalizado
		time++;
		discoveryTime.put(u, time);

		GraphNode<T, W> *node = adjList.get(u);
		Node<Edge<T, W> *> *current = node->neighbors.getIterator();
		while (current != nullptr)
		{
			T v = current->data->destination;
			if (!colors.exists(v) || colors.get(v) == 0)
			{
				parent.put(v, u);
				DFSVisit(v);
			}
			current = current->next;
		}

		colors.put(u, 2); // Negro: finalizado
		time++;
		finishTime.put(u, time);
	}

public:
	Graph(bool directed = false, bool weighted = false) : isDirected(directed), isWeighted(weighted), time(0) {}

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

	void initializeColors()
	{
		ForwardList<T> keys = adjList.getAllKeys();
		Node<T> *keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			colors.put(keyNode->data, 0);	// Blanco: No visitado
			parent.put(keyNode->data, T()); // Nil
			keyNode = keyNode->next;
		}
		time = 0;
	}

	void DFSFrom(T start)
	{
		if (!adjList.exists(start))
			return;
		DFSVisit(start);
	}

	int getColor(T node)
	{
		return colors.exists(node) ? colors.get(node) : 0;
	}

	void DFS()
	{
		ForwardList<T> keys = adjList.getAllKeys();
		Node<T> *keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			colors.put(keyNode->data, 0);	// Inicialmente, todos los nodos son blancos
			parent.put(keyNode->data, T()); // nullptr
			keyNode = keyNode->next;
		}
		time = 0;
		keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			if (colors.get(keyNode->data) == 0)
			{
				DFSVisit(keyNode->data);
			}
			keyNode = keyNode->next;
		}
	}

	void printDFSInfo()
	{
		cout << "Nodo | Descubrimiento | Finalización | Padre" << endl;
		cout << "--------------------------------------" << endl;
		ForwardList<T> keys = adjList.getAllKeys();
		Node<T> *keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			T node = keyNode->data;
			cout << node << "\t " << discoveryTime.get(node) << "\t\t "
				 << finishTime.get(node) << "\t\t ";
			if (parent.get(node) == T())
				cout << "-";
			else
				cout << parent.get(node);
			cout << endl;
			keyNode = keyNode->next;
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

	void DFSFromAlternative(T source, Hash<T, bool> &visited)
	{
		if (visited.exists(source) && visited.get(source))
			return;
		visited.put(source, true);
		GraphNode<T, W> *node = adjList.get(source);
		Node<Edge<T, W> *> *current = node->neighbors.getIterator();
		while (current != nullptr)
		{
			DFSFromAlternative(current->data->destination, visited);
			current = current->next;
		}
	}

	void DFSAlternative(Hash<T, bool> &visited)
	{
		ForwardList<T> keys = adjList.getAllKeys();
		Node<T> *keyNode = keys.getIterator();
		while (keyNode != nullptr)
		{
			if (!visited.exists(keyNode->data) || !visited.get(keyNode->data))
			{
				DFSVisitAlternative(keyNode->data, visited);
			}
			keyNode = keyNode->next;
		}
	}

	void DFSVisitAlternative(T node, Hash<T, bool> &visited)
	{
		visited.put(node, true); // Mark as visited
		GraphNode<T, W> *graphNode = adjList.get(node);
		Node<Edge<T, W> *> *current = graphNode->neighbors.getIterator();
		while (current != nullptr)
		{
			if (!visited.exists(current->data->destination) || !visited.get(current->data->destination))
			{
				DFSVisitAlternative(current->data->destination, visited);
			}
			current = current->next;
		}
	}
	friend class Solution;
};

class Solution
{
public:
	bool possibleBipartition(int n, vector<vector<int>> &dislikes)
	{
		Graph<int> graph(false);
		Hash<int, int> color;

		for (const auto &d : dislikes)
		{
			graph.addEdge(d[0], d[1]);
		}

		for (int i = 1; i <= n; i++)
		{
			if (!color.exists(i))
			{
				color.put(i, 0); // Intentar con color 0
				if (!isValidColoring(i, graph, color))
				{
					return false;
				}
			}
		}
		return true;
	}

private:
	bool isValidColoring(int node, Graph<int> &graph, Hash<int, int> &color)
	{
		GraphNode<int, int> *current = graph.adjList.get(node);
		if (!current)
			return true;

		Node<Edge<int, int> *> *edge = current->neighbors.getIterator();
		while (edge != nullptr)
		{
			int next = edge->data->destination;

			if (!color.exists(next))
			{
				color.put(next, 1 - color.get(node));
				if (!isValidColoring(next, graph, color))
				{
					return false;
				}
			}
			else if (color.get(next) == color.get(node))
			{
				return false;
			}
			edge = edge->next;
		}
		return true;
	}
};