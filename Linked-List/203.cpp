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
	ListNode *removeElements(ListNode *head, int val)
	{
		if (head == nullptr)
			return nullptr;

		while (head != nullptr && head->val == val)
		{
			auto toDelete = head;
			head = head->next;
			toDelete->next = nullptr;
			delete toDelete;
		}
		if (head == nullptr)
			return nullptr;

		auto temp = head;
		while (temp->next != nullptr)
		{
			if (temp->next->val == val)
			{
				auto toDelete = temp->next;
				temp->next = temp->next->next;
				toDelete->next = nullptr;
				delete toDelete;
			}
			else
			{
				if (temp->next != nullptr)
					temp = temp->next;
			}
		}
		return head;
	}
};