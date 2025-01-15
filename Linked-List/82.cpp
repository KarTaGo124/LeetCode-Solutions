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
	ListNode *deleteDuplicates(ListNode *head)
	{
		auto prevHead = new ListNode(0, head);

		if (head == nullptr || head->next == nullptr)
			return head;

		auto temp1 = prevHead;
		int i = 0;
		while (temp1->next != nullptr)
		{
			ListNode *temp2;
			if (temp1->next->next == nullptr)
				temp2 = new ListNode(-101);
			else
				temp2 = temp1->next->next;

			if (temp1->next->val == temp2->val)
			{
				auto toDelete = temp1->next;
				toDelete->next = nullptr;
				temp1->next = temp2;
				delete toDelete;
				i++;
			}
			else if (i > 0)
			{
				if (temp1->next->next != nullptr)
				{
					auto toDelete = temp1->next;
					toDelete->next = nullptr;
					temp1->next = temp2;
					delete toDelete;
					i = 0;
				}
				else
				{
					temp1->next = nullptr;
					return prevHead->next;
				}
			}
			else if (i == 0 && temp1->next->next == nullptr)
			{
				return prevHead->next;
			}
			else
			{
				temp1 = temp1->next;
			}
		}
		return prevHead->next;
	}
};