/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
	void deleteNode(ListNode *node)
	{
		auto temp = node;
		ListNode *temp2 = nullptr;
		while (temp->next != nullptr)
		{
			temp->val = temp->next->val;
			if (temp->next->next == nullptr)
				temp2 = temp;
			temp = temp->next;
		}
		temp2->next = nullptr;
	}
};