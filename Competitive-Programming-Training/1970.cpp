class Solution
{
public:
	bool canCross(int row, int col, const vector<vector<int>> &cells, int day)
	{
		vector<vector<int>> grid(row, vector<int>(col, 0));

		for (int i = 0; i < day; i++)
		{
			int r = cells[i][0] - 1;
			int c = cells[i][1] - 1;
			grid[r][c] = 1;
		}

		queue<pair<int, int>> q;
		vector<vector<bool>> visited(row, vector<bool>(col, false));

		for (int c = 0; c < col; c++)
		{
			if (grid[0][c] == 0)
			{
				q.push({0, c});
				visited[0][c] = true;
			}
		}

		vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

		while (!q.empty())
		{
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			if (r == row - 1)
			{
				return true;
			}

			for (auto &dir : directions)
			{
				int nr = r + dir.first;
				int nc = c + dir.second;

				if (nr >= 0 && nr < row && nc >= 0 && nc < col && !visited[nr][nc] && grid[nr][nc] == 0)
				{
					visited[nr][nc] = true;
					q.push({nr, nc});
				}
			}
		}

		return false;
	}

	int latestDayToCross(int row, int col, vector<vector<int>> &cells)
	{
		int left = 1, right = cells.size();
		int answer = 0;

		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (canCross(row, col, cells, mid))
			{
				answer = mid;
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}

		return answer;
	}
};