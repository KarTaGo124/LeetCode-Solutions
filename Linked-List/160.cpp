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
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
	{
		auto currentA = headA;
		auto currentB = headB;

		while (currentA != nullptr)
		{
			auto currentC = currentB;
			while (currentB != nullptr)
			{
				if (currentA == currentB)
					return currentA;
				currentB = currentB->next;
			}
			currentA = currentA->next;
			currentB = currentC;
		}
		return nullptr;
	}
};