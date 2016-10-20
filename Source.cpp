#include "SetEval.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(){
	bool parenthesisCheck = true;
	string Test;
	string temp;
	ifstream myFile;
	SetEval testProblem;
	
	//Finds the file to read from
	myFile.open("C:/Users/Jeffrey/Dropbox/My Programs/JeffreyHoover_DataStructures_Project2/Test.txt", ios::in);

	//Reads in the information for the file and stores it in my object
	do
	{
		getline(myFile, Test);
		parenthesisCheck = (testProblem.parse(Test)) ? true : false;
	} while (!(myFile.eof()));

	//Evaluates and prints the results if there is correct amount of
	//parenthesis
	if (parenthesisCheck)
	{
		testProblem.rpn();
		testProblem.eval();
	}

	system("pause");
}