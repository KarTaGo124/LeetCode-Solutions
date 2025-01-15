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
	ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
	{
		auto prevHead = new ListNode(0);
		auto temp1 = list1;
		auto temp2 = list2;
		auto temp3 = prevHead;
		while (temp1 != nullptr || temp2 != nullptr)
		{

			if (temp1 != nullptr && temp2 != nullptr)
			{
				if (temp1->val <= temp2->val)
				{
					temp3->next = new ListNode(temp1->val);
					temp1 = temp1->next;
					temp3 = temp3->next;
				}
				else
				{
					temp3->next = new ListNode(temp2->val);
					temp2 = temp2->next;
					temp3 = temp3->next;
				}
			}

			while (temp1 == nullptr && temp2 != nullptr)
			{
				temp3->next = new ListNode(temp2->val);
				temp2 = temp2->next;
				temp3 = temp3->next;
			}

			while (temp1 != nullptr && temp2 == nullptr)
			{
				temp3->next = new ListNode(temp1->val);
				temp1 = temp1->next;
				temp3 = temp3->next;
			}
		}
		return prevHead->next;
	}
};