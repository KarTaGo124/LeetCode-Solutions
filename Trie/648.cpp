//
// Created by Guillermo Galvez on 04/02/2025.
//

#include <iostream>
using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE]{};
	bool isEndOfWord;

	TrieNode()
	{
		isEndOfWord = false;
		for (auto &i : children)
		{
			i = nullptr;
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
	}

	void remove(const string &word)
	{
		TrieNode *node = root;
		for (char ch : word)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				return;
			}
			node = node->children[index];
		}
		node->isEndOfWord = false;
	}

	bool search(const string &word)
	{
		TrieNode *node = root;
		for (char ch : word)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				return false;
			}
			node = node->children[index];
		}
		return node->isEndOfWord;
	}

	bool startsWith(const string &prefix)
	{
		TrieNode *node = root;
		for (char ch : prefix)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				return false;
			}
			node = node->children[index];
		}
		return true;
	}

	string searchPrefix(const string &word)
	{
		TrieNode *node = root;
		string prefix;
		for (char ch : word)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				return "";
			}
			prefix += ch;
			node = node->children[index];
			if (node->isEndOfWord)
				return prefix;
		}
		return "";
	}
};

class Solution
{
public:
	string replaceWords(vector<string> &dictionary, string sentence)
	{
		Trie trie;

		for (auto word : dictionary)
		{
			trie.insert(word);
		}
		vector<string> words;
		string word;
		for (char c : sentence)
		{
			if (c == ' ')
			{
				words.push_back(word);
				word = "";
				continue;
			}
			word += c;
		}
		words.push_back(word);

		for (int i = 0; i < words.size(); i++)
		{
			string prefix = trie.searchPrefix(words[i]);
			if (prefix != "")
			{
				words[i] = prefix;
			}
		}

		string result;
		for (int i = 0; i < words.size() - 1; i++)
		{
			result += words[i] + " ";
		}
		result += words[words.size() - 1];
		return result;
	}
};