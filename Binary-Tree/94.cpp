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
class Solution
{
private:
	vector<int> values;

public:
	vector<int> inorderTraversal(TreeNode *root)
	{
		if (root == nullptr)
			return values;
		inorderTraversal(root->left);
		values.push_back(root->val);
		inorderTraversal(root->right);
		return values;
	}
};