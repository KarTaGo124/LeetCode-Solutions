class Solution
{
public:
	void dfs(const vector<vector<int>> &graph, int source, unordered_map<int, bool> &visited)
	{
		if (visited[source])
			return;
		visited[source] = true;
		vector<int> neighbours = graph[source];
		for (auto neighbour : neighbours)
		{
			if (!visited[neighbour])
				dfs(graph, neighbour, visited);
		}
	}
	int findCircleNum(vector<vector<int>> &isConnected)
	{
		int n = isConnected.size();
		vector<vector<int>> graph(n);

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (isConnected[i][j] == 1)
				{
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			graph[i].push_back(i);
		}

		for (int i = 0; i < n; i++)
		{
			for (auto vertex : graph[i])
			{
				cout << i + 1 << "--" << vertex + 1 << endl;
			}
		}
		unordered_map<int, bool> visited;
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
			{
				dfs(graph, i, visited);
				count++;
			}
		}
		return count;
	}
};