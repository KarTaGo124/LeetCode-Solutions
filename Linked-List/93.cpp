/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

int size(ListNode *node)
{
	int i = 0;
	auto temp = node;
	while (temp != nullptr)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

int value(int position, ListNode *head)
{
	if (head == nullptr)
	{
		return -1;
	}
	else
	{
		auto *temp = head;
		int i = 0;
		while (i < position)
		{
			temp = temp->next;
			i++;
		}
		if (temp != nullptr)
			return temp->val;
		else
			return -1;
	}
}

ListNode *reverse(ListNode *head)
{
	if (head == nullptr || head->next == nullptr)
		return head;

	auto current = head;
	ListNode *newHead = nullptr;

	while (current != nullptr)
	{
		auto nextNode = current->next;
		current->next = newHead;
		newHead = current;
		current = nextNode;
	}
	return newHead;
}
class Solution
{
public:
	bool isPalindrome(ListNode *head)
	{
		if (head == nullptr || head->next == nullptr)
			return true;
		auto temp = head;
		int tamano = size(head);

		for (int i = 0; i < tamano / 2; i++)
		{
			temp = temp->next;
		}
		temp = reverse(temp);

		auto firstHalf = head;
		auto secondHalf = temp;

		for (int i = 0; i < tamano / 2; i++)
		{
			if (firstHalf->val != secondHalf->val)
				return false;
			firstHalf = firstHalf->next;
			secondHalf = secondHalf->next;
		}
		return head;
	}
};
