#ifndef ALGORITHMS_AND_DATA_STRUCTURES_HASH_H
#define ALGORITHMS_AND_DATA_STRUCTURES_HASH_H

#include <iostream>
using namespace std;

template <typename T, typename Q>
struct Node
{
	T key;
	int value;
	Node *next;
	Node(T k, Q v) : key(k), value(v), next(nullptr) {}
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

template <typename T, typename Q>
class Hash
{
private:
	Node<T, Q> *buckets[SIZE]{};

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
				auto temp = current;
				current = current->next;
				delete temp;
			}
		}
	}

	void put(T key, int value)
	{
		int index = hashFunctionInt(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				current->value = value;
				return;
			}
			current = current->next;
		}
		auto newNode = new Node<T, Q>(key, value);
		newNode->next = buckets[index];
		buckets[index] = newNode;
	}

	Q get(T key)
	{
		int index = hashFunctionInt(key);
		auto current = buckets[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return current->value;
			}
			current = current->next;
		}
		return 0;
	}

	void remove(T key)
	{
		int index = hashFunctionInt(key);
		auto current = buckets[index];
		Node<T, Q> *prev = nullptr;
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

	bool findValue(Q value)
	{
		for (int i = 0; i < SIZE; i++)
		{
			auto current = buckets[i];
			while (current != nullptr)
			{
				if (current->value == value)
				{
					return true;
				}
				current = current->next;
			}
		}
		return false;
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
			auto current = bucket;
			while (current != nullptr)
			{
				auto temp = current;
				current = current->next;
				delete temp;
			}
			bucket = nullptr;
		}
	}
};

#endif // ALGORITHMS_AND_DATA_STRUCTURES_HASH_H

class Solution
{
public:
	string getHint(string secret, string guess)
	{
		Hash<char, int> hashSecret;
		Hash<char, int> hashGuess;

		int countBulls = 0;
		int countCows = 0;
		for (int i = 0; i < secret.size(); i++)
		{
			if (secret[i] == guess[i])
				countBulls++;
			else
			{
				hashSecret.put(secret[i], hashSecret.get(secret[i]) + 1);
				hashGuess.put(guess[i], hashGuess.get(guess[i]) + 1);
			}
		}

		for (int i = 0; i < guess.size(); i++)
		{
			if (secret[i] != guess[i])
			{
				if (hashSecret.get(guess[i]) > 0)
				{
					countCows++;
					hashSecret.put(guess[i], hashSecret.get(guess[i]) - 1);
				}
			}
		}

		string result = to_string(countBulls) + "A" + to_string(countCows) + "B";
		return result;
	}
};