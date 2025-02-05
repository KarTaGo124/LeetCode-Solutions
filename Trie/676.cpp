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

	/*
	bool searchWithOneModification(string word) {
		for (int i = 0; i < word.size(); i++) {
			char originalChar = word[i];

			for (char c = 'a'; c <= 'z'; c++) {
				if (c == originalChar) continue;

				word[i] = c;
				if (search(word)) return true;
			}

			word[i] = originalChar;
		}
		return false;
	}
	*/

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
	bool searchWithOneModification(TrieNode *node, const string &word, int index, bool modified)
	{
		if (index == word.size())
		{
			return modified && node->isEndOfWord;
		}

		int charIndex = word[index] - 'a';
		if (node->children[charIndex])
		{
			if (searchWithOneModification(node->children[charIndex], word, index + 1, modified))
			{
				return true;
			}
		}

		if (!modified)
		{
			for (int i = 0; i < ALPHABET_SIZE; i++)
			{
				if (i != charIndex && node->children[i])
				{
					if (searchWithOneModification(node->children[i], word, index + 1, true))
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	bool searchWithOneModification(const string &word)
	{
		return searchWithOneModification(root, word, 0, false);
	}
};

class MagicDictionary
{
private:
	Trie trie;

public:
	MagicDictionary()
	{
	}

	void buildDict(vector<string> dictionary)
	{
		for (auto word : dictionary)
		{
			trie.insert(word);
		}
	}

	bool search(string searchWord)
	{
		return trie.searchWithOneModification(searchWord);
	}
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */