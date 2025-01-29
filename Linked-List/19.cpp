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
	while (head != nullptr)
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
		int tamano = size(head);
		auto temp = prevHead;

		int i = 0;
		while (i < tamano - n)
		{
			temp = temp->next;
			i++;
		}
		auto toDelete = temp->next;
		temp->next = toDelete->next;
		delete toDelete;

		return prevHead->next;
	}
};