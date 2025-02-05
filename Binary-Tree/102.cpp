/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

void BFS(TreeNode *root)
{
	if (!root)
		return;
	std::queue<TreeNode *> q;
	q.push(root);
	while (!q.empty())
	{
		TreeNode *node = q.front();
		q.pop();
		printf("%d ", node->val);
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}
}
class Solution
{
private:
	vector<vector<int>> values{};

public:
	vector<vector<int>> levelOrder(TreeNode *root)
	{
		if (root == nullptr)
			return values;
		std::queue<TreeNode *> q;
		q.push(root);
		while (!q.empty())
		{
			int levelSize = q.size();
			vector<int> currentLevel;
			for (int i = 0; i < levelSize; ++i)
			{
				TreeNode *node = q.front();
				q.pop();
				currentLevel.push_back(node->val);

				if (node->left)
					q.push(node->left);
				if (node->right)
					q.push(node->right);
			}
			values.push_back(currentLevel);
		}
		return values;
	}
};