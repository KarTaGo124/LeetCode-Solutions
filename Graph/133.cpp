/*
// Definition for a Node.
class Node {
public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
	friend class Solution;
};
*/

class Solution
{
public:
	unordered_map<Node *, Node *> clonedNodes;

	Node *cloneGraph(Node *node)
	{
		if (node == nullptr)
			return nullptr;

		if (clonedNodes.find(node) != clonedNodes.end())
		{
			return clonedNodes[node];
		}

		Node *clonedNode = new Node(node->val);
		clonedNodes[node] = clonedNode;

		for (Node *neighbor : node->neighbors)
		{
			clonedNode->neighbors.push_back(cloneGraph(neighbor));
		}

		return clonedNode;
	}
};