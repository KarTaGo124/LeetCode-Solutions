/*
// Definition for a Node.
class Node {
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;
};
*/

class Solution
{
public:
	Node *flatten(Node *head)
	{
		if (head == nullptr)
			return head;
		auto current = head;
		while (current != nullptr)
		{
			if (current->child != nullptr)
			{
				auto nextCurr = current->next;
				current->next = current->child;
				current->child->prev = current;
				current->child = nullptr;
				auto temp = current;
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}
				temp->next = nextCurr;
				if (nextCurr != nullptr)
					nextCurr->prev = temp;
			}
			current = current->next;
		}
		return head;
	}
};

/*
class Solution {
public:
	Node* flatten(Node* head) {
		if (head == nullptr) return head;

		auto current = head;

		while (current != nullptr) {
			if (current->child != nullptr) {
				auto nextCurr = current->next;
				auto child = flatten(current->child);
				current->next = current->child;
				current->child->prev = current;
				current->child = nullptr;
				while (current->next != nullptr){
					current = current->next;
				}
				if (nextCurr != nullptr) {
					current->next = nextCurr;
					nextCurr->prev = current;
				}
			}
			current = current->next;
		}
		return head;
	}
};
*/