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
	bool hasCycle(ListNode *&slow, ListNode *&fast)
	{

		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
				return true;
		}
		return false;
	}

	ListNode *detectCycle(ListNode *head)
	{
		ListNode *slow = head;
		ListNode *fast = head;

		if (hasCycle(slow, fast))
		{
			fast = head;
			while (slow != fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
		return nullptr;
	}
};
