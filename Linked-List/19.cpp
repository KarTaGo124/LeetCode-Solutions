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

int size(ListNode *head)
{
	int i = 0;
	if (head == nullptr)
	{
		return i;
	}
	while (head->next != nullptr)
	{
		i++;
		head = head->next;
	}
	return i;
}
class Solution
{
public:
	ListNode *removeNthFromEnd(ListNode *head, int n)
	{
		auto prevHead = new ListNode(0, head);
		int tamano = size(prevHead);
		auto temp = prevHead;
		if (tamano == n)
		{
			auto temp3 = head;
			head = head->next;
			temp3->next = nullptr;
			delete temp3;
			return head;
		}
		else
		{
			int i = 0;
			while (i < tamano - n)
			{
				temp = temp->next;
				i++;
			}
			auto temp2 = temp->next;
			temp->next = temp->next->next;
			temp2->next = nullptr;
			delete temp2;
			return head;
		}
	}
};