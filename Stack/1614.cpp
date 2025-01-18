#include <stack>
class Solution
{
public:
	int maxDepth(string s)
	{
		stack<char> pila;
		int count = 0;
		int max = 0;
		for (char c : s)
		{
			if (c == '(')
			{
				pila.push(c);
				count++;
			}
			if (c == ')')
			{
				pila.pop();
				count--;
			}
			if (max < count)
				max = count;
		}
		return max;
	}
};