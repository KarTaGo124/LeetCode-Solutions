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
		int currentComparator;
		while (temp1->next->next != nullptr)
		{
			auto temp2 = temp1->next->next;
			currentComparator = temp2->val;
			while (temp1->next != nullptr && temp1->next->val == currentComparator)
			{
				auto toDelete = temp1->next;
				temp1->next = toDelete->next;
				delete toDelete;
			}
			if (temp1->next == nullptr || temp1->next->next == nullptr)
				break;
			if (temp1->next->val != temp1->next->next->val)
				temp1 = temp1->next;
		}
		return prevHead->next;
	}
};