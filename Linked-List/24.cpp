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
	ListNode *swapPairs(ListNode *head)
	{
		auto prevHead = new ListNode(0, head);
		if (head == nullptr || head->next == nullptr)
			return head;
		auto temp1 = prevHead;
		auto temp2 = temp1->next;

		while (temp2 != nullptr && temp2->next != nullptr)
		{
			temp1->next = temp2->next;
			temp2->next = temp2->next->next;
			temp1->next->next = temp2;
			temp1 = temp2;
			temp2 = temp1->next;
		}
		return prevHead->next;
	}
};