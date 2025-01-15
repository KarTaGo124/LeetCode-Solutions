struct Node
{
	string tokenId;
	int insertedTime;
	Node *prev;
	Node *next;
	Node(string tokenId, int currentTime)
	{
		this->tokenId = tokenId;
		this->insertedTime = currentTime;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

#include <unordered_map>

class AuthenticationManager
{
private:
	int timeToLive;
	unordered_map<string, Node *> cache;
	Node *head;
	Node *tail;
	int size;

	void remove(Node *node)
	{
		if (!node || node == head || node == tail)
			return;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		size--;
	}

	void insert(Node *node)
	{
		node->next = head;
		node->prev = head->prev;
		head->prev->next = node;
		head->prev = node;
		size++;
	}

	void cleanUp(int currentTime)
	{
		Node *temp = tail->next;
		while (temp != head && temp->insertedTime + timeToLive <= currentTime)
		{
			Node *toDelete = temp;
			temp = temp->next;
			remove(toDelete);
		}
	}

public:
	AuthenticationManager(int timeToLive)
	{
		this->timeToLive = timeToLive;
		head = new Node("", 0);
		tail = new Node("", 0);
		head->prev = tail;
		tail->next = head;
		size = 0;
	}

	void generate(string tokenId, int currentTime)
	{
		if (cache.find(tokenId) != cache.end())
		{
			remove(cache[tokenId]);
			cache.erase(tokenId);
		}
		auto newNode = new Node(tokenId, currentTime);
		insert(newNode);
		cache[tokenId] = newNode;
	}

	void renew(string tokenId, int currentTime)
	{
		if (cache.find(tokenId) != cache.end())
		{
			auto node = cache[tokenId];
			if (node->insertedTime + timeToLive > currentTime)
			{
				remove(node);
				node->insertedTime = currentTime;
				insert(node);
			}
		}
	}

	int countUnexpiredTokens(int currentTime)
	{
		cleanUp(currentTime);
		return size;
	}
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */