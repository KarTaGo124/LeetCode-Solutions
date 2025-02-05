#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
	int frequency;

	TrieNode()
	{
		isEndOfWord = false;
		frequency = 0;
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
		}
		node->isEndOfWord = true;
		node->frequency++;
	}

	void dfs(TrieNode *node, string currentWord, vector<pair<int, string>> &wordList)
	{
		if (node == nullptr)
			return;

		if (node->isEndOfWord)
		{
			wordList.emplace_back(node->frequency, currentWord);
		}

		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (node->children[i] != nullptr)
			{
				dfs(node->children[i], currentWord + char('a' + i), wordList);
			}
		}
	}

	vector<string> getTopKFrequentWords(int k)
	{
		vector<pair<int, string>> wordList;
		dfs(root, "", wordList);

		sort(wordList.begin(), wordList.end(), [](const pair<int, string> &a, const pair<int, string> &b)
			 {
            if (a.first == b.first)
                return a.second < b.second;
            return a.first > b.first; });

		vector<string> result;
		for (int i = 0; i < k && i < wordList.size(); i++)
		{
			result.push_back(wordList[i].second);
		}

		return result;
	}
};

class Solution
{
public:
	vector<string> topKFrequent(vector<string> &words, int k)
	{
		Trie trie;
		for (const string &word : words)
		{
			trie.insert(word);
		}
		return trie.getTopKFrequentWords(k);
	}
};