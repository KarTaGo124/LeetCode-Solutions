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

int size_list(ListNode *head)
{
	int i = 0;
	while (head != nullptr)
	{
		head = head->next;
		i++;
	}
	return i;
}
class Solution
{
public:
	ListNode *rotateRight(ListNode *head, int k)
	{
		int k_real;
		if (size_list(head) != 0)
			k_real = k % size_list(head);
		else
			k_real = k;
		if (head == nullptr || head->next == nullptr)
			return head;
		else
		{
			for (int i = 0; i < k_real; i++)
			{
				auto temp = head;
				while (temp->next->next != nullptr)
				{
					temp = temp->next;
				}
				temp->next->next = head;
				head = temp->next;
				temp->next = nullptr;
			}
		}
		return head;
	}
};