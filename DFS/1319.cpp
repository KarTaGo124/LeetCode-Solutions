class Solution
{
public:
	void dfs(int source, const vector<vector<int>> &graph, vector<bool> &visited)
	{
		if (visited[source])
			return;
		visited[source] = true;
		vector<int> neighbours = graph[source];
		for (auto neighbour : neighbours)
		{
			if (!visited[neighbour])
			{
				dfs(neighbour, graph, visited);
			}
		}
	}
	int makeConnected(int n, vector<vector<int>> &connections)
	{
		if (connections.size() < n - 1)
			return -1;

		vector<vector<int>> graph(n);

		for (auto connection : connections)
		{
			int u = connection[0];
			int v = connection[1];
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		vector<bool> visited(n, false);

		int countDFS = 0;
		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
			{
				dfs(i, graph, visited);
				countDFS++;
			}
		}
		return countDFS - 1;
	}
};