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

//
// Created by Guillermo Galvez on 19/01/2025.
//

class Solution
{
private:
	int sum = 0;

public:
	TreeNode *convertBST(TreeNode *root)
	{
		if (root == nullptr)
			return nullptr;
		convertBST(root->right);

		sum += root->val;
		root->val = sum;

		convertBST(root->left);
		return root;
	}
};
