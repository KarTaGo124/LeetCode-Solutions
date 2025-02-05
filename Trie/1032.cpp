#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;

	TrieNode()
	{
		isEndOfWord = false;
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

	void insertReverse(const string &word)
	{
		TrieNode *node = root;
		for (int i = word.size() - 1; i >= 0; i--)
		{
			int index = word[i] - 'a';
			if (node->children[index] == nullptr)
			{
				node->children[index] = new TrieNode();
			}
			node = node->children[index];
		}
		node->isEndOfWord = true;
	}

	bool searchSuffix(string stream)
	{
		TrieNode *node = root;
		for (char ch : stream)
		{
			int index = ch - 'a';
			if (node->children[index] == nullptr)
			{
				return false;
			}
			node = node->children[index];
			if (node->isEndOfWord)
			{
				return true;
			}
		}
		return false;
	}
};

class StreamChecker
{
private:
	Trie trie;
	string stream;
	int maxLength;

public:
	StreamChecker(vector<string> &words)
	{
		maxLength = 0;
		for (const string &word : words)
		{
			trie.insertReverse(word);
			maxLength = max(maxLength, (int)word.size());
		}
	}

	bool query(char letter)
	{
		stream = letter + stream;
		if (stream.size() > maxLength)
		{
			stream.pop_back();
		}
		return trie.searchSuffix(stream);
	}
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */