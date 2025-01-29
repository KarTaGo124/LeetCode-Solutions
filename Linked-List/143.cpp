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
class Solution
{
public:
	int size(ListNode *head)
	{
		int i = 0;
		while (head)
		{
			i++;
			head = head->next;
		}
		return i;
	}
	ListNode *reverseList(ListNode *head)
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

	void reorderList(ListNode *head)
	{
		if (head == nullptr || head->next == nullptr)
			return;
		int length = size(head);

		auto temp = head;
		for (int i = 0; i < length / 2; i++)
		{
			temp = temp->next;
		}

		ListNode *secondHalf = reverseList(temp->next);
		temp->next = nullptr;

		ListNode *firstHalf = head;

		while (secondHalf != nullptr)
		{
			auto temp1 = firstHalf->next;
			auto temp2 = secondHalf->next;

			firstHalf->next = secondHalf;
			secondHalf->next = temp1;

			firstHalf = temp1;
			secondHalf = temp2;
		}
	}
};