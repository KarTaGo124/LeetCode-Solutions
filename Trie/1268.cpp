#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	vector<string> suggestions;

	TrieNode()
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			children[i] = nullptr;
		}
	}
};

class Trie
{
private:
	TrieNode *root;

public:
	Trie()
	{
		root = new TrieNode();
	}

	void insert(const string &word)
	{
		TrieNode *node = root;
		for (char ch : word)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				node->children[index] = new TrieNode();
			}
			node = node->children[index];

			if (node->suggestions.size() < 3)
			{
				node->suggestions.push_back(word);
			}
		}
	}

	vector<vector<string>> getSuggestions(const string &searchWord)
	{
		vector<vector<string>> result;
		TrieNode *node = root;

		for (char ch : searchWord)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				break;
			}
			node = node->children[index];
			result.push_back(node->suggestions);
		}

		while (result.size() < searchWord.size())
		{
			result.push_back({});
		}

		return result;
	}
};

class Solution
{
public:
	vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord)
	{
		Trie trie;

		sort(products.begin(), products.end());

		for (const string &product : products)
		{
			trie.insert(product);
		}

		return trie.getSuggestions(searchWord);
	}
};
