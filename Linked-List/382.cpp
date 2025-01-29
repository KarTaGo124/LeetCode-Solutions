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
private:
	ListNode *head;

public:
	int size(ListNode *head)
	{
		int i = 0;
		while (head != nullptr)
		{
			head = head->next;
			i++;
		}
		return i;
	}

	Solution(ListNode *head)
	{
		this->head = head;
		srand(time(nullptr));
	}

	int getRandom()
	{
		int x = rand() % size(head);
		auto temp = head;
		for (int i = 0; i < x; i++)
		{
			temp = temp->next;
		}
		return temp->val;
	}
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */