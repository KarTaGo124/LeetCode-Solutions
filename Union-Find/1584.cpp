#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class DisjointSet
{
	int *parent, *rank;

public:
	explicit DisjointSet(const int &n) : parent(new int[n]), rank(new int[n])
	{
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
			rank[i] = 0;
		}
	}

	~DisjointSet()
	{
		delete[] parent;
		delete[] rank;
	}

	int findSet(const int &x)
	{
		if (parent[x] != x)
		{
			parent[x] = findSet(parent[x]); // Compresión de caminos
		}
		return parent[x];
	}

	bool unionSets(const int &x, const int &y)
	{
		const int xRoot = findSet(x);
		const int yRoot = findSet(y);
		if (xRoot == yRoot)
			return false;

		if (rank[xRoot] < rank[yRoot])
		{
			parent[xRoot] = yRoot;
		}
		else if (rank[xRoot] > rank[yRoot])
		{
			parent[yRoot] = xRoot;
		}
		else
		{
			parent[yRoot] = xRoot;
			rank[xRoot]++;
		}
		return true;
	}
};

struct Edge
{
	int u, v, weight;
};

class Solution
{
public:
	int minCostConnectPoints(vector<vector<int>> &points)
	{
		int n = points.size();
		vector<Edge> edges;

		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				int weight = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
				edges.push_back({i, j, weight});
			}
		}

		sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
			 { return a.weight < b.weight; });

		DisjointSet ds(n);
		int mst_cost = 0;
		for (const auto &edge : edges)
		{
			if (ds.findSet(edge.u) != ds.findSet(edge.v))
			{
				ds.unionSets(edge.u, edge.v);
				mst_cost += edge.weight;
			}
		}

		return mst_cost;
	}
};