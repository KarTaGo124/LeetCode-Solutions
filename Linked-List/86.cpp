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
	ListNode *partition(ListNode *head, int x)
	{
		auto newNode = new ListNode(-102);
		auto temp2 = newNode;
		auto prevHead = new ListNode(-101, head);
		auto temp = prevHead;
		while (temp->next != nullptr)
		{
			if (temp->next->val >= x)
			{
				auto toDelete = temp->next;
				temp2->next = new ListNode(temp->next->val);
				temp2 = temp2->next;
				temp->next = toDelete->next;
				delete toDelete;
			}
			else
			{
				temp = temp->next;
			}
		}
		temp->next = newNode->next;
		return prevHead->next;
	}
};