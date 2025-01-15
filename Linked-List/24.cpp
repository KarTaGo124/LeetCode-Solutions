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
		if (head == nullptr || head->next == nullptr)
			return head;
		auto temp = head;
		auto temp2 = temp->next->next;
		temp->next->next = temp;
		head = temp->next;
		temp->next = temp2;

		while (temp->next != nullptr && temp->next->next != nullptr)
		{
			auto temp3 = temp;
			temp = temp->next;
			temp2 = temp->next->next;
			temp->next->next = temp;
			temp3->next = temp->next;
			temp->next = temp2;
		}
		return head;
	}
};