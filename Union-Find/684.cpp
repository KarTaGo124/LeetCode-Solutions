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
			parent[x] = findSet(parent[x]); // Path compression
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

class Solution
{
public:
	vector<vector<int>> kruskal(vector<vector<int>> aristas, int V)
	{
		DisjointSet ds(V + 1);
		vector<vector<int>> A;

		for (auto arista : aristas)
		{
			int u = arista[0];
			int v = arista[1];
			if (ds.findSet(u) != ds.findSet(v))
			{
				A.push_back({u, v});
				ds.unionSets(u, v);
			}
		}
		return A;
	}
	vector<int> findRedundantConnection(vector<vector<int>> &edges)
	{
		int n = edges.size();
		vector<vector<int>> kruskal_result = kruskal(edges, n);

		for (int i = 0; i < edges.size(); i++)
		{
			bool found = false;
			for (int j = 0; j < kruskal_result.size(); j++)
			{
				if (found)
					continue;
				if (edges[i][0] == kruskal_result[j][0] && edges[i][1] == kruskal_result[j][1])
					found = true;
			}
			if (!found)
				return edges[i];
		}

		return {};
	}
};