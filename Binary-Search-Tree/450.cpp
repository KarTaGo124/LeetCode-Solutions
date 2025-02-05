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
public:
	TreeNode *findMin(TreeNode *root)
	{
		while (root && root->left)
			root = root->left;
		return root;
	}

	TreeNode *findMax(TreeNode *root)
	{
		while (root && root->right)
			root = root->right;
		return root;
	}

	TreeNode *findPredecessor(TreeNode *root, TreeNode *node)
	{
		if (node->left)
			return findMax(node->left);
		TreeNode *pred = nullptr;
		while (root)
		{
			if (node->val > root->val)
			{
				pred = root;
				root = root->right;
			}
			else if (node->val < root->val)
				root = root->left;
			else
				break;
		}
		return pred;
	}

	TreeNode *deleteNode(TreeNode *root, int key)
	{
		if (!root)
			return nullptr;
		if (key < root->val)
			root->left = deleteNode(root->left, key);
		else if (key > root->val)
			root->right = deleteNode(root->right, key);
		else
		{
			if (!root->left && !root->right)
			{ // Caso 1: Nodo hoja
				delete root;
				return nullptr;
			}
			else if (!root->left)
			{ // Caso 2: Un solo hijo derecho
				TreeNode *temp = root->right;
				delete root;
				return temp;
			}
			else if (!root->right)
			{ // Caso 2: Un solo hijo izquierdo
				TreeNode *temp = root->left;
				delete root;
				return temp;
			}
			else
			{ // Caso 3: Dos hijos
				TreeNode *temp = findPredecessor(root, root);
				root->val = temp->val;
				root->left = deleteNode(root->left, temp->val);
			}
		}
		return root;
	}
};