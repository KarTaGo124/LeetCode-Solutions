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
	ListNode *oddEvenList(ListNode *head)
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		auto nextNode = head->next;
		auto temp1 = head;
		auto temp2 = nextNode;
		while (temp2 != nullptr && temp2->next != nullptr)
		{
			temp1->next = temp2->next;
			temp2->next = temp2->next->next;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		if (temp1 != nullptr)
			temp1->next = nullptr;
		if (temp2 != nullptr)
			temp2->next = nullptr;
		auto temp3 = head;
		while (temp3->next != nullptr)
		{
			temp3 = temp3->next;
		}
		temp3->next = nextNode;
		return head;
	}
};