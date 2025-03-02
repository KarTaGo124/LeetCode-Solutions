#define ALPHABET_SIZE 26

// Definición básica del nodo del Trie.
struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	bool isWord;
	TrieNode() : isWord(false)
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
			children[i] = nullptr;
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
	// Inserta una palabra en el Trie.
	void insert(const string &word)
	{
		TrieNode *curr = root;
		for (char c : word)
		{
			int idx = c - 'a';
			if (curr->children[idx] == nullptr)
				curr->children[idx] = new TrieNode();
			curr = curr->children[idx];
		}
		curr->isWord = true;
	}
	TrieNode *getRoot()
	{
		return root;
	}
};

class Solution
{
public:
	bool wordBreak(string s, vector<string> &wordDict)
	{
		Trie trie;
		// Construimos el Trie con todas las palabras del diccionario.
		for (const string &word : wordDict)
			trie.insert(word);

		// Vector de memoización: -1 sin calcular, 1 significa segmentable, 0 no segmentable.
		vector<int> memo(s.size(), -1);
		return dfs(s, 0, trie.getRoot(), memo);
	}

private:
	// Función DFS con memoización para verificar si s[pos:] se puede segmentar.
	bool dfs(const string &s, int pos, TrieNode *root, vector<int> &memo)
	{
		if (pos == s.size())
			return true;
		if (memo[pos] != -1)
			return memo[pos] == 1;

		TrieNode *curr = root;
		for (int i = pos; i < s.size(); i++)
		{
			int idx = s[i] - 'a';
			if (curr->children[idx] == nullptr)
				break; // No existe un prefijo que continúe.
			curr = curr->children[idx];
			if (curr->isWord)
			{
				// Si s[pos...i] es una palabra válida, intentamos segmentar el resto.
				if (dfs(s, i + 1, root, memo))
				{
					memo[pos] = 1;
					return true;
				}
			}
		}
		memo[pos] = 0;
		return false;
	}
};
