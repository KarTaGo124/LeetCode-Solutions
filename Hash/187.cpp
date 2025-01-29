#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Node
{
	T key;
	int value;
	Node *next;
	Node(T k, int v) : key(k), value(v), next(nullptr) {}
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

template <typename T>
class Hash
{
private:
	Node<T> *buckets[SIZE]{};

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
				Node<T> *temp = current;
				current = current->next;
				delete temp;
			}
		}
	}

	void put(T key, int value)
	{
		int index = hashFunctionString(key);
		Node<T> *current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				current->value = value;
				return;
			}
			current = current->next;
		}
		auto newNode = new Node<T>(key, value);
		newNode->next = buckets[index];
		buckets[index] = newNode;
	}

	int get(T key)
	{
		int index = hashFunctionString(key);
		Node<T> *current = buckets[index];
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

	void remove(T key)
	{
		int index = hashFunctionString(key);
		Node<T> *current = buckets[index];
		Node<T> *prev = nullptr;
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

	bool find(T key)
	{
		return get(key) != -1;
	}

	int size()
	{
		int count = 0;
		for (auto current : buckets)
		{
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
		for (auto &bucket : buckets)
		{
			Node<T> *current = bucket;
			while (current != nullptr)
			{
				Node<T> *temp = current;
				current = current->next;
				delete temp;
			}
			bucket = nullptr;
		}
	}
};

class Solution
{
public:
	vector<string> findRepeatedDnaSequences(string s)
	{
		Hash<string> hash;
		vector<string> cadenas;
		if (s.length() < 10)
			return cadenas;
		for (int i = 0; i <= s.length() - 10; i++)
		{
			string substring = s.substr(i, 10);
			if (hash.find(substring))
			{
				if (hash.get(substring) == 1)
				{
					if (find(cadenas.begin(), cadenas.end(), substring) == cadenas.end())
					{
						cadenas.push_back(substring);
					}
				}
			}
			else
			{
				hash.put(substring, 1);
			}
		}
		return cadenas;
	}
};