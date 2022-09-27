#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>


std::string convertInfix(const std::string& input) //takes infix and convert it into RPN notation ----> (a+b)*c/d ---> ab+c*d/
{
	std::string operators("^*/%+-"); // Operator precedence from the highes to lowest
	std::stack<char>stos2{};
	std::string result{};
	for (auto x : input)
	{
		if (x >= '0' && x <= '9')
			result += x;
		else if (x == '(')
			stos2.push(x);
		else if (operators.find(x) != std::string::npos)
		{
			if (!stos2.size() == 0 && operators.find(stos2.top()) != std::string::npos)
			{
				if (operators.find(x) > operators.find(stos2.top()))
				{
					result += stos2.top();
					stos2.pop();
					stos2.push(x);
				}
				else
					stos2.push(x);
			}
			else
				stos2.push(x);
		}
		else if (x == ')')
		{
			while (stos2.top() != '(')
			{
				result += stos2.top();
				stos2.pop();
			}
			stos2.pop();
		}
	}
	while (!stos2.empty())
	{
		result += stos2.top();
		stos2.pop();
	}
	return result;
}

std::string removeBlanks(std::string rpn_input) // remove space from RPN sequence
{
	rpn_input.erase(remove(rpn_input.begin(), rpn_input.end(), ' '), rpn_input.end());
	return rpn_input;
}


int calculate(std::string rpn)
{
	std::stack<int>stos{};

	for (auto x : rpn)
	{
		int valA{}, valB{};
		if (x >= '0' && x <= '9')
			stos.push(x - 48); // push to stack and convert value from ASCII to int value
		else
		{
			// rule LIFO - Last In Firs Out
			valB = stos.top();
			stos.pop();
			valA = stos.top();
			stos.pop();

			switch (x)
			{
			case '+':
			{
				stos.push(valA + valB);
				break;
			}
			case '-':
			{
				stos.push(valA - valB);
				break;
			}
			case '*':
			{
				stos.push(valA * valB);
				break;
			}
			case '/':
			{
				stos.push(valA / valB);
				break;
			}
			case '^':
			{
				stos.push(valA ^ valB);
				break;
			}
			default:
				break;
			}

		}
	}
	return stos.top();
}

int main()
{
	std::string rpn{};
	std::string infix{};

	std::cout << "+---------------------------------+\n" << std::endl;
	std::cout << "+- Welcome to the RPN Calculator -+\n" << std::endl;
	std::cout << "+---------------------------------+\n" << std::endl;

	do {
		std::cout << "Write your infix expression:\n" << std::endl;
		std::cin >> infix;

		rpn = convertInfix(infix);

		std::cout << "\nConverted infix expresion ---> " << infix << " <--- to RPN ---> " << rpn << " <---\n" << std::endl;
		std::cout << "\nResult RPN is: " << calculate(rpn) << "\n" << std::endl;

	} while (true);
}
