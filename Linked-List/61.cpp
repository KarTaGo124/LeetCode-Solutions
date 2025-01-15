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
	if (head == nullptr)
	{
		return 0;
	}
	else
	{
		auto temp = head;
		int i = 1;
		while (temp->next != nullptr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}
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
		if (head == nullptr)
			return nullptr;
		else if (head->next == nullptr)
			return head;
		else
		{
			for (int i = 0; i < k_real; i++)
			{
				auto temp = head;
				auto temp2 = head->next;
				while (temp2->next != nullptr)
				{
					temp = temp->next;
					temp2 = temp2->next;
				}
				temp2->next = head;
				head = temp2;
				temp->next = nullptr;
			}
		}
		return head;
	}
};