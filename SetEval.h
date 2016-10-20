#ifndef SETEVAL
#define SETEVAL
#pragma once
#include "Set.h"
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
class SetEval
{
public:
	SetEval(); //Default constructor
	~SetEval(); //Deafult destructor
	bool testParthenesis(string Input); //Test to make sure there are correct amount of parenthesis
	void eval(); //Evaluates the equation and gives the final result
	bool parse(string Input); //Reads in the strings from the file and stores them
	void rpn(); //Converts the equation given from the file and coverts it from infix to rpn
private:
	stack<char> holdParthenesis; //I use these two stacks to help check for matching parenthesis in
	stack<char> tempParthenesis; //my equations.
	stack<char> rpnHold; //Holds my characters while a convert from infix to rpn
	vector<Set*> Sets; //Holds the different sets that are inputed from the file
	string Equ; //Holds my equation
};
#endif

