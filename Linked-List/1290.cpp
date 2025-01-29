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
	int getDecimalValue(ListNode *head)
	{
		auto temp1 = head;
		int size = 0;
		while (temp1 != nullptr)
		{
			temp1 = temp1->next;
			size++;
		}

		long long int total = 0;
		auto temp = head;
		while (temp != nullptr)
		{
			size--;
			total += pow(2, size) * (temp->val);
			temp = temp->next;
		}
		return total;
	}
};