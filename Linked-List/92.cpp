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

	ListNode *reverseBetween(ListNode *head, int left, int right)
	{
		if (head == nullptr || head->next == nullptr || left == right)
			return head;
		auto prevHead = new ListNode(0, head);
		auto temp = prevHead;
		for (int i = 0; i < left - 1; i++)
		{
			temp = temp->next;
		}
		auto temp4 = prevHead;
		for (int k = 0; k < right; k++)
		{
			temp4 = temp4->next;
		}
		auto newHead = new ListNode(0);
		auto temp2 = newHead;
		auto temp3 = temp->next;
		for (int j = 0; j < right - left + 1; j++)
		{
			temp2->next = new ListNode(temp3->val);
			temp3 = temp3->next;
			temp2 = temp2->next;
		}

		ListNode *newNode = nullptr;
		newNode = reverseList(newHead->next);
		auto temp5 = newNode;
		while (temp5->next != nullptr)
		{
			temp5 = temp5->next;
		}
		temp5->next = temp4->next;
		temp->next = newNode;
		return prevHead->next;
	}
};