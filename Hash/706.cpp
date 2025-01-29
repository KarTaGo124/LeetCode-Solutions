#include <cmath>
using namespace std;

struct Node
{
	int key, value;
	Node *next;
	Node(int k, int v) : key(k), value(v), next(nullptr) {}
};

static const int SIZE = 100000;

int hashFunction(int key)
{
	return key % SIZE;
}

class MyHashMap
{
private:
	Node *buckets[SIZE];

public:
	MyHashMap()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			buckets[i] = nullptr;
		}
	}

	~MyHashMap()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			Node *current = buckets[i];
			while (current != nullptr)
			{
				Node *temp = current;
				current = current->next;
				delete temp;
			}
		}
	}

	void put(int key, int value)
	{
		int index = hashFunction(key);
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

	int get(int key)
	{
		int index = hashFunction(key);
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

	void remove(int key)
	{
		int index = hashFunction(key);
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
};
