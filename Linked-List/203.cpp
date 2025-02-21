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

		auto prevHead = new ListNode(-1, head);

		auto temp = prevHead;

		while (temp->next != nullptr)
		{
			if (temp->next->val == val)
			{
				auto toDelete = temp->next;
				temp->next = toDelete->next;
				delete toDelete;
			}
			else
			{
				temp = temp->next;
			}
		}
		return prevHead->next;
	}
};