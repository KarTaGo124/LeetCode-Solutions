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
	ListNode *reverseList(ListNode *head)
	{

		if (head == nullptr || head->next == nullptr)
			return head;

		auto current = head;
		ListNode *newHead = nullptr;

		while (current != nullptr)
		{
			auto nextNode = current->next;
			current->next = newHead;
			newHead = current;
			current = nextNode;
		}
		return newHead;
	}

	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
	{
		l1 = reverseList(l1);
		l2 = reverseList(l2);
		ListNode *prevHead = new ListNode(0);
		auto temp = prevHead;
		int carry = 0;

		while (l1 != nullptr || l2 != nullptr || carry != 0)
		{
			int sum = carry;

			if (l1 != nullptr)
			{
				sum += l1->val;
				l1 = l1->next;
			}

			if (l2 != nullptr)
			{
				sum += l2->val;
				l2 = l2->next;
			}

			carry = sum / 10;
			temp->next = new ListNode(sum % 10);
			temp = temp->next;
		}
		return reverseList(prevHead->next);
	}
};