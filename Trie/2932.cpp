#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TrieNode
{
public:
	TrieNode *children[2] = {nullptr, nullptr};
	vector<int> values;
};

class Trie
{
private:
	TrieNode *root;

	bool isStrongPair(int x, int y)
	{
		return abs(x - y) <= min(x, y);
	}

public:
	Trie()
	{
		root = new TrieNode();
	}

	void insert(int num)
	{
		TrieNode *node = root;
		for (int i = 31; i >= 0; --i)
		{
			int bit = (num >> i) & 1;
			if (!node->children[bit])
			{
				node->children[bit] = new TrieNode();
			}
			node = node->children[bit];
			node->values.push_back(num);
		}
	}

	int getMaxXOR(int num)
	{
		TrieNode *node = root;
		int maxXor = 0;

		for (int i = 31; i >= 0; --i)
		{
			int bit = (num >> i) & 1;
			int oppositeBit = 1 - bit;

			if (node->children[oppositeBit] && hasStrongPair(num, node->children[oppositeBit]->values))
			{
				node = node->children[oppositeBit];
			}
			else if (node->children[bit] && hasStrongPair(num, node->children[bit]->values))
			{
				node = node->children[bit];
			}
			else
			{
				break;
			}
		}

		if (node)
		{
			for (int val : node->values)
			{
				if (isStrongPair(num, val))
				{
					maxXor = max(maxXor, num ^ val);
				}
			}
		}

		return maxXor;
	}

private:
	bool hasStrongPair(int num, const vector<int> &values)
	{
		for (int val : values)
		{
			if (isStrongPair(num, val))
			{
				return true;
			}
		}
		return false;
	}
};

class Solution
{
public:
	int maximumStrongPairXor(vector<int> &nums)
	{
		int maxXOR = 0;
		Trie trie;

		for (int num : nums)
		{
			trie.insert(num);
		}

		for (int num : nums)
		{
			maxXOR = max(maxXOR, trie.getMaxXOR(num));
		}

		return maxXOR;
	}
};