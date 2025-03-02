#include <vector>
#include <string>
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
	bool equationsPossible(vector<string> &equations)
	{
		DisjointSet dsu(26);

		for (const string &eq : equations)
		{
			if (eq[1] == '=')
			{
				int u = eq[0] - 'a';
				int v = eq[3] - 'a';
				dsu.unionSets(u, v);
			}
		}

		for (const string &eq : equations)
		{
			if (eq[1] == '!')
			{
				int u = eq[0] - 'a';
				int v = eq[3] - 'a';
				if (dsu.findSet(u) == dsu.findSet(v))
				{
					return false;
				}
			}
		}

		return true;
	}
};
