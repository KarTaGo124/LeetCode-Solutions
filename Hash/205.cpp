#include <iostream>
using namespace std;

struct Node
{
	char key;
	int value;
	Node *next;
	Node(char k, int v) : key(k), value(v), next(nullptr) {}
};

static const int SIZE = 100000;

int hashFunctionInt(int key)
{
	return key % SIZE;
}

int hashFunctionChar(const char key)
{
	int hash = 0;
	hash = (hash * 31 + key) % SIZE;
	return hash;
}

int hashFunctionString(const string &key)
{
	int hash = 0;
	for (char c : key)
	{
		hash = (hash * 31 + c) % SIZE;
	}
	return hash;
}

class Hash
{
private:
	Node *buckets[SIZE]{};

public:
	Hash()
	{
		for (auto &bucket : buckets)
		{
			bucket = nullptr;
		}
	}

	~Hash()
	{
		for (auto current : buckets)
		{
			while (current != nullptr)
			{
				Node *temp = current;
				current = current->next;
				delete temp;
			}
		}
	}

	void put(char key, int value)
	{
		int index = hashFunctionChar(key);
		Node *current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				current->value = value;
				return;
			}
			current = current->next;
		}
		Node *newNode = new Node(key, value);
		newNode->next = buckets[index];
		buckets[index] = newNode;
	}

	int get(char key)
	{
		int index = hashFunctionChar(key);
		Node *current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return current->value;
			}
			current = current->next;
		}
		return -1;
	}

	void remove(char key)
	{
		int index = hashFunctionChar(key);
		Node *current = buckets[index];
		Node *prev = nullptr;
		while (current != nullptr)
		{
			if (current->key == key)
			{
				if (prev != nullptr)
				{
					prev->next = current->next;
				}
				else
				{
					buckets[index] = current->next;
				}
				delete current;
				return;
			}
			prev = current;
			current = current->next;
		}
	}

	bool find(char key)
	{
		return get(key) != -1;
	}

	int size()
	{
		int count = 0;
		for (int i = 0; i < SIZE; i++)
		{
			Node *current = buckets[i];
			while (current != nullptr)
			{
				count++;
				current = current->next;
			}
		}
		return count;
	}

	void clear()
	{
		for (int i = 0; i < SIZE; i++)
		{
			Node *current = buckets[i];
			while (current != nullptr)
			{
				Node *temp = current;
				current = current->next;
				delete temp;
			}
			buckets[i] = nullptr;
		}
	}
};

class Solution
{
public:
	bool isIsomorphic(string s, string t)
	{
		Hash hash1;
		Hash hash2;
		if (s.length() != t.length())
			return false;
		for (int i = 0; i < s.length(); i++)
		{
			if (!hash1.find(s[i]))
			{
				hash1.put(s[i], i);
			}
			if (!hash2.find(t[i]))
			{
				hash2.put(t[i], i);
			}
			if (hash1.get(s[i]) != hash2.get(t[i]))
				return false;
		}
		return true;
	}
};