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
	ListNode *insertionSortList(ListNode *head)
	{
		if (head == nullptr || head->next == nullptr)
		{
			return head;
		}

		auto prevHead = new ListNode(0, head);
		auto current = head;

		while (current != nullptr && current->next != nullptr)
		{
			if (current->val <= current->next->val)
			{
				current = current->next;
				continue;
			}

			auto toInsert = current->next;
			current->next = current->next->next;

			auto prev = prevHead;
			while (prev->next->val < toInsert->val)
			{
				prev = prev->next;
			}

			toInsert->next = prev->next;
			prev->next = toInsert;
		}
		return prevHead->next;
	}
};