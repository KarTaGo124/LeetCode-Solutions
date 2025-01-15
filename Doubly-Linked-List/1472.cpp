struct Node
{
	string url;
	Node *prev;
	Node *next;
	Node(string url)
	{
		this->url = url;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

class BrowserHistory
{
private:
	Node *headPage;
	Node *currentPage;

public:
	BrowserHistory(string homepage)
	{
		this->headPage = new Node(homepage);
		currentPage = headPage;
	}

	int size()
	{
		auto temp = currentPage;
		int i = 0;
		while (temp != nullptr)
		{
			temp = temp->next;
			i++;
		}
		return i;
	}

	void post_cleaning(Node *node)
	{
		while (node->next != nullptr)
		{
			auto nextNode = node->next->next;
			delete node->next;
			node->next = nextNode;
		}
	}
	void visit(string url)
	{
		auto newPage = new Node(url);
		post_cleaning(currentPage);
		currentPage->next = newPage;
		newPage->prev = currentPage;
		currentPage = newPage;
	}

	string back(int steps)
	{
		int possibleSteps = 0;
		auto temp = headPage;
		while (temp != currentPage)
		{
			possibleSteps++;
			temp = temp->next;
		}
		if (steps > possibleSteps)
			steps = possibleSteps;
		for (int i = 0; i < steps; i++)
		{
			currentPage = currentPage->prev;
		}
		return currentPage->url;
	}

	string forward(int steps)
	{
		int possibleSteps = 0;
		auto temp = currentPage;
		while (temp->next != nullptr)
		{
			possibleSteps++;
			temp = temp->next;
		}
		if (steps > possibleSteps)
			steps = possibleSteps;
		for (int i = 0; i < steps; i++)
		{
			currentPage = currentPage->next;
		}
		return currentPage->url;
	}
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */