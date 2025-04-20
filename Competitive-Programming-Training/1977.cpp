class Solution
{
public:
	static const int MOD = 1000000007;

	int numberOfCombinations(const string &s)
	{
		int n = s.size();
		vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));
		for (int i = n - 1; i >= 0; --i)
		{
			for (int j = n - 1; j >= 0; --j)
			{
				if (s[i] == s[j])
				{
					lcp[i][j] = lcp[i + 1][j + 1] + 1;
				}
			}
		}

		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
		vector<vector<int>> pre(n + 1, vector<int>(n + 1, 0));

		for (int i = 1; i <= n; ++i)
		{
			for (int l = 1; l <= i; ++l)
			{
				int start = i - l;
				if (s[start] == '0')
				{
					dp[i][l] = 0;
				}
				else if (start == 0)
				{
					dp[i][l] = 1;
				}
				else
				{
					long long ways = 0;
					int maxk = min(i - l, l - 1);
					if (maxk >= 1)
						ways += pre[i - l][maxk];
					if (i - l >= l)
					{
						int prev = i - 2 * l;
						int common = lcp[prev][start];
						if (common >= l || s[prev + common] <= s[start + common])
							ways += dp[i - l][l];
					}
					dp[i][l] = ways % MOD;
				}
				pre[i][l] = (pre[i][l - 1] + dp[i][l]) % MOD;
			}
		}

		return pre[n][n];
	}
};
