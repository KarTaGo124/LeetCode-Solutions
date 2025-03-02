#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
	double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start_node, int end_node)
	{
		vector<double> prob(n, 0.0);
		prob[start_node] = 1.0;

		// Bellman-Ford: relaja todas las aristas n-1 veces
		for (int i = 0; i < n - 1; ++i)
		{
			bool updated = false;
			for (int j = 0; j < edges.size(); ++j)
			{
				int u = edges[j][0];
				int v = edges[j][1];
				double weight = succProb[j];

				// relaja en ambas direcciones (grafo no dirigido)
				if (prob[u] * weight > prob[v])
				{
					prob[v] = prob[u] * weight;
					updated = true;
				}
				if (prob[v] * weight > prob[u])
				{
					prob[u] = prob[v] * weight;
					updated = true;
				}
			}
			if (!updated)
				break;
		}

		return prob[end_node];
	}
};
