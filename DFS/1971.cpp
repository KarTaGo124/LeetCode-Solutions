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
	bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
	{
		if (source == destination)
			return true;
		unordered_map<int, bool> visited;
		vector<vector<int>> graph(n); // adjList

		for (const auto &edge : edges)
		{
			int u = edge[0];
			int v = edge[1];
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		dfs(graph, source, visited);

		return visited[destination];
	}
};