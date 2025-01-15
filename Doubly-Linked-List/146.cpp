struct Node
{
	int key;
	int val;
	Node *prev;
	Node *next;
	Node(int key, int val)
	{
		this->key = key;
		this->val = val;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

#include <unordered_map>

class LRUCache
{
private:
	int capacity;
	unordered_map<int, Node *> cache;
	Node *MRU;
	Node *LRU;

	void remove(Node *node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = nullptr;
		node->prev = nullptr;
	}

	void insert(Node *node)
	{
		MRU->prev->next = node;
		node->prev = MRU->prev;
		node->next = MRU;
		MRU->prev = node;
	}

public:
	LRUCache(int capacity)
	{
		this->capacity = capacity;
		MRU = new Node(0, 0);
		LRU = new Node(0, 0);
		MRU->prev = LRU;
		LRU->next = MRU;
	}

	int get(int key)
	{
		if (cache.find(key) != cache.end())
		{
			auto toMove = cache[key];
			remove(toMove);
			insert(toMove);
			return toMove->val;
		}
		return -1;
	}

	void put(int key, int value)
	{
		if (cache.find(key) != cache.end())
		{
			remove(cache[key]);
		}

		auto toInsert = new Node(key, value);
		cache[key] = toInsert;
		insert(toInsert);

		if (cache.size() > capacity)
		{
			auto toDelete = LRU->next;
			remove(toDelete);
			cache.erase(toDelete->key);
			delete toDelete;
		}
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */