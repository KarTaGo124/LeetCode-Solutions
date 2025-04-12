class Solution
{
public:
	TreeNode *canMerge(vector<TreeNode *> &trees)
	{
		unordered_map<int, TreeNode *> roots;
		unordered_map<int, pair<TreeNode *, bool>> leaves;
		unordered_set<int> allValues;

		// Construcción de mapas
		for (TreeNode *root : trees)
		{
			roots[root->val] = root;
			allValues.insert(root->val);

			if (root->left)
			{
				leaves[root->left->val] = {root, true};
				allValues.insert(root->left->val);
			}

			if (root->right)
			{
				leaves[root->right->val] = {root, false};
				allValues.insert(root->right->val);
			}
		}

		// Identificación de la raíz final, la cual es la que no aparece como hoja en otro árbol
		TreeNode *finalRoot = nullptr;
		for (TreeNode *root : trees)
		{
			if (leaves.find(root->val) == leaves.end())
			{
				if (finalRoot)
					return nullptr;
				finalRoot = root;
			}
		}

		if (!finalRoot)
			return nullptr;

		// Fusión de árboles
		for (TreeNode *root : trees)
		{
			if (root == finalRoot)
				continue;

			auto it = leaves.find(root->val);
			if (it == leaves.end())
				return nullptr;

			auto [parent, isLeft] = it->second;
			if (isLeft)
			{
				parent->left = root;
			}
			else
			{
				parent->right = root;
			}
		}

		// Verificación del BST resultante
		vector<int> inorder;
		inorderTraversal(finalRoot, inorder);

		if (inorder.size() != allValues.size())
			return nullptr;

		for (int i = 1; i < inorder.size(); i++)
		{
			if (inorder[i] <= inorder[i - 1])
				return nullptr;
		}

		return finalRoot;
	}

private:
	void inorderTraversal(TreeNode *root, vector<int> &result)
	{
		if (!root)
			return;
		inorderTraversal(root->left, result);
		result.push_back(root->val);
		inorderTraversal(root->right, result);
	}
};