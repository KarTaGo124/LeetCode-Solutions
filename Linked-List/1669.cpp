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
	void removeSomeNodesAfterANode(ListNode *node, int n)
	{
		auto temp = node->next;
		for (int i = 0; i < n; i++)
		{
			auto toDelete = temp;
			temp = temp->next;
			delete toDelete;
		}
		node->next = nullptr;
	}
	ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2)
	{
		auto temp1 = list1;
		for (int i = 0; i < a - 1; i++)
		{
			temp1 = temp1->next;
		}

		auto temp2 = temp1;
		for (int j = 0; j <= b - a; j++)
		{
			temp2 = temp2->next;
		}

		auto temp3 = list2;
		while (temp3->next != nullptr)
		{
			temp3 = temp3->next;
		}

		temp3->next = temp2->next;

		removeSomeNodesAfterANode(temp1, b - a + 1);

		temp1->next = list2;

		return list1;
	}
};