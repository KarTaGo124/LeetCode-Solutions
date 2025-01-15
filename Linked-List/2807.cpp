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
int mcd(int x, int y)
{
	if (y == 0)
		return x;
	else
		return mcd(y, x % y);
}
class Solution
{
public:
	ListNode *insertGreatestCommonDivisors(ListNode *head)
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		auto temp = head;
		int number;
		while (temp->next != nullptr)
		{
			number = mcd(temp->val, temp->next->val);
			auto toInsert = new ListNode(number);
			toInsert->next = temp->next;
			temp->next = toInsert;
			temp = temp->next->next;
		}
		return head;
	}
};