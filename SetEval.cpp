#include "SetEval.h"


SetEval::SetEval()
{
}


SetEval::~SetEval()
{
}


bool SetEval::testParthenesis(string Input)
{
	char testChar = NULL;

	//Finds all the right and left parthenesis in equation being read from the file
	for (int i = 0; i < Input.length(); i++)
	{
		if (Input[i] == '(' || Input[i] == ')')
		{
			holdParthenesis.push(Input[i]);
		}
	}

	//Test to make sure there is a matching right and left parthenesis, otherwise
	//a error message gets printed
	while (!holdParthenesis.empty())
	{
		if (testChar == ')' && holdParthenesis.top() == '(')
		{
			holdParthenesis.pop();
			testChar = NULL;
		}
		else if (testChar == ')' && holdParthenesis.top() == ')')
		{
			tempParthenesis.push(testChar);
			testChar = holdParthenesis.top();
			holdParthenesis.pop();
		}
		else if (holdParthenesis.top() == '(' && tempParthenesis.top() == ')')
		{
			holdParthenesis.pop();
			tempParthenesis.pop();
		}
		else if (holdParthenesis.top() == ')')
		{
			testChar = holdParthenesis.top();
			holdParthenesis.pop();
		}
		else
		{
			cout << "Error parthensis mismatch!\n";
			return false;
		}
	}

	//One last check to make for matching parenthesis
	if (!tempParthenesis.empty() || testChar != NULL)
	{
		cout << "Error parthensis mismatch!\n";
		return false;
	}
	else
	{
		return true;
	}
}


void SetEval::eval()
{
	char holdChar = NULL; //Holds the next char from the stack to evaulate
	int found = 0; 
	int result = 0; //The loaction of the results set
	int set1, set2 = 0; //I use these ints to hold the locations of the sets im going to evaluate
	stack<char> rpnEqu; //Holds the rpn equation

	//Pushed the rpn equation onto the stack
	for (int i = Equ.size() - 1; i >= 0; i--)
	{
		rpnEqu.push(Equ[i]);
	}

	//Loops untill the rpn euqation is empty
	do
	{
		//Checks the top of the stack to see if its a char
		if (rpnEqu.top() <= 90 && rpnEqu.top() >= 65)
		{
			if (holdChar == NULL)
			{
				holdChar = rpnEqu.top();
				rpnEqu.pop();
			}
			else
			{
				rpnHold.push(holdChar);
				holdChar = rpnEqu.top();
				rpnEqu.pop();
			}
			
		}
		//If the top of the stack is a function I find my sets for calculation
		else if (rpnEqu.top() == '*' || rpnEqu.top() == '^'
			|| rpnEqu.top() == '+' || rpnEqu.top() == '-')
		{
			for (int i = 0; i < Sets.size(); i++)
			{
				if (Sets.at(i)->Name == rpnHold.top())
				{
					set1 = i;
				}
			}

			for (int i = 0; i < Sets.size(); i++)
			{
				if (Sets.at(i)->Name == holdChar)
				{
					set2 = i;
				}
			}

			//Based on the function I perform the computation for that function
			switch (rpnEqu.top())
			{
			case '*':
				for (int i = 0; i < Sets.at(set1)->Nums.size(); i++)
				{
					for (int j = 0; j < Sets.at(set2)->Nums.size(); j++)
					{
						if (Sets.at(set1)->Nums.at(i) == Sets.at(set2)->Nums.at(j))
						{
							found = 1;
						}
					}

					if (found != 1)
					{
						Sets.at(set1)->Nums.erase(Sets.at(set1)->Nums.begin() + i);
						i--;
					}

					found = 0;
				}
				rpnEqu.pop();
				holdChar = rpnHold.top();
				rpnHold.pop();
				break;
			case '^':
				for (int i = 0; i < Sets.at(set1)->Nums.size(); i++)
				{
					for (int j = 0; j < Sets.at(set2)->Nums.size(); j++)
					{
						if (Sets.at(set1)->Nums.at(i) == Sets.at(set2)->Nums.at(j))
						{
							found = 1;
							Sets.at(set2)->Nums.erase(Sets.at(set2)->Nums.begin() + j);
						}
					}

					if (found == 1)
					{
						Sets.at(set1)->Nums.erase(Sets.at(set1)->Nums.begin() + i);
						i--;
					}

					found = 0;
				}

				for (int i = 0; i < Sets.at(set2)->Nums.size(); i++)
				{
					for (int j = 0; j < Sets.at(set1)->Nums.size(); j++)
					{
						if (Sets.at(set2)->Nums.at(i) == Sets.at(set1)->Nums.at(j))
						{
							found = 1;
						}
					}

					if (found != 1)
					{
						Sets.at(set1)->Nums.push_back(Sets.at(set2)->Nums.at(i));
					}

					found = 0;
				}
				rpnEqu.pop();
				holdChar = rpnHold.top();
				rpnHold.pop();
				break;
			case '+':
				for (int i = 0; i < Sets.at(set2)->Nums.size(); i++)
				{
					for (int j = 0; j < Sets.at(set1)->Nums.size(); j++)
					{
						if (Sets.at(set2)->Nums.at(i) == Sets.at(set1)->Nums.at(j))
						{
							found = 1;
						}
					}

					if (found != 1)
					{
						Sets.at(set1)->Nums.push_back(Sets.at(set2)->Nums.at(i));
					}

					found = 0;
				}
				rpnEqu.pop();
				holdChar = rpnHold.top();
				rpnHold.pop();
				break;
			case '-':
				for (int i = 0; i < Sets.at(set1)->Nums.size(); i++)
				{
					for (int j = 0; j < Sets.at(set2)->Nums.size(); j++)
					{
						if (Sets.at(set1)->Nums.at(i) == Sets.at(set2)->Nums.at(j))
						{
							found = 1;
						}
					}

					if (found == 1)
					{
						Sets.at(set1)->Nums.erase(Sets.at(set1)->Nums.begin() + i);
						i--;
					}

					found = 0;
				}
				rpnEqu.pop();
				holdChar = rpnHold.top();
				rpnHold.pop();
				break;
			default:
				break;
			}
		}
	}while (!rpnEqu.empty());

	//Sets my result int
	for (int i = 0; i < Sets.size(); i++)
	{
		if (Sets.at(i)->Name == holdChar)
		{
			result = i;
		}
	}
	
	//Sorts the result in order
	sort(Sets.at(result)->Nums.begin(), Sets.at(result)->Nums.end());

	//Prints the answer
	cout << "{ ";
	for (int i = 0; i < Sets.at(result)->Nums.size(); i++)
	{
		cout << Sets.at(result)->Nums.at(i);
		if (i != Sets.at(result)->Nums.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
}


bool SetEval::parse(string Input)
{
	if (!testParthenesis(Input))
	{
		return false;
	}

	int isSet = 0; //Test to see if the line being read is a set
	int isDigit = 0; //Helps me to find the digits inside the sets
	Set *tempSet; //Set pointer for creating the my sets
	string Num; //Hols the digit characters for converting to integers

	//Checks the string to see if there is a '=' sign in there to signify that it
	//is a set
	for (int i = 0; i < Input.length(); i++)
	{
		if (Input[i] == '=')
		{
			isSet = 1;
		}
	}


	//If the string is a set it this creates a new set struct and stores it
	if (isSet == 1)
	{
		tempSet = new Set;
		tempSet->Name = Input[0];

		for (int i = 0; i < Input.length(); i++)
		{
			Num.clear();

			if (isdigit(Input[i]))
			{
				while (isdigit(Input[i]))
				{
					Num.push_back(Input[i]);
					i++;
				}

				tempSet->Nums.push_back(stoi(Num));
			}
		}

		Sets.push_back(tempSet);
	}
	else if (isSet == 0)
	{
		Equ = Input;
	}

	return true;
}


void SetEval::rpn()
{
	string rpnEqu; //String for holding my rpn euqation
	string infixEqu; //String for holding my infix equation

	infixEqu = Equ;

	//Converts the infix equation to rpn
	for (int i = 0; i < infixEqu.length(); i++)
	{
		//Checks the infix for begining parenthesis
		if (infixEqu.at(i) == '(')
		{
			rpnHold.push(infixEqu[i]);
		} //(Oumghar, Karmin)
		//Checks the infix for ending parenthesis
		else if (infixEqu.at(i) == ')')
		{
			while (!rpnHold.empty() && rpnHold.top() != '(')
			{
				rpnEqu.push_back(rpnHold.top());
				rpnHold.pop();
			}

			rpnHold.pop();
		} //(Oumghar, Karmin)
		//Checks the infix for a +, -, ^
		else if (infixEqu.at(i) == '+' || infixEqu.at(i) == '-' || infixEqu.at(i) == '^')
		{
			if (!rpnHold.empty())
			{
				//Checking for precedence
				if (rpnHold.top() == '*')
				{
					rpnEqu.push_back(rpnHold.top());
					rpnHold.pop();
				}
			}

			rpnHold.push(infixEqu[i]);
		}
		//Checks the infix for a *
		else if (infixEqu.at(i) == '*')
		{
			rpnHold.push(infixEqu.at(i));
		}
		else if (infixEqu.at(i) != ' ')
		{
			rpnEqu.push_back(infixEqu[i]);
		}
	}

	//After its done I push the remaining funtions onto the equation
	while (!rpnHold.empty())
	{
		rpnEqu.push_back(rpnHold.top());
		rpnHold.pop();
	}

	Equ = rpnEqu;
}

//Oumghar, Karmin. "Convert Infix to Prefix Notation C /C# Implementation (shunting Yard Method)." Bits and Pieces of Code. 3 Jan. 2015. Web. 23 Feb. 2015. <https://simpledevcode.wordpress.com/2015/01/03/convert-infix-to-reverse-polish-notation-c-implementation/>.




