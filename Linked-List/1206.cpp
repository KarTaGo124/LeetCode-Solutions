struct Node
{
	int value;
	Node *next;
	Node *down;

	Node(int val = 0, Node *next = nullptr, Node *down = nullptr)
		: value(val), next(next), down(down) {}
};

class Skiplist
{
private:
	Node *head;

public:
	Skiplist() : head(new Node(0)) {}

	bool search(int target)
	{
		Node *current = head;

		while (current != nullptr)
		{
			while (current->next != nullptr && current->next->value < target)
			{
				current = current->next;
			}

			if (current->next != nullptr && current->next->value == target)
			{
				return true;
			}

			current = current->down;
		}

		return false;
	}

	void add(int num)
	{
		Node *stack[64];
		int level = 0;
		Node *current = head;

		while (current != nullptr)
		{
			while (current->next != nullptr && current->next->value < num)
			{
				current = current->next;
			}

			stack[level++] = current;
			current = current->down;
		}

		bool insertHigherLevel = true;
		Node *down = nullptr;

		while (insertHigherLevel && level > 0)
		{
			Node *predecessor = stack[--level];
			predecessor->next = new Node(num, predecessor->next, down);
			down = predecessor->next;
			insertHigherLevel = rand() % 2 == 1;
		}
		/*
		if (insertHigherLevel) {
			head = new Node(0, new Node(num, nullptr, down), head);
		}
		*/
	}

	bool erase(int num)
	{
		Node *current = head;
		bool found = false;

		while (current != nullptr)
		{
			while (current->next != nullptr && current->next->value < num)
			{
				current = current->next;
			}

			if (current->next != nullptr && current->next->value == num)
			{
				found = true;
				Node *temp = current->next;
				current->next = temp->next;
				delete temp;
			}

			current = current->down;
		}

		return found;
	}
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */