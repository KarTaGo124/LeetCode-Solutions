#include <iostream>
#include <stack>

class Solution
{
public:
	bool isValid(string s)
	{
		stack<char> pila;
		for (char c : s)
		{
			if (c == '(' || c == '{' || c == '[')
				pila.push(c);
			if (c == ')' || c == '}' || c == ']')
			{
				if (pila.empty())
					return false;
				char x = pila.top();
				pila.pop();
				if (x == '(' && c != ')')
					return false;
				if (x == '{' && c != '}')
					return false;
				if (x == '[' && c != ']')
					return false;
			}
		}
		if (pila.empty())
			return true;
		else
			return false;
	}
};