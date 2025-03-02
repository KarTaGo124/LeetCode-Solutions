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

	// Getter para acceder a la raíz (necesario para la DFS)
	TrieNode *getRoot()
	{
		return root;
	}
};

class Solution
{

public:
	string longestWord(vector<string> &words)
	{
		Trie trie;
		// Insertamos todas las palabras en el Trie
		for (const auto &word : words)
			trie.insert(word);

		string ans = "";
		// Empezamos la DFS desde la raíz con la cadena vacía.
		dfs(trie.getRoot(), "", ans);
		return ans;
	}

	// DFS que recorre el Trie y construye palabras válidas.
	// Sólo avanza por nodos que terminan una palabra (isEndOfWord true),
	// exceptuando la raíz.
	void dfs(TrieNode *node, string current, string &ans)
	{
		// Actualizamos la respuesta si encontramos una palabra más larga o
		// igual en longitud pero lexicográficamente menor.
		if (current.size() > ans.size() || (current.size() == ans.size() && current < ans))
			ans = current;

		// Recorremos los hijos en orden alfabético para asegurar el criterio lexicográfico.
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (node->children[i] && node->children[i]->isEndOfWord)
			{
				char c = 'a' + i;
				dfs(node->children[i], current + c, ans);
			}
		}
	}
};