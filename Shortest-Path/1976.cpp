#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int MOD = 1e9 + 7;
const long long INF = LLONG_MAX;

// Generalized Heap template (MinHeap, MaxHeap, CustomHeap)
template <typename T, typename Compare = less<T>>
class Heap
{
private:
	vector<T> heap;	 // Stores the heap elements
	Compare cmp;	 // Comparator (customizable)
	vector<int> pos; // Tracks positions of elements

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
				break; // No violation
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
				break; // Already satisfies heap property
			swapNodes(index, smallest);
			index = smallest;
		}
	}

public:
	Heap(int n = 0, Compare cmp = Compare()) : cmp(cmp), pos(n, -1) {}

	// Insert or update an element
	void pushOrUpdate(const T &value)
	{
		int node = value.second;

		if (pos[node] == -1)
		{ // Node not present
			pos[node] = heap.size();
			heap.push_back(value);
			heapifyUp(heap.size() - 1);
		}
		else if (cmp(value, heap[pos[node]]))
		{ // Update if needed
			heap[pos[node]] = value;
			heapifyUp(pos[node]);
		}
	}

	// Extract the top element
	T pop()
	{
		T topElement = heap[0];
		swapNodes(0, heap.size() - 1);
		pos[topElement.second] = -1; // Mark as removed
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

class Solution
{
public:
	int countPaths(int n, vector<vector<int>> &roads)
	{
		vector<vector<pair<int, int>>> graph(n);

		for (const auto &road : roads)
		{
			int u = road[0], v = road[1], w = road[2];
			graph[u].emplace_back(v, w);
			graph[v].emplace_back(u, w);
		}

		vector<long long> dist(n, INF);
		vector<int> ways(n, 0); // Number of ways to reach each node
		dist[0] = 0;
		ways[0] = 1;

		// distance, node
		Heap<pair<long long, int>> heap(n);
		heap.pushOrUpdate({0, 0});

		while (!heap.empty())
		{
			auto [currDist, node] = heap.pop();

			for (const auto &[neighbor, weight] : graph[node])
			{
				long long newDist = currDist + weight;

				// if a shorter path is found
				if (newDist < dist[neighbor])
				{
					dist[neighbor] = newDist;
					ways[neighbor] = ways[node];
					heap.pushOrUpdate({newDist, neighbor});
				}
				// if another path with the same shortest distance is found
				else if (newDist == dist[neighbor])
				{
					ways[neighbor] = (ways[neighbor] + ways[node]) % MOD;
				}
			}
		}

		return ways[n - 1];
	}
};
