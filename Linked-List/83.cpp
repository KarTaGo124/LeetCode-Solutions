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
		if (head == nullptr || head->next == nullptr)
			return head;
		auto temp1 = head;
		while (temp1->next != nullptr)
		{
			auto temp2 = temp1->next;
			if (temp1->val == temp2->val)
			{
				temp1->next = temp2->next;
				temp2->next = nullptr;
				delete temp2;
			}
			else
			{
				temp1 = temp1->next;
			}
		}
		return head;
	}
};